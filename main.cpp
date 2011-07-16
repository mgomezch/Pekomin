#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <vector>

#include <GL/glut.h>
#include <sysexits.h>
#include <sys/time.h>

#include "Behavior.hpp"
#include "Behaviors.hpp"
#include "Dijkstra.hpp"
#include "game.hpp"
#include "gl.hpp"
#include "Node.hpp"
#include "parse.hpp"
#include "Phantom.hpp"
#include "Player.hpp"
#include "RuntimeBox.hpp"
#include "RuntimePoint.hpp"
#include "Alien.hpp"
#include "RuntimeSegment.hpp"
#include "Triple.hpp"
#include "util.hpp"

#define DEBUG_MAIN

#define NO_LIGHTING

#define BUFSIZE 65536
#define DEFAULT_GAME_FILENAME "games/default"

using namespace std;

char *game_filename;

int power(int b, unsigned int e) {
        int r = 1;
        for (; e > 0; e--) {
                r *= b;
        }
        return r;
}

void initJuego() {
        nboom = 0;
        for (i = 0; i < N_BOOM_SETS; i++) {
                boom[i].on = 0;
        }

        frozen    = false;
        level     = START_LEVEL;
        cam_old_t = 0;
        retract   = 1;
        mesh      = false;

        px   = 0;
        py   = 0;
        pz   = 0;
        pv   = 0;
        prz  = 0;
        pvx  = 0;
        pvy  = 0;
        pvz  = 0;
        pvrz = 0;
        pa   = 0;
        pav  = 0;
        pbi  = 0;
        pbn  = 0;
        for (i = 0; i < N_PBALAS; i++) {
                pb[i] = 0;
                pbv[i] = V_BALA_MAX;
        }
        pts   = 0;
        balas = BALAS;

        {
                Ent      *e;
                Behavior *b;
                Actor    *a;

                while (!ents.empty()) {
                        e = ents.back();
                        ents.pop_back();
                        // TODO: hacer lo mismo pa otros tipos de runtime
                        if ((a = dynamic_cast<Actor *>(e)) != NULL) {
                                while (!a->behaviors.empty()) {
                                        b = a->behaviors.back();
                                        a->behaviors.pop_back();
                                        delete b;
                                }
                        }

                        delete e;
                }
                player = NULL;

                for (int i = -60; i <= 40; i = i + 20) {
                        for (int j = -40; j <= 20; j = j + 20) {
                                nodes.push_back(new Node("", (Triple(i     , j     , 0) + Triple(i     , j + 20, 0) + Triple(i + 20, j     , 0))/3.0));
                                nodes.push_back(new Node("", (Triple(i + 20, j + 20, 0) + Triple(i + 20, j     , 0) + Triple(i     , j + 20, 0))/3.0));
                        }
                }

                for (unsigned int i = 0; i < nodes.size(); i++) {
                        for (unsigned int j = 0; j < nodes.size(); j++) {
                                if (nodes[i] != nodes[j] && (nodes[j]->pos - nodes[i]->pos).length() < 25) {
                                        nodes[i]->add_adj(nodes[j]);
                                }
                        }
#ifdef DEBUG_MAIN
                        nodes[i]->print_node();
#endif
                }

                {
                        char buf[BUFSIZE];
                        int pos = 0;
                        FILE *file;

                        if (game_filename == NULL) {
                                file = fopen(DEFAULT_GAME_FILENAME, "r");
                                if (file == NULL) {
                                        perror("error opening default game file " DEFAULT_GAME_FILENAME ": fopen");
                                        exit(EX_IOERR);
                                }
                        } else {
                                file = fopen(game_filename, "r");
                                if (file == NULL) {
                                        fprintf(stderr, "error opening game file %s: ", game_filename);
                                        perror("fopen");
                                        exit(EX_IOERR);
                                }
                        }

                        while (!feof(file)) pos += fread(&buf + pos, sizeof(char), BUFSIZE - pos, file);
                        buf[pos] = '\0';
                        parse(buf);

                        if (player == NULL) {
                                std::cerr << "warning: no player defined in game file; using default player." << std::endl;
                                player = new Player("default player");
                                ents.push_back(player);
                        }
                }
        }
}

void display() {
        switch (pass) {
                case PASS_BLUR:
                        glViewport(0, 0, BLUR_TEXTURE_SIZE, BLUR_TEXTURE_SIZE);
                        glClearColor(0.0, 0.0, 0.0, 0.0);
                        break;
                case PASS_LAST:
                        glViewport(0, 0, ww, wh);
                        glClearColor(0.0, 0.0, 0.0, 1.0);
                        break;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, aspectratio, znear, zfar);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

/*
        glPushMatrix();
                //glLoadIdentity();
                glRasterPos3f(0, 0, 10);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'h');
        glPopMatrix();
*/

        switch (pass) {
                case PASS_BLUR:
#ifndef NO_LIGHTING
                        glEnable(GL_LIGHTING);
#endif
                        for (i = 0; i < 8; i++) {
                                glDisable(GL_LIGHT0 + i);
                        }
                        break;
                case PASS_LAST:
#ifndef NO_LIGHTING
                        glEnable(GL_LIGHTING);
#endif
                        for (i = 0; i < 8; i++) {
                                glDisable(GL_LIGHT0 + i);
                        }
                        break;
        }

        if (pass == PASS_LAST) {
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                switch (level) {
                        case LEVEL_DESERT:
                                glBindTexture(GL_TEXTURE_2D, tdesert);
                                break;
                        case LEVEL_SKY:
                                glBindTexture(GL_TEXTURE_2D, tcielo);
                                break;
                        case LEVEL_SPACE:
                                glBindTexture(GL_TEXTURE_2D, tstars);
                                break;
                }
                glEnable(GL_TEXTURE_2D);
                glPushMatrix();
                        glRotatef(cam_rotx, 1, 0, 0);
                        glRotatef(cam_roty, 0, 1, 0);
                        glRotatef((level == LEVEL_SKY ? 1 : -1)*90, 1, 0, 0);
                        glCallList(cielo);
                glPopMatrix();
                glDisable(GL_TEXTURE_2D);
        }

        glPushMatrix();
                glRotatef(cam_rotx, 1.0, 0.0, 0.0);
                glRotatef(cam_roty, 0.0, 1.0, 0.0);
                glTranslatef(-cam_x, -cam_y, -cam_z);
                glRotatef(-90, 0, 1, 0);
                glRotatef(-90, 1, 0, 0);

                glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
                glEnable(GL_LIGHT0);

                if (pass == PASS_LAST) {
                        glPushMatrix();
                                glScalef(5, 5, 5);
                                glColor4ub(200, 200, 200, 255);
                                glCallList(checker);
                                glTranslatef(1, 0, 0);
                                glColor4ub(0, 0, 0, 255);
                                glCallList(checker);
                        glPopMatrix();
                }

                if (pass == PASS_LAST) {
                        for (i = 0; static_cast<unsigned int>(i) < ents.size(); i++) {
                                glPushMatrix();
                                        glTranslatef(ents[i]->pos.x, ents[i]->pos.y, ents[i]->pos.z);
                                        glRotatef((ents[i]->ang * 180.0)/M_PI, 0, 0, 1);
                                        ents[i]->draw();
                                glPopMatrix();
                        }

                        if (mesh) {
                                //Triple pos = Triple(0, 0, 0);
                                glPushMatrix();
                                        glColor4ub(255, 0, 255, 255);
                                        glTranslatef(0, 0, 0.5);
                                        for (int i = -60; i <= 40; i = i + 20) {
                                                for (int j = -40; j <= 20; j = j + 20) {
                                                glBegin(GL_LINE_LOOP);
                                                        glLineWidth(100.0);
                                                        glVertex3f(     i,      j, 0); //-60, -40, 0
                                                        glVertex3f(     i, j + 20, 0); //-60, -20, 0
                                                        glVertex3f(i + 20,      j, 0); //-40, -40, 0
//                                                      pos = (Triple(i, j, 0) + Triple(i, j + 20, 0) + Triple(i + 20, j, 0))/3.0;
                                                glEnd();
//                                              glBegin(GL_POINTS);
//                                                      glVertex3f(pos.x, pos.y, 0);
//                                              glEnd();

                                                glBegin(GL_LINE_LOOP);
                                                        glLineWidth(100.0);
                                                        glVertex3f(i + 20, j + 20, 0); //-40, -20, 0
                                                        glVertex3f(i + 20, j     , 0); //-40, -40, 0
                                                        glVertex3f(i     , j + 20, 0); //-60, -20, 0
//                                                      pos = (Triple(i + 20, j + 20, 0) + Triple(i + 20, j, 0) + Triple(i, j + 20, 0))/3.0;
                                                glEnd();
//                                              glBegin(GL_POINTS);
//                                                      glVertex3f(pos.x, pos.y, 0);
//                                              glEnd();
                                                }
                                        }
                                        for (unsigned int i = 0; i < nodes.size(); i++) {
                                                for (unsigned int j = 0; j < nodes[i]->adj.size(); j++) {
                                                        glBegin(GL_LINES);
                                                                glVertex3f(nodes[i]->pos.x, nodes[i]->pos.y, 0);
//                                                              glVertex3f(get<0>(nodes[i]->adj[j])->pos.x, get<0>(nodes[i]->adj[j])->pos.y, 0);
                                                                glVertex3f(nodes[i]->adj[j]->pos.x, nodes[i]->adj[j]->pos.y, 0);
                                                        glEnd();
                                                }
                                                glPushMatrix();
                                                        glTranslatef(nodes[i]->pos.x, nodes[i]->pos.y, nodes[i]->pos.z);
                                                        nodes[i]->draw();
                                                glPopMatrix();
                                        }
                                glPopMatrix();
                        }
                }

                /* Balas del jugador */
                for (i = 0; i < N_PBALAS; i++) if (pb[i] && pbl[i] == level) {
                        glPushMatrix();
                                glTranslatef(pbx[i], pby[i], pbz[i]);
                                // TODO: usar solo dirección del cañón para mostrar la inclinación de la bala
                                glRotatef((-180.0*atan2(pbvx[i], pbvy[i]))/M_PI, 0, 0, 1);
                                glRotatef(( 180.0*atan2(pbvz[i], sqrt(pbvx[i]*pbvx[i] + pbvy[i]*pbvy[i])))/M_PI, 1, 0, 0);
                                glScalef(3.0, 7.0, 3.0);
                                switch (pass) {
                                        case PASS_BLUR:
#ifndef NO_LIGHTING
                                                glDisable(GL_LIGHTING);
#endif
                                                glColor4ub(255, 255, 255, 255);
                                                break;
                                        case PASS_LAST:
                                                //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                                                //glBindTexture(GL_TEXTURE_2D, tbrushmetal);
                                                //glEnable(GL_TEXTURE_2D);
                                                glColor4ub(70, 70, 70, 255);
                                                break;
                                }
                                glCallList(bala);
                                switch (pass) {
                                        case PASS_BLUR:
#ifndef NO_LIGHTING
                                                glEnable(GL_LIGHTING);
#endif
                                                break;
                                        case PASS_LAST:
                                                //glDisable(GL_TEXTURE_2D);
                                                break;
                                }
                        glPopMatrix();
                }

/*
                glPushMatrix();
                        double cosax, cosay, cosaz, cosavx, cosavy, cosavz;
                        double ncosax, ncosay, ncosaz, ncosavx, ncosavy, ncosavz;

                        cosax  = 0;
                        cosay  = mesh[MESH_CANNON].zM + 1;
                        cosaz  = 0;
                        ncosax = cosax;
                        ncosay = cosay * cos((a_cannon*M_PI)/180.0) - cosaz * sin((a_cannon*M_PI)/180.0);
                        ncosaz = cosay * sin((a_cannon*M_PI)/180.0) + cosaz * cos((a_cannon*M_PI)/180.0);
                        cosax  = ncosax;
                        cosay  = ncosay;
                        cosaz  = ncosaz;
                        cosax += 0;
                        cosay += CANNON_Z - TURRET_Z;
                        cosaz += CANNON_Y;
                        ncosax = cosax * cos((a_turret*M_PI)/180.0) - cosay * sin((a_turret*M_PI)/180.0);
                        ncosay = cosax * sin((a_turret*M_PI)/180.0) + cosay * cos((a_turret*M_PI)/180.0);
                        ncosaz = cosaz;
                        cosax  = ncosax;
                        cosay  = ncosay;
                        cosaz  = ncosaz;
                        cosax += 0;
                        cosay += TURRET_Z;
                        cosaz += 0;
                        ncosax = cosax * cos((prz*M_PI)/180.0) - cosay * sin((prz*M_PI)/180.0);
                        ncosay = cosax * sin((prz*M_PI)/180.0) + cosay * cos((prz*M_PI)/180.0);
                        ncosaz = cosaz;
                        cosax  = ncosax;
                        cosay  = ncosay;
                        cosaz  = ncosaz;
                        cosax += px;
                        cosay += py;
                        cosaz += pz;
                        cosavx = cosax;
                        cosavy = cosay;
                        cosavz = cosaz;

                        cosax  = 0;
                        cosay  = mesh[MESH_CANNON].zM;
                        cosaz  = 0;
                        ncosax = cosax;
                        ncosay = cosay * cos((a_cannon*M_PI)/180.0) - cosaz * sin((a_cannon*M_PI)/180.0);
                        ncosaz = cosay * sin((a_cannon*M_PI)/180.0) + cosaz * cos((a_cannon*M_PI)/180.0);
                        cosax  = ncosax;
                        cosay  = ncosay;
                        cosaz  = ncosaz;
                        cosax += 0;
                        cosay += CANNON_Z - TURRET_Z;
                        cosaz += CANNON_Y;
                        ncosax = cosax * cos((a_turret*M_PI)/180.0) - cosay * sin((a_turret*M_PI)/180.0);
                        ncosay = cosax * sin((a_turret*M_PI)/180.0) + cosay * cos((a_turret*M_PI)/180.0);
                        ncosaz = cosaz;
                        cosax  = ncosax;
                        cosay  = ncosay;
                        cosaz  = ncosaz;
                        cosax += 0;
                        cosay += TURRET_Z;
                        cosaz += 0;
                        ncosax = cosax * cos((prz*M_PI)/180.0) - cosay * sin((prz*M_PI)/180.0);
                        ncosay = cosax * sin((prz*M_PI)/180.0) + cosay * cos((prz*M_PI)/180.0);
                        ncosaz = cosaz;
                        cosax  = ncosax;
                        cosay  = ncosay;
                        cosaz  = ncosaz;
                        cosax += px;
                        cosay += py;
                        cosaz += pz;
                        cosavx -= cosax;
                        cosavy -= cosay;
                        cosavz -= cosaz;

                        glLineWidth(3);
                        glColor4ub(255, 0, 0, 80);
#ifndef NO_LIGHTING
                        glDisable(GL_LIGHTING);
#endif
                        glBegin(GL_LINES);
                                glVertex3f(cosax, cosay, cosaz);
                                glVertex3f(cosax+600*cosavx, cosay+600*cosavy, cosaz+600*cosavz);
                        glEnd();
#ifndef NO_LIGHTING
                        glEnable(GL_LIGHTING);
#endif
                        glTranslatef(cosax, cosay, cosaz);
                        glRotatef((-180.0*atan2(cosavx, cosavy))/M_PI, 0, 0, 1);
                        glRotatef(( 180.0*atan(cosavz/sqrt(cosavx*cosavx + cosavy*cosavy)))/M_PI, 1, 0, 0);
                        glScalef(0.3, 1.0, 0.3);
                        glColor4ub(255, 255, 255, 255);
                        glCallList(bala);
                glPopMatrix();
*/

                glDisable(GL_CULL_FACE);
#ifndef NO_LIGHTING
                glDisable(GL_LIGHTING);
#endif
                if (pass == PASS_LAST) for (i = 0; i < N_BOOM_SETS; i++) {
                        if (boom[i].on > 0 && boom[i].level == level) {
                                for (k = 0; k < N_BOOMS; k++) {
                                        glPushMatrix();
                                                glTranslatef(boom[i].x[k], boom[i].y[k], boom[i].z[k]);
                                                glScalef(3 * boom[i].s[k], 3 * boom[i].s[k], 3 * boom[i].s[k]);
                                                glRotatef(boom[i].a[k], boom[i].rx[k], boom[i].ry[k], boom[i].rz[k]);
                                                glBegin(GL_TRIANGLES);
                                                        glColor4ub(boom[i].r[k], boom[i].g[k], boom[i].b[k], 255 * ((double)boom[i].on) / ((double)T_BOOM));
                                                        glVertex3f(-0.5, -0.5, 0);
                                                        glVertex3f( 0.5, -0.5, 0);
                                                        glVertex3f( 0  ,  0.5, 0);
                                                glEnd();
                                        glPopMatrix();
                                }
                        }
                }

                if (pass == PASS_BLUR) for (i = 0; i < N_BOOM_SETS; i++) {
                        if (boom[i].on > 0 && boom[i].level == level) {
                                for (k = 0; k < N_BOOMS; k++) {
                                        glPushMatrix();
                                                glTranslatef(boom[i].x[k], boom[i].y[k], boom[i].z[k]);
                                                glScalef(3 * boom[i].s[k], 3 * boom[i].s[k], 3 * boom[i].s[k]);
                                                glRotatef(boom[i].a[k], boom[i].rx[k], boom[i].ry[k], boom[i].rz[k]);
                                                glBegin(GL_TRIANGLES);
                                                        glColor4ub(boom[i].r[k] * ((double)boom[i].on) / ((double)T_BOOM), boom[i].g[k] * ((double)boom[i].on) / ((double)T_BOOM), boom[i].b[k] * ((double)boom[i].on) / ((double)T_BOOM), 255);
//                                                      glColor4ub(255, 255, 255, ((boom[i].r[k] + boom[i].g[k] + boom[i].b[k])/3.0) * ((double)boom[i].on) / ((double)T_BOOM));
                                                        glVertex3f(-0.5, -0.5, 0);
                                                        glVertex3f( 0.5, -0.5, 0);
                                                        glVertex3f( 0  ,  0.5, 0);
                                                glEnd();
                                        glPopMatrix();
                                }
                        }
                }
#ifndef NO_LIGHTING
                glEnable(GL_LIGHTING);
#endif
                glEnable(GL_CULL_FACE);

        glPopMatrix();

        if (pass == PASS_LAST) {
                /* HUD */
#ifndef NO_LIGHTING
                glDisable(GL_LIGHTING);
#endif

                if (blur) {
                        glMatrixMode(GL_PROJECTION);
                        glLoadIdentity();
                        glOrtho(0, 1, 0, 1, -1, 1);

                        glDisable(GL_DEPTH_TEST);
                        glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                        glBindTexture(GL_TEXTURE_2D, tblur);
                        glEnable(GL_TEXTURE_2D);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                        glPushMatrix();
                                glTranslatef(0.5 - D_BLUR/2, 0.5 - D_BLUR/2, -1);
                                for (i = 0; i < N_BLURS; i++) {
                                        glTranslatef(D_BLUR/N_BLURS, 0, 0);
                                        for (j = 0; j < N_BLURS; j++) {
                                                glTranslatef(0, D_BLUR/N_BLURS, 0);
                                                glPushMatrix();
                                                        glScalef(1.0 + D_BLUR, 1.0 + D_BLUR, 1);
                                                        glColor4f(1, 1, 1, (12.0/(N_BLURS*N_BLURS))*(sqrtf(0.5) - sqrtf((((double)i)/N_BLURS - 0.5)*(((double)i)/N_BLURS - 0.5) + (((double)j)/N_BLURS - 0.5)*(((double)j)/N_BLURS - 0.5))));
                                                        glCallList(cuadrado_simple);
                                                glPopMatrix();
                                        }
                                        glTranslatef(0, -D_BLUR, 0);
                                }
                        glPopMatrix();
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                        glDisable(GL_TEXTURE_2D);
                        glEnable(GL_DEPTH_TEST);
                }

                glClear(GL_DEPTH_BUFFER_BIT);

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                if (ww <= wh) {
                        glOrtho(-10.0, 10.0, -10.0 / aspectratio, 10.0 / aspectratio, 1.0, -1.0);
                } else {
                        glOrtho(-10.0 * aspectratio, 10.0 * aspectratio, -10.0, 10.0, 1.0, -1.0);
                }

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                /* Score */
                for (i = 0; i < DIGITS_SCORE; i++) {
                        glPushMatrix();
                                glTranslatef(0, 9.2, 0);
                                glScalef(0.1, 0.1, 0.1);
                                glTranslatef((((DIGITS_SCORE + 1) / 2.0) - i - 0.5) * (W_SEGMENT + 4.0 * W_SEGMENT_T), 0, 0);
                                glCallList(segs[(abs(pts) / power(10, i)) % 10]);
                        glPopMatrix();
                }

                /* Vidas */
/*
                for (i = 0; i < lives - 1; i++) {
                        glPushMatrix();
                                glTranslatef(-12.25 + 2.1 * i, 8.5, 0);
                                glScalef(0.5, 0.5, 0.5);
                                glCallList(tanque);
                        glPopMatrix();
                }
 */

                //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                //glBindTexture(GL_TEXTURE_2D, tbrushmetal);
                //glEnable(GL_TEXTURE_2D);
                for (i = 0; i < balas; i++) {
                        glPushMatrix();
                                glTranslatef(-12.25 + 0.8 * i, 8.5, 0);
                                glScalef(1, 2, 1);
                                glColor4ub(255, 255, 255, 255);
                                glCallList(bala);
                        glPopMatrix();
                }
                //glDisable(GL_TEXTURE_2D);
        }

        switch (pass) {
                case PASS_BLUR:
                        glBindTexture(GL_TEXTURE_2D, tblur);
                        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, BLUR_TEXTURE_SIZE, BLUR_TEXTURE_SIZE, 0);
                        pass = PASS_LAST;
                        break;
                case PASS_LAST:
                        pass = PASS_BLUR;
                        break;
        }
}

void realDisplay() {
        if (blur) {
                pass = FIRST_PASS;
                do display();
                while (pass != FIRST_PASS);
        } else {
                pass = PASS_LAST;
                display();
        }
        glutSwapBuffers();
}

void reshape(int w, int h){
        if (h == 0) h = 1;
        ww = w;
        wh = h;
        aspectratio = ((double)w)/((double)h);
        glViewport(0, 0, w, h);
}

void skeydown(int key, int mx, int my) {
        if      (key == GLUT_KEY_LEFT)  keystate_l = true;
        else if (key == GLUT_KEY_RIGHT) keystate_r = true;
        else if (key == GLUT_KEY_UP)    keystate_u = true;
        else if (key == GLUT_KEY_DOWN)  keystate_d = true;
        else if (key == GLUT_KEY_F2)    initJuego();
}

void skeyup(int key, int mx, int my) {
        if      (key == GLUT_KEY_LEFT)  keystate_l = false;
        else if (key == GLUT_KEY_RIGHT) keystate_r = false;
        else if (key == GLUT_KEY_UP)    keystate_u = false;
        else if (key == GLUT_KEY_DOWN)  keystate_d = false;
}

void keyup(unsigned char key, int mx, int my) {
        if      (key == key_fwd         ) keystate_fwd          = player->control_f     = false;
        else if (key == key_back        ) keystate_back         = player->control_b     = false;
        else if (key == key_left        ) keystate_left         = player->control_rot_l = false;
        else if (key == key_right       ) keystate_right        = player->control_rot_r = false;
        else if (key == key_cam_up      ) keystate_cam_up       = false;
        else if (key == key_cam_down    ) keystate_cam_down     = false;
        else if (key == key_cam_left    ) keystate_cam_left     = false;
        else if (key == key_cam_right   ) keystate_cam_right    = false;
        else if (key == key_cam_fwd     ) keystate_cam_fwd      = false;
        else if (key == key_cam_back    ) keystate_cam_back     = false;
        else if (key == key_cam_rotup   ) keystate_cam_rotup    = false;
        else if (key == key_cam_rotdown ) keystate_cam_rotdown  = false;
        else if (key == key_cam_rotleft ) keystate_cam_rotleft  = false;
        else if (key == key_cam_rotright) keystate_cam_rotright = false;
        else if (key == key_enter       ) keystate_enter        = false;
        else if (key == key_shoot       ) keystate_shoot        = player->control_shoot = false;
        else if (key == key_reload      ) keystate_reload       = false;
        else if (key == key_jump        ) keystate_jump         = player->control_jump  = false;
}

void keydown(unsigned char key, int mx, int my) {
        if      (key == key_fwd         ) keystate_fwd          = player->control_f     = true;
        else if (key == key_back        ) keystate_back         = player->control_b     = true;
        else if (key == key_left        ) keystate_left         = player->control_rot_l = true;
        else if (key == key_right       ) keystate_right        = player->control_rot_r = true;
        else if (key == key_cam_up      ) keystate_cam_up       = true;
        else if (key == key_cam_down    ) keystate_cam_down     = true;
        else if (key == key_cam_left    ) keystate_cam_left     = true;
        else if (key == key_cam_right   ) keystate_cam_right    = true;
        else if (key == key_cam_fwd     ) keystate_cam_fwd      = true;
        else if (key == key_cam_back    ) keystate_cam_back     = true;
        else if (key == key_cam_rotup   ) keystate_cam_rotup    = true;
        else if (key == key_cam_rotdown ) keystate_cam_rotdown  = true;
        else if (key == key_cam_rotleft ) keystate_cam_rotleft  = true;
        else if (key == key_cam_rotright) keystate_cam_rotright = true;
        else if (key == key_enter       ) keystate_enter        = true;
        else if (key == key_shoot       ) keystate_shoot        = player->control_shoot = true;
        else if (key == key_reload      ) keystate_reload       = true;
        else if (key == key_jump        ) keystate_jump         = player->control_jump  = true;
        else if (key == key_mesh) mesh ^= 1;
        else if (key == key_pause) {
                frozen ^= 1;
#ifdef DEBUG_MAIN
                std::cout << "toggling pause" << std::endl;
#endif
        }
        else if (key == key_cam_switch) {
                if ((cam += 1) >= N_CAMS) cam = 0;
#ifdef DEBUG_MAIN
                switch (cam) {
                        case CAM_STATIC_OVERHEAD:
                                printf("cam is now static overhead\n");
                                break;
                        case CAM_OVERHEAD:
                                printf("cam is now overhead\n");
                                break;
                        case CAM_FPS:
                                printf("cam is now fps\n");
                                break;
                        case CAM_TPS:
                                printf("cam is now tps\n");
                                break;
                        case CAM_MANUAL:
                                printf("cam is now manual\n");
                                break;
                }
#endif
                cam_old_x    = cam_x;
                cam_old_y    = cam_y;
                cam_old_z    = cam_z;
                cam_old_rotx = cam_rotx;
                cam_old_roty = cam_roty;
                cam_old_t    = T_CAM_OLD;
                cam_old_adj  = true;
        }
        else if (key == 27) exit(EX_OK);
}

void juego(int v) {
        new_time = glutGet(GLUT_ELAPSED_TIME);
        delta = new_time - old_time;
        old_time = new_time;
        deltas_sum += delta - deltas[deltas_cur];
        deltas[deltas_cur] = delta;
        deltas_cur = (deltas_cur + 1) % N_DELTAS;

        if (!frozen) {
/*
                if (keystate_u) if ((a_cannon += delta / 20.0) > MAX_A_CANNON) a_cannon = MAX_A_CANNON;
                if (keystate_d) if ((a_cannon -= delta / 20.0) < MIN_A_CANNON) a_cannon = MIN_A_CANNON;
                if (keystate_l) if ((a_turret += delta / 20.0) > MAX_A_TURRET) a_turret = MAX_A_TURRET;
                if (keystate_r) if ((a_turret -= delta / 20.0) < MIN_A_TURRET) a_turret = MIN_A_TURRET;
 */

                if (keystate_jump && pz == 0 && pvz == 0) {
                        pvz = 0.04;
                }

                if (keystate_reload && balas < BALAS) {
                        // TODO: limit ammo
                        balas = BALAS;
                }

                if (pz != 0 || pvz != 0) {
                        pvz += GRAVEDAD * delta;
                        px  += pvx * delta;
                        py  += pvy * delta;
                        pz  += pvz * delta;
                        if (pz <= 0) {
                                pz  = 0;
                                pvz = 0;
                        }
                } else {
                        if (keystate_fwd)   pv   += delta / 20000.0;
                        if (keystate_back)  pv   -= delta / 20000.0;
                        if (keystate_left)  pvrz += delta / 2500.0;
                        if (keystate_right) pvrz -= delta / 2500.0;
//                      pv += -0.005 * pv * delta;
                        if (!keystate_fwd && !keystate_back && fabs(pv) < 0.01) pv = 0;
                        pvrz += -0.005 * pvrz * delta;
                        prz  += (pv < 0 ? -1 : 1) * pvrz * delta;
                        prz  -= (((int)prz)/360)*360;
                        pvx   = pv * cos((prz*M_PI)/180.0);
                        pvy   = pv * sin((prz*M_PI)/180.0);
                        pvx  += -0.002 * pvx * delta;
                        pvy  += -0.002 * pvy * delta;
                        pv    = sqrt(pvx*pvx + pvy*pvy) * (pv > 0 ? 1 : -1);
//                      pvz  += -0.005 * pvz * delta; // Roce vertical
                        px   += pvx * delta;
                        py   += pvy * delta;
                        pz   += pvz * delta;
                }

                player->pos  = Triple(px , py , pz );
                player->vel  = Triple(pvx, pvy, pvz);
                player->ang  = mapToRange((prz  * M_PI) / 180.0);
                player->vrot = (pvrz * M_PI) / 180.0;

                for (i = 0; (unsigned int)i < ents.size(); i++) {
                        ents[i]->steer(new_time, delta);
                }
                for (i = 0; (unsigned int)i < ents.size(); i++) {
                        ents[i]->update();
                }

                if (pbn < N_PBALAS) {
                        if (keystate_enter && balas > 0 && retract == 1) {
                                double npbx, npby, npbz;
                                pbn++;
                                if ((++pbi) == N_PBALAS) pbi = 0;
                                pb[pbi]   = true;
                                pbl[pbi]  = level;

                                // TODO: optimize
                                pbx[pbi]  = 0.55;
                                pby[pbi]  = 0;
                                pbz[pbi]  = 0;
                                npbx = pbx[pbi] * cos((30.0*M_PI)/180.0) - pbz[pbi] * sin((30.0*M_PI)/180.0);
                                npby = pby[pbi];
                                npbz = pbx[pbi] * sin((30.0*M_PI)/180.0) + pbz[pbi] * cos((30.0*M_PI)/180.0);
                                pbx[pbi]  = npbx;
                                pby[pbi]  = npby;
                                pbz[pbi]  = npbz;
                                pbx[pbi] += 0;
                                pby[pbi] += 0;
                                pbz[pbi] += 0.5;
                                npbx = pbx[pbi] * cos(player->ang) - pby[pbi] * sin(player->ang);
                                npby = pbx[pbi] * sin(player->ang) + pby[pbi] * cos(player->ang);
                                npbz = pbz[pbi];
                                pbx[pbi]  = npbx;
                                pby[pbi]  = npby;
                                pbz[pbi]  = npbz;
                                pbx[pbi] += player->pos.x;
                                pby[pbi] += player->pos.y;
                                pbz[pbi] += player->pos.z;
                                pbvx[pbi] = pbx[pbi];
                                pbvy[pbi] = pby[pbi];
                                pbvz[pbi] = pbz[pbi];

                                pbx[pbi]  = 0.50;
                                pby[pbi]  = 0;
                                pbz[pbi]  = 0;
                                npbx = pbx[pbi] * cos((30.0*M_PI)/180.0) - pbz[pbi] * sin((30.0*M_PI)/180.0);
                                npby = pby[pbi];
                                npbz = pbx[pbi] * sin((30.0*M_PI)/180.0) + pbz[pbi] * cos((30.0*M_PI)/180.0);
                                pbx[pbi]  = npbx;
                                pby[pbi]  = npby;
                                pbz[pbi]  = npbz;
                                pbx[pbi] += 0;
                                pby[pbi] += 0;
                                pbz[pbi] += 0.5;
                                npbx = pbx[pbi] * cos(player->ang) - pby[pbi] * sin(player->ang);
                                npby = pbx[pbi] * sin(player->ang) + pby[pbi] * cos(player->ang);
                                npbz = pbz[pbi];
                                pbx[pbi]  = npbx;
                                pby[pbi]  = npby;
                                pbz[pbi]  = npbz;
                                pbx[pbi] += player->pos.x;
                                pby[pbi] += player->pos.y;
                                pbz[pbi] += player->pos.z;
                                pbvx[pbi] += player->vel.x - pbx[pbi];
                                pbvy[pbi] += player->vel.y - pby[pbi];
                                pbvz[pbi] += player->vel.z - pbz[pbi];
                                retract = 0;
                                balas--;

                                boom[nboom].on = 1000;
                                for (k = 0; k < N_BOOMS; k++) {
                                        boom[nboom].x[k]  = pbx[pbi];
                                        boom[nboom].y[k]  = pby[pbi];
                                        boom[nboom].z[k]  = pbz[pbi];
                                        boom[nboom].a[k]  =                                                                                         ((double)rand())/((double)RAND_MAX)  * 180.0     ;
                                        boom[nboom].rx[k] =                                                                                   0.5 - ((double)rand())/((double)RAND_MAX)              ;
                                        boom[nboom].ry[k] =                                                                                   0.5 - ((double)rand())/((double)RAND_MAX)              ;
                                        boom[nboom].rz[k] =                                                                                   0.5 - ((double)rand())/((double)RAND_MAX)              ;
                                        boom[nboom].vx[k] = (pbx[pbi] <= -W_TABLERO/2.0 || W_TABLERO/2.0 <= pbx[pbi] ? -1 : 1) * pbvx[pbi] + (0.5 - ((double)rand())/((double)RAND_MAX)) * 0.01      ;
                                        boom[nboom].vy[k] = (pby[pbi] <= -H_TABLERO/2.0 || H_TABLERO/2.0 <= pby[pbi] ? -1 : 1) * pbvy[pbi] + (0.5 - ((double)rand())/((double)RAND_MAX)) * 0.01      ;
                                        boom[nboom].vz[k] = (pbz[pbi] <= 0                                           ? -1 : 1) * pbvz[pbi] + (0.5 - ((double)rand())/((double)RAND_MAX)) * 0.01      ;
                                        boom[nboom].va[k] =                                                                                   0.5 - ((double)rand())/((double)RAND_MAX)              ;
                                        boom[nboom].s[k]  =                                                                                         ((double)rand())/((double)RAND_MAX)  * BOOM_SCALE;
                                        boom[nboom].r[k]  = 120 + 120.0 * ((double)rand())/((double)RAND_MAX);
                                        boom[nboom].g[k]  = 120 + 120.0 * ((double)rand())/((double)RAND_MAX);
                                        boom[nboom].b[k]  =        60.0 * ((double)rand())/((double)RAND_MAX);
                                }
                                boom[nboom].level = level;
                                if ((++nboom) == N_BOOM_SETS) nboom = 0;
                        }
                }
                if ((retract += delta * 0.0025) > 1) retract = 1;

                for (i = 0; i < N_BOOM_SETS; i++) {
                        if (boom[i].on) {
                                if ((boom[i].on -= delta) < 0) boom[i].on = 0;
                                for (k = 0; k < N_BOOMS; k++) {
                                        boom[i].vz[k] += (GRAVEDAD/3.0) * delta;
                                        boom[i].x[k]  += boom[i].vx[k]  * delta;
                                        boom[i].y[k]  += boom[i].vy[k]  * delta;
                                        boom[i].z[k]  += boom[i].vz[k]  * delta;
                                        boom[i].a[k]  += boom[i].va[k]  * delta;
                                }
                        }
                }

                for (int q = 0; q < N_PBALAS; q++) if (pb[q]) {
                        pbvz[q] += delta * GRAVEDAD;
                        pbx[q]  += delta * pbvx[q] ;
                        pby[q]  += delta * pbvy[q] ;
                        pbz[q]  += delta * pbvz[q] ;
                        if (
//                              pbx[q] <= -W_TABLERO/2.0 || W_TABLERO/2.0 <= pbx[q] ||
//                              pby[q] <= -H_TABLERO/2.0 || H_TABLERO/2.0 <= pby[q] ||
                                pbz[q] <= 0
                            ) {
                                pb[q] = false;
                                pbn--;
                                boom[nboom].on = T_BOOM;
                                for (k = 0; k < N_BOOMS; k++) {
                                        boom[nboom].x[k]  = pbx[q];
                                        boom[nboom].y[k]  = pby[q];
                                        boom[nboom].z[k]  = pbz[q];
                                        boom[nboom].a[k]  =                                                                                          ((double)rand())/((double)RAND_MAX)  * 180.0;
                                        boom[nboom].rx[k] =                                                                                    0.5 - ((double)rand())/((double)RAND_MAX);
                                        boom[nboom].ry[k] =                                                                                    0.5 - ((double)rand())/((double)RAND_MAX);
                                        boom[nboom].rz[k] =                                                                                    0.5 - ((double)rand())/((double)RAND_MAX);
                                        boom[nboom].vx[k] = (pbx[q] <= -W_TABLERO/2.0 || W_TABLERO/2.0 <= pbx[q] ? -1 : 1) * pbvx[q] * 0.25 + (0.5 - ((double)rand())/((double)RAND_MAX)) * 0.01;
                                        boom[nboom].vy[k] = (pby[q] <= -H_TABLERO/2.0 || H_TABLERO/2.0 <= pby[q] ? -1 : 1) * pbvy[q] * 0.25 + (0.5 - ((double)rand())/((double)RAND_MAX)) * 0.01;
                                        boom[nboom].vz[k] = (pbz[q] <= 0                                         ? -1 : 1) * pbvz[q] * 0.25 + (0.5 - ((double)rand())/((double)RAND_MAX)) * 0.01;
                                        boom[nboom].va[k] = 0.5 - ((double)rand())/((double)RAND_MAX);
                                        boom[nboom].s[k]  = ((double)rand())/((double)RAND_MAX)*BOOM_SCALE;
                                        boom[nboom].r[k]  = 120 + 120.0 * ((double)rand())/((double)RAND_MAX);
                                        boom[nboom].g[k]  = 120 + 120.0 * ((double)rand())/((double)RAND_MAX);
                                        boom[nboom].b[k]  =        60.0 * ((double)rand())/((double)RAND_MAX);
                                }
                                boom[nboom].level = level;
                                if ((++nboom) == N_BOOM_SETS) nboom = 0;
                        }
                }

        }

        switch (cam) {
                case CAM_STATIC_OVERHEAD:
                        cam_x = 0;
                        cam_y = H_OVERHEAD;
                        cam_z = 0;
                        cam_rotx = 90;
                        cam_roty = 0;
                        break;

                case CAM_OVERHEAD:
                        cam_x = player->pos.y;
                        cam_y = H_OVERHEAD;
                        cam_z = player->pos.x;
                        cam_rotx = 90;
                        cam_roty = 0;
                        break;

                case CAM_FPS:
                        {
                                double ncam_x, ncam_y, ncam_z;
                                double cam_vx, cam_vy, cam_vz;
                                double ncam_vx, ncam_vy, ncam_vz;

                                cam_x  = 0;
                                cam_y  = -0.51;
                                cam_z  = 0;
                                ncam_x = cam_x * cos(player->ang) - cam_y * sin(player->ang);
                                ncam_y = cam_x * sin(player->ang) + cam_y * cos(player->ang);
                                ncam_z = cam_z;
                                cam_x  = ncam_x;
                                cam_y  = ncam_y;
                                cam_z  = ncam_z;
                                cam_x += player->pos.x;
                                cam_y += player->pos.y;
                                cam_z += player->pos.z;
                                cam_vx = cam_x;
                                cam_vy = cam_y;
                                cam_vz = cam_z;

                                ncam_vx = cam_vx - player->pos.x;
                                ncam_vy = cam_vy - player->pos.y;
                                ncam_vz = cam_vz - player->pos.z;
                                cam_vx = ncam_vy;
                                cam_vy = ncam_vz;
                                cam_vz = ncam_vx;
                                cam_x  = player->pos.y;
                                cam_y  = player->pos.z + 0.5;
                                cam_z  = player->pos.x;

                                cam_roty = (180.0*atan2(cam_vz, cam_vx))/M_PI;
                                cam_rotx = (-180.0*atan(cam_vy/sqrt(cam_vx*cam_vx + cam_vz*cam_vz)))/M_PI;
                        }
                        break;

                case CAM_TPS:
                        cam_x = player->pos.y - 12 * sin(player->ang);
                        cam_y = player->pos.z + 5;
                        cam_z = player->pos.x - 12 * cos(player->ang);

                        cam_roty = 180.0 - ((player->ang * 180.0)/M_PI);
                        cam_rotx = 10;
                        break;

                case CAM_MANUAL:
                        if (keystate_cam_up      ) cam_y    += delta / 100.0;
                        if (keystate_cam_down    ) cam_y    -= delta / 100.0;
                        if (keystate_cam_rotup   ) cam_rotx -= delta / 25.0;
                        if (keystate_cam_rotdown ) cam_rotx += delta / 25.0;
                        if (keystate_cam_rotleft ) cam_roty -= delta / 25.0;
                        if (keystate_cam_rotright) cam_roty += delta / 25.0;
                        if (keystate_cam_fwd) {
                                cam_x += (delta * sin((cam_roty * M_PI)/180.0)) / 100.0;
                                cam_y -= (delta * sin((cam_rotx * M_PI)/180.0)) / 100.0;
                                cam_z -= (delta * cos((cam_roty * M_PI)/180.0)) / 100.0;
                        }
                        if (keystate_cam_back) {
                                cam_x -= (delta * sin((cam_roty * M_PI)/180.0)) / 100.0;
                                cam_y += (delta * sin((cam_rotx * M_PI)/180.0)) / 100.0;
                                cam_z += (delta * cos((cam_roty * M_PI)/180.0)) / 100.0;
                        }
                        if (keystate_cam_left) {
                                cam_x -= (delta * cos((cam_roty * M_PI)/180.0)) / 100.0;
                                cam_z -= (delta * sin((cam_roty * M_PI)/180.0)) / 100.0;
                        }
                        if (keystate_cam_right) {
                                cam_x += (delta * cos((cam_roty * M_PI)/180.0)) / 100.0;
                                cam_z += (delta * sin((cam_roty * M_PI)/180.0)) / 100.0;
                        }
                        break;

                default:
                        break;
        }
        if (cam_old_t) {
                cam_old_t -= delta;
                if (cam_old_t < 0) {
                        cam_old_t = 0;
                } else {
                        if (cam_old_adj) {
                                cam_old_rotx += (((int)(cam_rotx - cam_old_rotx))/360)*360;
                                if ((cam_rotx - cam_old_rotx) > 180) cam_old_rotx += 360;
                                cam_old_roty += (((int)(cam_roty - cam_old_roty))/360)*360;
                                if ((cam_roty - cam_old_roty) > 180) cam_old_roty += 360;
                                cam_old_adj = false;
                        }
                        double t = ((double)(T_CAM_OLD - cam_old_t))/T_CAM_OLD;
                        t = t*t*(t - 2)*(t - 2);
                        cam_x    = cam_x    * t + cam_old_x    * (1 - t);
                        cam_y    = cam_y    * t + cam_old_y    * (1 - t);
                        cam_z    = cam_z    * t + cam_old_z    * (1 - t);
                        cam_rotx = cam_rotx * t + cam_old_rotx * (1 - t);
                        cam_roty = cam_roty * t + cam_old_roty * (1 - t);
                }
        }

        frame_delay = max_frame_delay - (deltas_sum / N_DELTAS);

        if ((cosa = (cosa + 1) % COSA) == 0) glutPostRedisplay();
        glutTimerFunc((frame_delay > 0) ? frame_delay / COSA : 0, juego, 0);
}

void initGL() {
#ifdef NO_LIGHTING
        glDisable(GL_LIGHTING);
#endif
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black4f);
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, 1);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER , 0);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE     , 1);

        glLightfv(GL_LIGHT0, GL_AMBIENT , black4f);
        glLightfv(GL_LIGHT0, GL_DIFFUSE , white4f);
        glLightfv(GL_LIGHT0, GL_SPECULAR, black4f);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF          , 180);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT        ,   0);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION ,   1);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION   ,   0);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,   0);
        glEnable(GL_LIGHT0);

/*
        glLightfv(GL_LIGHT1, GL_AMBIENT , black4f      );
        glLightfv(GL_LIGHT1, GL_SPECULAR, black4f      );
        glLightfv(GL_LIGHT1, GL_DIFFUSE , light_diffuse);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF          , 90);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT        , 20);

        glLightfv(GL_LIGHT2, GL_AMBIENT , black4f      );
        glLightfv(GL_LIGHT2, GL_SPECULAR, black4f      );
        glLightfv(GL_LIGHT2, GL_DIFFUSE , light_diffuse);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF          , 90);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT        , 20);

        for (i = MIN_BALA_LIGHT; i < 8; i++) {
                glLightfv(GL_LIGHT0 + i, GL_AMBIENT , black4f           );
                glLightfv(GL_LIGHT0 + i, GL_DIFFUSE , bala_light_diffuse);
                glLightfv(GL_LIGHT0 + i, GL_SPECULAR, bala_light_diffuse);
//              glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF          , 30);
//              glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT        ,  2);
                glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION ,  0);
                glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION   ,  1);
                glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION,  2);
        }
*/

        glEnable(GL_COLOR_MATERIAL);
        glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);
        glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
        glColor4ub(0, 0, 0, 255);
        glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
        glColor4ub(255, 255, 255, 255);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

/*
        GLfloat fog_color[4] = {0.8, 0.8, 0.8, 1.0};
        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, GL_EXP2);
        glFogi(GL_FOG_COORD_SRC, GL_FRAGMENT_DEPTH);
        glFogf(GL_FOG_START, 1.0);
        glFogf(GL_FOG_END, 30.0);
        glFogf(GL_FOG_DENSITY, 0.05);
        glFogfv(GL_FOG_COLOR, fog_color);
*/

        buildLists();
}

int main(int argc, char **argv) {
        glutInit(&argc, argv);
        glutInitWindowSize(ww, wh);
        glutInitDisplayMode(GLUT_RGBA      |
                            GLUT_DOUBLE    |
                            GLUT_ALPHA     |
                            GLUT_DEPTH     |
                            GLUT_LUMINANCE |
                            GLUT_MULTISAMPLE);
        glutCreateWindow("Pekomin");
        glutIgnoreKeyRepeat(1);

        {
                struct timeval t;

                if (gettimeofday(&t, NULL) == -1) {
                        perror("gettimeofday");
                        exit(EX_OSERR);
                }
                srand(t.tv_usec);
        }

        initGL();

        // TODO: use getopt, implement a decent set of command-line arguments; figure out how glutInit rapes argv
        if (argc == 2) {
                game_filename = argv[1];
                printf("%s\n", game_filename);
        } else {
                game_filename = NULL;
        }
        initJuego();

        blur = false;
        glutDisplayFunc(realDisplay);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keydown);
        glutKeyboardUpFunc(keyup);
        glutSpecialFunc(skeydown);
        glutSpecialUpFunc(skeyup);
        max_frame_delay = 1000.0/60.0;
        for (i = 0; i < N_DELTAS; i++) deltas[i] = 0;
        glutTimerFunc(max_frame_delay, juego, 0);
        old_time = glutGet(GLUT_ELAPSED_TIME);
        glutMainLoop();

        return EX_OK;
}
