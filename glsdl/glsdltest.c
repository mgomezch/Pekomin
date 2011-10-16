#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

void exit_error(void *f) {
        char *e = "Unknown SDL error";
        if      (f == SDL_SetVideoMode   ) e = "Couldn't set SDL video mode"  ;
        else if (f == SDL_GL_SetAttribute) e = "Couldn't set OpenGL attribute";
        else if (f == SDL_Init           ) e = "Couldn't initialize SDL"      ;
        fprintf(stderr, "%s: %s\n", e, SDL_GetError());
        exit(EX_OSERR);
}

int **init_life(const unsigned int w, const unsigned int h) {
        int i, j;
        int **grid = NULL;
        errno = 0;
        if ((grid = malloc(h*sizeof(int *))) == NULL) return NULL;
        for (j = 0; j < h; j++) if ((grid[j] = malloc(w*sizeof(int))) == NULL) {
                for (i = 0; i < j; ++i) free(grid[i]);
                free(grid);
                return NULL;
        }
        for (j = 0; j < h; ++j) for (i = 0; i < h; ++i) grid[i][j] = 0;
        return grid;
}

void advance_life(int **grid, const unsigned int w, const unsigned int h) {
        int i, j;
        int neighbors[w][h];
        for (j = 0; j < h; ++j) for (i = 0; i < w; ++i) neighbors[i][j] = 0;
        for (j = 0; j < h; ++j) for (i = 0; i < w; ++i) if (grid[i][j]) {
                if (0 <= j-1) {
                        if (0 <= i-1) neighbors[i-1][j-1] += 1;
                        neighbors[i][j-1] += 1;
                        if (i+1 < w) neighbors[i+1][j-1] += 1;
                }
                if (0 <= i-1) neighbors[i-1][j] += 1;
                if (i+1 < w) neighbors[i+1][j] += 1;
                if (j+1 < h) {
                        if (0 <= i-1) neighbors[i-1][j+1] += 1;
                        neighbors[i][j+1] += 1;
                        if (i+1 < w) neighbors[i+1][j+1] += 1;
                }
        }
        for (j = 0; j < h; ++j) for (i = 0; i < w; i++) switch (neighbors[i][j]) {
                case 3:
                        grid[i][j] = 1;
                case 2:
                        break;
                default:
                        grid[i][j] = 0;
        }
}

int toggle_life(int **grid, const unsigned int x, const unsigned int y) {
        return grid[x][y] ^= 1;
}

void wipe_life(int **grid, const unsigned int w, const unsigned int h) {
        int i, j;
        for (j = 0; j < h; ++j) for (i = 0; i < w; ++i) grid[i][j] = 0;
}

int get_life(int **grid, const int x, const int y) {
        return grid[x][y];
}

void set_life(int **grid, const int x, const int y) {
        grid[x][y] = 1;
}

void unset_life(int **grid, const int x, const int y) {
        grid[x][y] = 0;
}

int main(int argc, char **argv) {
        int i,
            j,
            running,
            drawing,
            erasing,
            held_l,
            held_r,
            held_d,
            held_u,
            held_zoom_out,
            held_zoom_in,
            verbose;
        unsigned int w,
                     h,
                     ci,
                     cj,
                     ww,
                     wh,
                     fps_limit = 60;
        Uint16 mx,
               my;
        Uint32 begin,
               ticks,
               delay;
        int **grid;
        double aspect_ratio,
               x,
               y,
               zoom,
               min_x,
               max_x,
               min_y,
               max_y,
               min_zoom,
               max_zoom,
               pan_speed,
               zoom_speed;
        GLdouble pos3D_x,
                 pos3D_y,
                 pos3D_z;
        GLdouble model_view[16];
        GLdouble projection[16];
        GLint viewport[4];
        SDLKey key;
        SDL_Event event;
        SDL_Surface *screen;

        /* TODO: cmdline arguments:
           -v: verbose mode
           -h: usage text */

        if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) == -1) exit_error(SDL_Init);
        if (atexit(SDL_Quit) != 0) {
                fprintf(stderr, "atexit failed!\n");
                exit(EX_OSERR);
        }
        if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8) == -1) exit_error(SDL_GL_SetAttribute);
        if (SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) == -1) exit_error(SDL_GL_SetAttribute);
        if (SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8) == -1) exit_error(SDL_GL_SetAttribute);
        if (SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) == -1) exit_error(SDL_GL_SetAttribute);
        if (SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32) == -1) exit_error(SDL_GL_SetAttribute);
        if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) == -1) exit_error(SDL_GL_SetAttribute);
        if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1) exit_error(SDL_GL_SetAttribute);
        SDL_WM_SetCaption(argv[0], argv[0]);

        ww = 640;
        wh = 480;
        aspect_ratio = ((float)wh)/ww;
        if ((screen = SDL_SetVideoMode(ww, wh, 0, SDL_RESIZABLE|SDL_OPENGL)) == NULL) exit_error(SDL_SetVideoMode);
        if (ww != screen->w||wh != screen->h) {
                fprintf(stderr, "SDL screen dimensions don't match those requested!\nRequested %dx%d; obtained %dx%d", wh, ww, screen->h, screen->w);
                exit(EX_SOFTWARE);
        }

        glViewport(0, 0, ww, wh);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 1, 0, aspect_ratio, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClearColor(0, 0, 0, 0);
        glEnable(GL_BLEND);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_LINE_SMOOTH);
//      glEnable(GL_POLYGON_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        w = 100;
        h = 100;
        if ((grid = init_life(w, h)) == NULL) {
                perror("malloc");
                exit(EX_OSERR);
        }

        min_zoom = 1.0;
        max_zoom = 15.0;
        zoom = 10.0;

        min_x = -0.5;
        min_y = -0.5;
        max_x = w + 0.5 - (((float)ww)/zoom);
        max_y = h + 0.5 - (((float)wh)/zoom);
        x = (min_x + max_x)/2;
        y = (min_y + max_y)/2;

        zoom_speed = 0.025;
        pan_speed = 0.5;

        ci = w/2;
        cj = h/2;

        held_l = 0;
        held_r = 0;
        held_d = 0;
        held_u = 0;
        running = 0;
        drawing = 0;
        erasing = 0;
        held_zoom_out = 0;
        held_zoom_in = 0;
        ticks = SDL_GetTicks();
        while (1) {
                while (SDL_PollEvent(&event)) switch (event.type) {
                        case SDL_MOUSEBUTTONDOWN:
                                if (event.button.button == SDL_BUTTON_LEFT) {
                                        drawing = 1;
                                        erasing = 0;
                                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                                        erasing = 1;
                                        drawing = 0;
                                }
                        case SDL_MOUSEMOTION:
                                glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
                                glGetDoublev(GL_PROJECTION_MATRIX, projection);
                                glGetIntegerv(GL_VIEWPORT, viewport);
                                gluUnProject(event.button.x, wh-event.button.y, 0.01, model_view, projection, viewport, &pos3D_x, &pos3D_y, &pos3D_z);
                                ci = floorf(pos3D_x);
                                cj = floorf(pos3D_y);
                                if (ci <  0) ci = 0;
                                if (ci >= w) ci = w-1;
                                if (cj <  0) cj = 0;
                                if (cj >= h) cj = h-1;
                                if (drawing) set_life(grid, ci, cj);
                                else if (erasing) unset_life(grid, ci, cj);
                                break;
                        case SDL_MOUSEBUTTONUP:
                                if (event.button.button == SDL_BUTTON_LEFT) drawing = 0;
                                else if (event.button.button == SDL_BUTTON_RIGHT) erasing = 0;
                                break;
                        case SDL_KEYDOWN:
                                key = event.key.keysym.sym;
                                if      (key == SDLK_q       ) exit(EX_OK);
                                else if (key == SDLK_LEFT    ) held_l        = 1    ;
                                else if (key == SDLK_RIGHT   ) held_r        = 1    ;
                                else if (key == SDLK_DOWN    ) held_d        = 1    ;
                                else if (key == SDLK_UP      ) held_u        = 1    ;
                                else if (key == SDLK_MINUS   ) held_zoom_out = 1    ;
                                else if (key == SDLK_EQUALS  ) held_zoom_in  = 1    ;
                                else if (key == SDLK_HOME    ) x             = min_x;
                                else if (key == SDLK_END     ) x             = max_x;
                                else if (key == SDLK_PAGEDOWN) y             = min_y;
                                else if (key == SDLK_PAGEUP  ) y             = max_y;
                                else if (key == SDLK_SPACE   ) {
                                        begin = SDL_GetTicks();
                                        running ^= 1;
                                }
                                break;
                        case SDL_KEYUP:
                                key = event.key.keysym.sym;
                                if      (key == SDLK_LEFT  ) held_l        = 0;
                                else if (key == SDLK_RIGHT ) held_r        = 0;
                                else if (key == SDLK_DOWN  ) held_d        = 0;
                                else if (key == SDLK_UP    ) held_u        = 0;
                                else if (key == SDLK_MINUS ) held_zoom_out = 0;
                                else if (key == SDLK_EQUALS) held_zoom_in  = 0;
                                break;
                        case SDL_VIDEORESIZE:
                                if ((event.resize.w > 0)&&(event.resize.h > 0)) {
                                        ww = event.resize.w;
                                        wh = event.resize.h;
                                        aspect_ratio = ((float)wh)/ww;
                                        screen = SDL_SetVideoMode(ww, wh, 32, SDL_RESIZABLE|SDL_OPENGL);
                                        glViewport(0, 0, ww, wh);
                                        glMatrixMode(GL_PROJECTION);
                                        glLoadIdentity();
                                        glOrtho(0, 1, 0, aspect_ratio, 0, 1);
                                        glClearColor(0, 0, 0, 0);
                                        glEnable(GL_BLEND);
                                        glEnable(GL_POINT_SMOOTH);
                                        glEnable(GL_LINE_SMOOTH);
                                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                                        max_x = w + 0.5 - (((float)ww)/zoom);
                                        max_y = h + 0.5 - (((float)wh)/zoom);
                                }
                                break;
                        case SDL_QUIT:
                                exit(EX_OK);
                        default:
                                break;
                }

                if (held_l&&((x -= pan_speed) < min_x)) x = min_x;
                if (held_r&&((x += pan_speed) > max_x)) x = max_x;
                if (held_d&&((y -= pan_speed) < min_y)) y = min_y;
                if (held_u&&((y += pan_speed) > max_y)) y = max_y;
                if (held_zoom_out) {
                        if ((zoom -= zoom*zoom_speed) < min_zoom) zoom = min_zoom;
                        max_x = w + 0.5 - (((float)ww)/zoom);
                        max_y = h + 0.5 - (((float)wh)/zoom);
                }
                if (held_zoom_in) {
                        if ((zoom += zoom*zoom_speed) > max_zoom) zoom = max_zoom;
                        max_x = w + 0.5 - (((float)ww)/zoom);
                        max_y = h + 0.5 - (((float)wh)/zoom);
                }

                glClear(GL_COLOR_BUFFER_BIT);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glScalef(zoom/ww, zoom/ww, 1);
                glTranslatef(-x, -y, 0);

                if (running && (((SDL_GetTicks() - begin) > 250) == 0)) {
                        advance_life(grid, w, h);
                        begin = SDL_GetTicks();
                }

                glBegin(GL_LINES);
                glColor3f(1, 1, 1);
                glVertex3f(0, 0, 0);
                glVertex3f(0, h, 0);
                glVertex3f(0, h, 0);
                glVertex3f(w, h, 0);
                glVertex3f(w, h, 0);
                glVertex3f(w, 0, 0);
                glVertex3f(w, 0, 0);
                glVertex3f(0, 0, 0);
                glColor3f(0.5F, 0.5F, 0.5F);
                for (i = 1; i < w; ++i) {
                        glVertex3f(i, 0, 0);
                        glVertex3f(i, h, 0);
                }
                for (j = 1; j < h; ++j) {
                        glVertex3f(0, j, 0);
                        glVertex3f(w, j, 0);
                }
                glEnd();

                glBegin(GL_QUADS);
                glColor3f(1, 1, 1);
                for (j = 0; j < h; ++j) for (i = 0; i < w; i++) if (get_life(grid, i, j)) {
                        glVertex3f(i, j, 0);
                        glVertex3f(i+1, j, 0);
                        glVertex3f(i+1, j+1, 0);
                        glVertex3f(i, j+1, 0);
                }
                glColor4f(0, 1, 0, 0.3F);
                glVertex3f(ci, cj, 0);
                glVertex3f(ci+1, cj, 0);
                glVertex3f(ci+1, cj+1, 0);
                glVertex3f(ci, cj+1, 0);
                glEnd();

                SDL_GL_SwapBuffers();

                if (glGetError() != GL_NO_ERROR) {
                        /* NOTE: many of these can probably be safely ignored. */
                        fprintf(stderr, "OpenGL error!\n");
                        exit(EX_SOFTWARE);
                }

                /* TODO: fix this. */
                if (fps_limit != 0) {
                        fprintf(stderr, "%f\n", (1000.0F/fps_limit) - (1.0F/(SDL_GetTicks() - ticks)));
                        delay = (1000.0F/fps_limit) - (1.0F/(SDL_GetTicks() - ticks));
                        if (verbose) fprintf(stderr, "delay = %dms: ", delay);
                        if (delay > 0) {
                                SDL_Delay(delay);
                        }
                }
                fprintf(stderr, "%f fps\n", 1000.0F/(SDL_GetTicks() - ticks));
                ticks = SDL_GetTicks();
        }

        exit(EX_OK);
}
