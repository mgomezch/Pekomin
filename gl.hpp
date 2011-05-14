#ifndef _GL_HPP
#define _GL_HPP

#include <GL/glut.h>

#define N_SLICES_RINGBASE   6
#define N_SLICES           12
#define N_LOOPS             4
#define N_DIVS             10
#define N_DIVS_HD          30

int cuadrado,
    cuadrado_hd,
    cuadrado_simple,
    cubo,
    cubo_simple,
    checker,
    borde,
    light_cone,
    bala,
    segmento,
    barra,
    cielo;
#define N_LISTS            12

GLfloat black4f[4]       = {0, 0, 0, 1};
GLfloat white4f[4]       = {1, 1, 1, 1};
GLubyte color_ss_on[4]   = {255,   0,   0, 160};
GLubyte color_ss_off[4]  = { 50,   0,   0, 160};
GLubyte color_borde[4]   = { 90,  60,  30, 255};
GLubyte color_inicial[4] = {124, 252,   0, 255};
GLubyte color_medio[4]   = {255, 235,   0, 255};
GLubyte color_lleno[4]   = {255,  0,   0,  255};
GLubyte color_empty[4]   = {139, 136, 120, 255};
GLubyte color_wall[4]    = { 90,  40,   0, 255};
/* GLfloat light_diffuse[4]      = {1, 1, 1, 1}; */

int ss[12][7] = {
        {1, 1, 1, 1, 1, 1, 0}, /* 0 */
        {0, 1, 1, 0, 0, 0, 0}, /* 1 */
        {1, 1, 0, 1, 1, 0, 1}, /* 2 */
        {1, 1, 1, 1, 0, 0, 1}, /* 3 */
        {0, 1, 1, 0, 0, 1, 1}, /* 4 */
        {1, 0, 1, 1, 0, 1, 1}, /* 5 */
        {1, 0, 1, 1, 1, 1, 1}, /* 6 */
        {1, 1, 1, 0, 0, 0, 0}, /* 7 */
        {1, 1, 1, 1, 1, 1, 1}, /* 8 */
        {1, 1, 1, 1, 0, 1, 1}, /* 9 */
        {0, 0, 0, 0, 0, 0, 1}, /* - */
        {0, 0, 0, 0, 0, 0, 0}  /*   */
};

int segs[12];

GLubyte *tstars_img, *tdesert_img, *tcielo_img;
GLuint   tstars,      tdesert,      tcielo;
GLuint   tblur;
int tw, th, ta;

int loadPNG(char *name, int *outWidth, int *outHeight, int *outHasAlpha, GLubyte **outData);

void buildLists();

#endif
