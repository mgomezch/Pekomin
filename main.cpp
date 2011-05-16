#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sysexits.h>
#include <sys/time.h>
#include <GL/glut.h>

#include <vector>

#include "Behaviors.hpp"
#include "game.hpp"
#include "gl.hpp"
#include "RuntimePekomin.hpp"
#include "parse.hpp"
#include "Player.hpp"

#define DEBUG_MAIN

using namespace std;

#define N_DELTAS           50
#define COSA                3

enum cam_enum {
        CAM_OVERHEAD = 0,
        CAM_FPS,
        CAM_TPS,
        CAM_MANUAL
};
#define N_CAMS 4

int ww = 512;
int wh = 384;
int pass;

enum passes {
        PASS_BLUR = 0,
        PASS_LAST
};
#define FIRST_PASS PASS_BLUR
#define N_PASSES 2

int level;
enum levels {
        LEVEL_DESERT = 0,
        LEVEL_SKY,
        LEVEL_SPACE
};
#define START_LEVEL LEVEL_SPACE
#define N_LEVELS 3

GLfloat aspectratio = 4.0/3.0;
GLfloat fov         =    60.0;
GLfloat znear       =    0.01;
GLfloat zfar        =  1000.0;
GLfloat cam_x       =     0.0;
GLfloat cam_y       =     0.0;
GLfloat cam_z       =     0.0;
GLfloat cam_rotx    =     0.0;
GLfloat cam_roty    =     0.0;

GLfloat cam_old_x;
GLfloat cam_old_y;
GLfloat cam_old_z;
GLfloat cam_old_rotx;
GLfloat cam_old_roty;
int cam_old_t;
int cam_old_adj;
float retract;

int key_fwd          =  'w';
int key_back         =  's';
int key_left         =  'a';
int key_right        =  'd';
int key_cam_up       =  'p';
int key_cam_down     =  ';';
int key_cam_left     =  'j';
int key_cam_right    =  'l';
int key_cam_fwd      =  'i';
int key_cam_back     =  'k';
int key_cam_rotup    =  'y';
int key_cam_rotdown  =  'h';
int key_cam_rotleft  =  'u';
int key_cam_rotright =  'o';
int key_cam_switch   = '\t';
int key_shoot        =  ' ';
int key_enter        =   13;

int keystate_fwd          = 0;
int keystate_back         = 0;
int keystate_left         = 0;
int keystate_right        = 0;
int keystate_cam_up       = 0;
int keystate_cam_down     = 0;
int keystate_cam_left     = 0;
int keystate_cam_right    = 0;
int keystate_cam_fwd      = 0;
int keystate_cam_back     = 0;
int keystate_cam_rotup    = 0;
int keystate_cam_rotdown  = 0;
int keystate_cam_rotleft  = 0;
int keystate_cam_rotright = 0;
int keystate_shoot        = 0;
int keystate_enter        = 0;
int keystate_l            = 0;
int keystate_r            = 0;
int keystate_u            = 0;
int keystate_d            = 0;

int cosa = 0;
int cam = 0;
int blur = 0;

int deltas[N_DELTAS];
int deltas_cur = 0;
int deltas_sum = 0;
unsigned int delta;
int delay = 0;
int new_time;
int old_time;
float max_frame_delay;
float frame_delay;
int frozen;
int old_cam;

struct boom_data {
        float  x[N_BOOMS];
        float  y[N_BOOMS];
        float  z[N_BOOMS];
        float rx[N_BOOMS];
        float ry[N_BOOMS];
        float rz[N_BOOMS];
        float  a[N_BOOMS];
        float  s[N_BOOMS];
        float vx[N_BOOMS];
        float vy[N_BOOMS];
        float vz[N_BOOMS];
        float va[N_BOOMS];
        float  r[N_BOOMS];
        float  g[N_BOOMS];
        float  b[N_BOOMS];
        int on;
        int level;
} boom[N_BOOM_SETS];
int nboom;

float px, py, pz, prz, pv, pvx, pvy, pvz, pvrz, pa, pav;
int pb[N_PBALAS];
int pbl[N_PBALAS];
float pbx[N_PBALAS], pby[N_PBALAS], pbz[N_PBALAS], pbvx[N_PBALAS], pbvy[N_PBALAS], pbvz[N_PBALAS];
float pbv[N_PBALAS];
int pbi, pbn;
int pts;
int i, j, k;
int lives;
int balas;

Player *player;
vector<Ent *> ents;

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
        frozen     = 0;
        level      = START_LEVEL;
        cam_old_t  = 0;
        retract    = 1;

        px       = 0;
        py       = 0;
        pz       = 0;
        pv       = 0;
        prz      = 0;
        pvx      = 0;
        pvy      = 0;
        pvz      = 0;
        pvrz     = 0;
        pa       = 0;
        pav      = 0;
        pbi      = 0;
        pbn      = 0;
        for (i = 0; i < N_PBALAS; i++) {
                pb[i] = 0;
                pbv[i] = V_BALA_MAX;
        }
        pts   = 0;
        balas = BALAS;

        {
                Ent            *e;
                Behavior       *b;
                RuntimePekomin *p;

                while (!ents.empty()) {
                        e = ents.back();
                        ents.pop_back();
                        if ((p = dynamic_cast<RuntimePekomin *>(e)) != NULL) {
                                while (!p->behaviors.empty()) {
                                        b = p->behaviors.back();
                                        p->behaviors.pop_back();
                                        delete b;
                                }
                        }
                        delete e;
                }

                player = new Player();
                ents.push_back(player);

                p = new RuntimePekomin(Triple(10, 10, 0), 0);
//              p->addBehavior(new Seek(p, player, 0.01));
//              p->addBehavior(new Seek(p, player, 0.05));
                p->addBehavior(new Arrive(p, player, 0.01, 0.01, 5, 10));

                ents.push_back(p);
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
                        glEnable(GL_LIGHTING);
                        for (i = 0; i < 8; i++) {
                                glDisable(GL_LIGHT0 + i);
                        }
                        break;
                case PASS_LAST:
                        glEnable(GL_LIGHTING);
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
//                              glDisable(GL_LIGHTING);
                                glColor4ub(200, 200, 200, 255);
                                glCallList(checker);
                                glTranslatef(1, 0, 0);
                                glColor4ub(0, 0, 0, 255);
                                glCallList(checker);
//                              glEnable(GL_LIGHTING);
                        glPopMatrix();
                }

                if (pass == PASS_LAST) {
//                      glDisable(GL_LIGHTING);
                        for (i = 0; (unsigned int)i < ents.size(); i++) {
                                glPushMatrix();
                                        glTranslatef(ents[i]->pos.x, ents[i]->pos.y, ents[i]->pos.z);
                                        glRotatef(ents[i]->ang, 0, 0, 1);
                                        ents[i]->draw();
                                glPopMatrix();
                        }
//                      glEnable(GL_LIGHTING);
                }

                /* Balas del jugador */
                for (i = 0; i < N_PBALAS; i++) if (pb[i] && pbl[i] == level) {
                        glPushMatrix();
                                glTranslatef(pbx[i], pby[i], pbz[i]);
                                // TODO: usar solo dirección del cañón para mostrar la inclinación de la bala
                                glRotatef((-180.0*atan2(pbvx[i], pbvy[i]))/M_PI, 0, 0, 1);
                                glRotatef(( 180.0*atan2(pbvz[i], sqrt(pbvx[i]*pbvx[i] + pbvy[i]*pbvy[i])))/M_PI, 1, 0, 0);
                                glScalef(0.6, 1.0, 0.6);
                                switch (pass) {
                                        case PASS_BLUR:
                                                glDisable(GL_LIGHTING);
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
                                                glEnable(GL_LIGHTING);
                                                break;
                                        case PASS_LAST:
                                                //glDisable(GL_TEXTURE_2D);
                                                break;
                                }
                        glPopMatrix();
                }

/*
                glPushMatrix();
                        float cosax, cosay, cosaz, cosavx, cosavy, cosavz;
                        float ncosax, ncosay, ncosaz, ncosavx, ncosavy, ncosavz;

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
                        glDisable(GL_LIGHTING);
                        glBegin(GL_LINES);
                                glVertex3f(cosax, cosay, cosaz);
                                glVertex3f(cosax+600*cosavx, cosay+600*cosavy, cosaz+600*cosavz);
                        glEnd();
                        glEnable(GL_LIGHTING);
                        glTranslatef(cosax, cosay, cosaz);
                        glRotatef((-180.0*atan2(cosavx, cosavy))/M_PI, 0, 0, 1);
                        glRotatef(( 180.0*atan(cosavz/sqrt(cosavx*cosavx + cosavy*cosavy)))/M_PI, 1, 0, 0);
                        glScalef(0.3, 1.0, 0.3);
                        glColor4ub(255, 255, 255, 255);
                        glCallList(bala);
                glPopMatrix();
*/

                glDisable(GL_CULL_FACE);
                glDisable(GL_LIGHTING);
                if (pass == PASS_LAST) for (i = 0; i < N_BOOM_SETS; i++) {
                        if (boom[i].on > 0 && boom[i].level == level) {
                                for (k = 0; k < N_BOOMS; k++) {
                                        glPushMatrix();
                                                glTranslatef(boom[i].x[k], boom[i].y[k], boom[i].z[k]);
                                                glScalef(3 * boom[i].s[k], 3 * boom[i].s[k], 3 * boom[i].s[k]);
                                                glRotatef(boom[i].a[k], boom[i].rx[k], boom[i].ry[k], boom[i].rz[k]);
                                                glBegin(GL_TRIANGLES);
                                                        glColor4ub(boom[i].r[k], boom[i].g[k], boom[i].b[k], 255 * ((float)boom[i].on) / ((float)T_BOOM));
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
                                                        glColor4ub(boom[i].r[k] * ((float)boom[i].on) / ((float)T_BOOM), boom[i].g[k] * ((float)boom[i].on) / ((float)T_BOOM), boom[i].b[k] * ((float)boom[i].on) / ((float)T_BOOM), 255);
//                                                      glColor4ub(255, 255, 255, ((boom[i].r[k] + boom[i].g[k] + boom[i].b[k])/3.0) * ((float)boom[i].on) / ((float)T_BOOM));
                                                        glVertex3f(-0.5, -0.5, 0);
                                                        glVertex3f( 0.5, -0.5, 0);
                                                        glVertex3f( 0  ,  0.5, 0);
                                                glEnd();
                                        glPopMatrix();
                                }
                        }
                }
                glEnable(GL_LIGHTING);
                glEnable(GL_CULL_FACE);

        glPopMatrix();

        if (pass == PASS_LAST) {
                /* HUD */
                glDisable(GL_LIGHTING);

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
                                                        glColor4f(1, 1, 1, (12.0/(N_BLURS*N_BLURS))*(sqrtf(0.5) - sqrtf((((float)i)/N_BLURS - 0.5)*(((float)i)/N_BLURS - 0.5) + (((float)j)/N_BLURS - 0.5)*(((float)j)/N_BLURS - 0.5))));
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
                if (ww<=wh) {
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
        aspectratio = ((float)w)/((float)h);
        glViewport(0, 0, w, h);
}

void skeydown(int key, int mx, int my) {
        if      (key == GLUT_KEY_LEFT)  keystate_l = 1;
        else if (key == GLUT_KEY_RIGHT) keystate_r = 1;
        else if (key == GLUT_KEY_UP)    keystate_u = 1;
        else if (key == GLUT_KEY_DOWN)  keystate_d = 1;
        else if (key == GLUT_KEY_F2)    initJuego();
}

void skeyup(int key, int mx, int my) {
        if      (key == GLUT_KEY_LEFT)  keystate_l = 0;
        else if (key == GLUT_KEY_RIGHT) keystate_r = 0;
        else if (key == GLUT_KEY_UP)    keystate_u = 0;
        else if (key == GLUT_KEY_DOWN)  keystate_d = 0;
}

void keyup(unsigned char key, int mx, int my) {
        if      (key == key_fwd)          keystate_fwd          = 0;
        else if (key == key_back)         keystate_back         = 0;
        else if (key == key_left)         keystate_left         = 0;
        else if (key == key_right)        keystate_right        = 0;
        else if (key == key_cam_up)       keystate_cam_up       = 0;
        else if (key == key_cam_down)     keystate_cam_down     = 0;
        else if (key == key_cam_left)     keystate_cam_left     = 0;
        else if (key == key_cam_right)    keystate_cam_right    = 0;
        else if (key == key_cam_fwd)      keystate_cam_fwd      = 0;
        else if (key == key_cam_back)     keystate_cam_back     = 0;
        else if (key == key_cam_rotup)    keystate_cam_rotup    = 0;
        else if (key == key_cam_rotdown)  keystate_cam_rotdown  = 0;
        else if (key == key_cam_rotleft)  keystate_cam_rotleft  = 0;
        else if (key == key_cam_rotright) keystate_cam_rotright = 0;
        else if (key == key_enter)        keystate_enter        = 0;
        else if (key == key_shoot)        keystate_shoot        = 0;
}

void keydown(unsigned char key, int mx, int my) {
        if      (key == key_fwd)          keystate_fwd          = 1;
        else if (key == key_back)         keystate_back         = 1;
        else if (key == key_left)         keystate_left         = 1;
        else if (key == key_right)        keystate_right        = 1;
        else if (key == key_cam_up)       keystate_cam_up       = 1;
        else if (key == key_cam_down)     keystate_cam_down     = 1;
        else if (key == key_cam_left)     keystate_cam_left     = 1;
        else if (key == key_cam_right)    keystate_cam_right    = 1;
        else if (key == key_cam_fwd)      keystate_cam_fwd      = 1;
        else if (key == key_cam_back)     keystate_cam_back     = 1;
        else if (key == key_cam_rotup)    keystate_cam_rotup    = 1;
        else if (key == key_cam_rotdown)  keystate_cam_rotdown  = 1;
        else if (key == key_cam_rotleft)  keystate_cam_rotleft  = 1;
        else if (key == key_cam_rotright) keystate_cam_rotright = 1;
        else if (key == key_enter)        keystate_enter        = 1;
        else if (key == key_shoot)        keystate_shoot        = 1;
        else if (key == key_cam_switch) {
                if ((cam += 1) >= N_CAMS) cam = 0;
#ifdef DEBUG_MAIN
                switch (cam) {
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
                cam_old_adj  = 1;
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
                if (keystate_l)     m_AntiVirus->setFlag('l', true); else m_AntiVirus->setFlag('l', false);
                if (keystate_r)     m_AntiVirus->setFlag('r', true); else m_AntiVirus->setFlag('r', false);
                if (keystate_shoot) m_AntiVirus->setFlag('m', true); else m_AntiVirus->setFlag('m', false);
                if (keystate_enter) m_AntiVirus->setFlag('s', true); else m_AntiVirus->setFlag('s', false);
                */
/*
                if (keystate_u) if ((a_cannon += delta / 20.0) > MAX_A_CANNON) a_cannon = MAX_A_CANNON;
                if (keystate_d) if ((a_cannon -= delta / 20.0) < MIN_A_CANNON) a_cannon = MIN_A_CANNON;
                if (keystate_l) if ((a_turret += delta / 20.0) > MAX_A_TURRET) a_turret = MAX_A_TURRET;
                if (keystate_r) if ((a_turret -= delta / 20.0) < MIN_A_TURRET) a_turret = MIN_A_TURRET;
 */
                if (keystate_fwd)   pv   += delta / 20000.0;
                if (keystate_back)  pv   -= delta / 20000.0;
                if (keystate_left)  pvrz += delta / 5000.0;
                if (keystate_right) pvrz -= delta / 5000.0;
                pv += -0.005 * pv * delta;
                if (!keystate_fwd && !keystate_back && fabs(pv) < 0.01) pv = 0;
                pvrz += -0.005 * pvrz * delta;
                prz += (pv < 0 ? -1 : 1) * pvrz * delta;
                prz -= (((int)prz)/360)*360;
                pvx = pv * sin((-prz*M_PI)/180.0);
                pvy = pv * cos((-prz*M_PI)/180.0);
/*
                pvx  += -0.005 * pvx  * delta;
                pvy  += -0.005 * pvy  * delta;
                pvz  += -0.005 * pvz  * delta; // Roce vertical; cambiar?
 */
                px += pvx * delta;
                py += pvy * delta;
                pz += pvz * delta;

                player->pos  = Triple(px , py , pz );
                player->vel  = Triple(pvx, pvy, pvz);
                player->ang  = prz;
                player->vrot = pvrz;

/*
                if (px < -(W_TABLERO - mesh[MESH_TANK].size_x)/2) {
                        px  = -(W_TABLERO - mesh[MESH_TANK].size_x)/2;
                        pvx = 0;
                }
                if (px >  (W_TABLERO - mesh[MESH_TANK].size_x)/2) {
                        px  =  (W_TABLERO - mesh[MESH_TANK].size_x)/2;
                        pvx = 0;
                }
                if (py < -(H_TABLERO - mesh[MESH_TANK].size_z)/2) {
                        py  = -(H_TABLERO - mesh[MESH_TANK].size_z)/2;
                        pvy = 0;
                }
                if (py >  (H_TABLERO - mesh[MESH_TANK].size_z)/2) {
                        py  =  (H_TABLERO - mesh[MESH_TANK].size_z)/2;
                        pvy = 0;
                }
 */
        }

        switch (cam) {
                case CAM_OVERHEAD:
                        cam_x = 0;
                        cam_y = H_OVERHEAD;
                        cam_z = 0;
                        cam_rotx = 90;
                        cam_roty = 0;
                        break;

                case CAM_FPS:
                        {
                                // TODO
                                /*
                                PDK_Vector3 mPos = m_AntiVirus->getActualMachine()->getPosition();
                                PDK_Vector3 pPos = m_AntiVirus->getPosition();
                                cam_x = pPos.y + 0.1 * (pPos.y - mPos.y);
                                cam_y = 1;
                                cam_z = pPos.x + 0.1 * (pPos.x - mPos.x);
                                cam_rotx = 15;
                                cam_roty = -(180.0*m_AntiVirus->getRads())/M_PI;
                                */
                        }
                        break;

                case CAM_TPS:
                        {
                                // TODO
                                /*
                                PDK_Vector3 mPos = m_AntiVirus->getActualMachine()->getPosition();
                                PDK_Vector3 pPos = m_AntiVirus->getPosition();
                                cam_x = mPos.y;
                                cam_y = 2 * m_AntiVirus->getActualMachine()->getRadius();;
                                cam_z = mPos.x;
                                cam_rotx = 90;
                                cam_roty = 0;
                                */
                        }
                        break;

                case CAM_MANUAL:
                        if (keystate_cam_up)       cam_y    += delta / 100.0;
                        if (keystate_cam_down)     cam_y    -= delta / 100.0;
                        if (keystate_cam_rotup)    cam_rotx -= delta / 25.0;
                        if (keystate_cam_rotdown)  cam_rotx += delta / 25.0;
                        if (keystate_cam_rotleft)  cam_roty -= delta / 25.0;
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
                                cam_old_adj = 0;
                        }
                        float t = ((float)(T_CAM_OLD - cam_old_t))/T_CAM_OLD;
                        t = t*t*(t - 2)*(t - 2);
                        cam_x    = cam_x    * t + cam_old_x    * (1 - t);
                        cam_y    = cam_y    * t + cam_old_y    * (1 - t);
                        cam_z    = cam_z    * t + cam_old_z    * (1 - t);
                        cam_rotx = cam_rotx * t + cam_old_rotx * (1 - t);
                        cam_roty = cam_roty * t + cam_old_roty * (1 - t);
                }
        }

        for (i = 0; (unsigned int)i < ents.size(); i++) {
                ents[i]->update(delta);
        }

        if (pbn < N_PBALAS) {
                if (!frozen && keystate_enter && balas > 0 && retract == 1) {
//                      float npbx, npby, npbz;
                        pbn++;
                        if ((++pbi) == N_PBALAS) pbi = 0;
                        pb[pbi]   = 1;
                        pbl[pbi]  = level;

                        // TODO: optimize
                        // TODO: velocidad inicial por rotación de tanque y turret
/*
                        pbx[pbi]  = 0;
                        pby[pbi]  = mesh[MESH_CANNON].zM + v_cannon;
                        pbz[pbi]  = 0;
                        npbx = pbx[pbi];
                        npby = pby[pbi] * cos((a_cannon*M_PI)/180.0) - pbz[pbi] * sin((a_cannon*M_PI)/180.0);
                        npbz = pby[pbi] * sin((a_cannon*M_PI)/180.0) + pbz[pbi] * cos((a_cannon*M_PI)/180.0);
                        pbx[pbi]  = npbx;
                        pby[pbi]  = npby;
                        pbz[pbi]  = npbz;
                        pbx[pbi] += 0;
                        pby[pbi] += CANNON_Z - TURRET_Z;
                        pbz[pbi] += CANNON_Y;
                        npbx = pbx[pbi] * cos((a_turret*M_PI)/180.0) - pby[pbi] * sin((a_turret*M_PI)/180.0);
                        npby = pbx[pbi] * sin((a_turret*M_PI)/180.0) + pby[pbi] * cos((a_turret*M_PI)/180.0);
                        npbz = pbz[pbi];
                        pbx[pbi]  = npbx;
                        pby[pbi]  = npby;
                        pbz[pbi]  = npbz;
                        pbx[pbi] += 0;
                        pby[pbi] += TURRET_Z;
                        pbz[pbi] += 0;
                        npbx = pbx[pbi] * cos((prz*M_PI)/180.0) - pby[pbi] * sin((prz*M_PI)/180.0);
                        npby = pbx[pbi] * sin((prz*M_PI)/180.0) + pby[pbi] * cos((prz*M_PI)/180.0);
                        npbz = pbz[pbi];
                        pbx[pbi]  = npbx;
                        pby[pbi]  = npby;
                        pbz[pbi]  = npbz;
                        pbx[pbi] += px;
                        pby[pbi] += py;
                        pbz[pbi] += pz;
                        pbvx[pbi] = pbx[pbi];
                        pbvy[pbi] = pby[pbi];
                        pbvz[pbi] = pbz[pbi];

                        pbx[pbi]  = 0;
                        pby[pbi]  = mesh[MESH_CANNON].zM;
                        pbz[pbi]  = 0;
                        npbx = pbx[pbi];
                        npby = pby[pbi] * cos((a_cannon*M_PI)/180.0) - pbz[pbi] * sin((a_cannon*M_PI)/180.0);
                        npbz = pby[pbi] * sin((a_cannon*M_PI)/180.0) + pbz[pbi] * cos((a_cannon*M_PI)/180.0);
                        pbx[pbi]  = npbx;
                        pby[pbi]  = npby;
                        pbz[pbi]  = npbz;
                        pbx[pbi] += 0;
                        pby[pbi] += CANNON_Z - TURRET_Z;
                        pbz[pbi] += CANNON_Y;
                        npbx = pbx[pbi] * cos((a_turret*M_PI)/180.0) - pby[pbi] * sin((a_turret*M_PI)/180.0);
                        npby = pbx[pbi] * sin((a_turret*M_PI)/180.0) + pby[pbi] * cos((a_turret*M_PI)/180.0);
                        npbz = pbz[pbi];
                        pbx[pbi]  = npbx;
                        pby[pbi]  = npby;
                        pbz[pbi]  = npbz;
                        pbx[pbi] += 0;
                        pby[pbi] += TURRET_Z;
                        pbz[pbi] += 0;
                        npbx = pbx[pbi] * cos((prz*M_PI)/180.0) - pby[pbi] * sin((prz*M_PI)/180.0);
                        npby = pbx[pbi] * sin((prz*M_PI)/180.0) + pby[pbi] * cos((prz*M_PI)/180.0);
                        npbz = pbz[pbi];
                        pbx[pbi]  = npbx;
                        pby[pbi]  = npby;
                        pbz[pbi]  = npbz;
                        pbx[pbi] += px;
                        pby[pbi] += py;
                        pbz[pbi] += pz;
                        pbvx[pbi] += pvx - pbx[pbi];
                        pbvy[pbi] += pvy - pby[pbi];
                        pbvz[pbi] += pvz - pbz[pbi];
 */
                        retract = 0;
                        balas--;

                        boom[nboom].on = 1000;
                        for (k = 0; k < N_BOOMS; k++) {
                                boom[nboom].x[k]  = pbx[pbi];
                                boom[nboom].y[k]  = pby[pbi];
                                boom[nboom].z[k]  = pbz[pbi];
                                boom[nboom].a[k]  =                                                                                                ((float)rand())/((float)RAND_MAX)  * 180.0;
                                boom[nboom].rx[k] =                                                                                          0.5 - ((float)rand())/((float)RAND_MAX);
                                boom[nboom].ry[k] =                                                                                          0.5 - ((float)rand())/((float)RAND_MAX);
                                boom[nboom].rz[k] =                                                                                          0.5 - ((float)rand())/((float)RAND_MAX);
                                boom[nboom].vx[k] = (pbx[pbi] <= -W_TABLERO/2.0 || W_TABLERO/2.0 <= pbx[pbi] ? -1 : 1) * pbvx[pbi] + (0.5 - ((float)rand())/((float)RAND_MAX)) * 0.01;
                                boom[nboom].vy[k] = (pby[pbi] <= -H_TABLERO/2.0 || H_TABLERO/2.0 <= pby[pbi] ? -1 : 1) * pbvy[pbi] + (0.5 - ((float)rand())/((float)RAND_MAX)) * 0.01;
                                boom[nboom].vz[k] = (pbz[pbi] <= 0                                           ? -1 : 1) * pbvz[pbi] + (0.5 - ((float)rand())/((float)RAND_MAX)) * 0.01;
                                boom[nboom].va[k] = 0.5 - ((float)rand())/((float)RAND_MAX);
                                boom[nboom].s[k]  = ((float)rand())/((float)RAND_MAX)*BOOM_SCALE;
                                boom[nboom].r[k]  = 120 + 120.0 * ((float)rand())/((float)RAND_MAX);
                                boom[nboom].g[k]  = 120 + 120.0 * ((float)rand())/((float)RAND_MAX);
                                boom[nboom].b[k]  =        60.0 * ((float)rand())/((float)RAND_MAX);
                        }
                        boom[nboom].level = level;
                        if ((++nboom) == N_BOOM_SETS) nboom = 0;
                }
        }
        if (!frozen && (retract += delta * 0.0025) > 1) retract = 1;

        for (i = 0; i < N_BOOM_SETS; i++) {
                if (boom[i].on) {
                        if ((boom[i].on -= delta) < 0) boom[i].on = 0;
                        for (k = 0; k < N_BOOMS; k++) {
                                boom[i].x[k]  += boom[i].vx[k] * delta;
                                boom[i].y[k]  += boom[i].vy[k] * delta;
                                boom[i].vz[k] += (GRAVEDAD/3.0) * delta;
                                boom[i].z[k]  += boom[i].vz[k] * delta;
                                boom[i].a[k]  += boom[i].va[k] * delta;
                        }
                }
        }

        for (int q = 0; q < N_PBALAS; q++) if (pb[q]) {
                pbvz[q] += delta * GRAVEDAD;
                pbx[q]  += delta * pbvx[q] / 15.0;
                pby[q]  += delta * pbvy[q] / 15.0;
                pbz[q]  += delta * pbvz[q];
                if (
                        pbx[q] <= -W_TABLERO/2.0 || W_TABLERO/2.0 <= pbx[q] ||
                        pby[q] <= -H_TABLERO/2.0 || H_TABLERO/2.0 <= pby[q] ||
                        pbz[q] <= 0
                    ) {
                        pb[q] = 0;
                        pbn--;
                        boom[nboom].on = T_BOOM;
                        for (k = 0; k < N_BOOMS; k++) {
                                boom[nboom].x[k]  = pbx[q];
                                boom[nboom].y[k]  = pby[q];
                                boom[nboom].z[k]  = pbz[q];
                                boom[nboom].a[k]  =                                                                                   ((float)rand())/((float)RAND_MAX)  * 180.0;
                                boom[nboom].rx[k] =                                                                             0.5 - ((float)rand())/((float)RAND_MAX);
                                boom[nboom].ry[k] =                                                                             0.5 - ((float)rand())/((float)RAND_MAX);
                                boom[nboom].rz[k] =                                                                             0.5 - ((float)rand())/((float)RAND_MAX);
                                boom[nboom].vx[k] = (pbx[q] <= -W_TABLERO/2.0 || W_TABLERO/2.0 <= pbx[q] ? -1 : 1) * pbvx[q] * 0.25 + (0.5 - ((float)rand())/((float)RAND_MAX)) * 0.01;
                                boom[nboom].vy[k] = (pby[q] <= -H_TABLERO/2.0 || H_TABLERO/2.0 <= pby[q] ? -1 : 1) * pbvy[q] * 0.25 + (0.5 - ((float)rand())/((float)RAND_MAX)) * 0.01;
                                boom[nboom].vz[k] = (pbz[q] <= 0                                         ? -1 : 1) * pbvz[q] * 0.25 + (0.5 - ((float)rand())/((float)RAND_MAX)) * 0.01;
                                boom[nboom].va[k] = 0.5 - ((float)rand())/((float)RAND_MAX);
                                boom[nboom].s[k]  = ((float)rand())/((float)RAND_MAX)*BOOM_SCALE;
                                boom[nboom].r[k]  = 120 + 120.0 * ((float)rand())/((float)RAND_MAX);
                                boom[nboom].g[k]  = 120 + 120.0 * ((float)rand())/((float)RAND_MAX);
                                boom[nboom].b[k]  =        60.0 * ((float)rand())/((float)RAND_MAX);
                        }
                        boom[nboom].level = level;
                        if ((++nboom) == N_BOOM_SETS) nboom = 0;
                }
        }

        frame_delay = max_frame_delay - (deltas_sum / N_DELTAS);

        if ((cosa = (cosa + 1) % COSA) == 0) glutPostRedisplay();
        glutTimerFunc((frame_delay > 0) ? frame_delay / COSA : 0, juego, 0);
}

void initGL() {
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
        initJuego();

        blur = 0;
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

