#ifndef GL_HPP
#define GL_HPP

#include <GL/glut.h>

#define N_SLICES_RINGBASE   6
#define N_SLICES           12
#define N_LOOPS             4
#define N_DIVS             10
#define N_DIVS_HD          30

extern int cuadrado,
           cuadrado_hd,
           cuadrado_simple,
           cubo,
           cubo_simple,
           teclado,
           checker,
           borde,
           light_cone,
           bala,
           segmento,
           barra,
           cielo;
#define N_LISTS 12

extern GLfloat black4f[4]      ;
extern GLfloat white4f[4]      ;

extern GLubyte color_ss_on[4]  ;
extern GLubyte color_ss_off[4] ;
extern GLubyte color_borde[4]  ;
extern GLubyte color_inicial[4];
extern GLubyte color_medio[4]  ;
extern GLubyte color_lleno[4]  ;
extern GLubyte color_empty[4]  ;
extern GLubyte color_wall[4]   ;
extern GLfloat light_pos[4]    ;

extern int ss[12][7];

extern int segs[12];

extern GLubyte *tstars_img ,
               *tdesert_img,
               *tcielo_img ;

extern GLuint tstars, tdesert, tcielo;
extern GLuint tblur;
extern int tw, th, ta;

int loadPNG(char *name, int *outWidth, int *outHeight, int *outHasAlpha, GLubyte **outData);

void buildLists();

#endif
