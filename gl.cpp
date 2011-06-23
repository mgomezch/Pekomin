#include <png.h>
#include <stdlib.h>
#include <sysexits.h>

#include "game.hpp"
#include "gl.hpp"

int cuadrado        = -1,
    cuadrado_hd     = -1,
    cuadrado_simple = -1,
    cubo            = -1,
    cubo_simple     = -1,
    checker         = -1,
    borde           = -1,
    light_cone      = -1,
    bala            = -1,
    segmento        = -1,
    barra           = -1,
    cielo           = -1;

GLfloat black4f[4]       = {0, 0, 0, 1};
GLfloat white4f[4]       = {1, 1, 1, 1};

GLubyte color_ss_on[4]   = {255,   0,   0, 160};
GLubyte color_ss_off[4]  = { 50,   0,   0, 160};
GLubyte color_borde[4]   = { 90,  60,  30, 255};
GLubyte color_inicial[4] = {124, 252,   0, 255};
GLubyte color_medio[4]   = {255, 235,   0, 255};
GLubyte color_lleno[4]   = {255,   0,   0, 255};
GLubyte color_empty[4]   = {139, 136, 120, 255};
GLubyte color_wall[4]    = { 90,  40,   0, 255};

GLfloat light_pos[4]     = {0, 0, H_LIGHT_TABLERO, 1};

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

GLubyte *tstars_img  = NULL,
        *tdesert_img = NULL,
        *tcielo_img  = NULL;

GLuint   tstars  = -1,
         tdesert = -1,
         tcielo  = -1;

GLuint   tblur = -1;

int tw = 0,
    th = 0,
    ta = 0;

int loadPNG(char *name, int *outWidth, int *outHeight, int *outHasAlpha, GLubyte **outData) {
        int i;
        png_structp png_ptr;
        png_infop info_ptr;
        unsigned int sig_read = 0;
        FILE *fp;

        if (outWidth == NULL || outHeight == NULL || outHasAlpha == NULL) return -1;
        if ((fp = fopen(name, "rb")) == NULL) return -1;

        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (png_ptr == NULL) {
                fclose(fp);
                return -1;
        }

        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == NULL) {
                fclose(fp);
                png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
                return -1;
        }

        if (setjmp(png_jmpbuf(png_ptr))) {
                png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
                fclose(fp);
                return -1;
        }

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, sig_read);

        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);

        *outWidth  = info_ptr->width;
        *outHeight = info_ptr->height;
        switch (info_ptr->color_type) {
                case PNG_COLOR_TYPE_RGBA:
                        *outHasAlpha = 1;
                        break;
                case PNG_COLOR_TYPE_RGB:
                        *outHasAlpha = 0;
                        break;
                default:
                        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
                        fclose(fp);
                        return false;
        }

        unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
        *outData = (unsigned char*) malloc(row_bytes * (*outHeight));
        png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
        for (i = 0; i < *outHeight; i++) {
                memcpy(*outData + (row_bytes*((*outHeight) - 1 - i)), row_pointers[i], row_bytes);
        }

        png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
        fclose(fp);

        return 1;
}

void buildLists() {
        int i, j, tw, th, ta;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(1, &tblur);
        glBindTexture(GL_TEXTURE_2D, tblur);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        {
                int size = 4 * BLUR_TEXTURE_SIZE * BLUR_TEXTURE_SIZE * sizeof(GLuint);
                GLuint *tblur_data = (GLuint *)malloc(size);
                memset(tblur_data, 0, size);
                glTexImage2D(GL_TEXTURE_2D, 0, 4, BLUR_TEXTURE_SIZE, BLUR_TEXTURE_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, tblur_data);
                free(tblur_data);
        }

        glGenTextures(1, &tstars);
        glBindTexture(GL_TEXTURE_2D, tstars);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        loadPNG((char *)"png/stars.png", &tw, &th, &ta, &tstars_img);
        glTexImage2D(GL_TEXTURE_2D, 0, ta ? 4 : 3, tw, th, 0, ta ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, tstars_img);

        glGenTextures(1, &tdesert);
        glBindTexture(GL_TEXTURE_2D, tdesert);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        loadPNG((char *)"png/desert.png", &tw, &th, &ta, &tdesert_img);
        glTexImage2D(GL_TEXTURE_2D, 0, ta ? 4 : 3, tw, th, 0, ta ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, tdesert_img);

        glGenTextures(1, &tcielo);
        glBindTexture(GL_TEXTURE_2D, tcielo);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        loadPNG((char *)"png/cielo.png", &tw, &th, &ta, &tcielo_img);
        glTexImage2D(GL_TEXTURE_2D, 0, ta ? 4 : 3, tw, th, 0, ta ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, tcielo_img);

        if ((cuadrado = glGenLists(N_LISTS + 12)) == 0) {
                fprintf(stderr, "error: glGenLists(%d) == 0\n", N_LISTS + 12);
                exit(EX_OSERR);
        }
        cuadrado_hd     = cuadrado +  1;
        cuadrado_simple = cuadrado +  2;
        cubo            = cuadrado +  3;
        cubo_simple     = cuadrado +  4;
        checker         = cuadrado +  5;
        borde           = cuadrado +  6;
        bala            = cuadrado +  7;
        segmento        = cuadrado +  8;
        barra           = cuadrado +  9;
        cielo           = cuadrado + 10;
        for (i = 0; i <= 11; i++) {
                segs[i] = cuadrado + N_LISTS + i;
        }

        glNewList(cuadrado, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                        glNormal3f(0, 0, 1);
                        for (i = 0; i < N_DIVS; i++) {
                                for (j = 0; j < N_DIVS; j++) {
                                        glTexCoord2f(       (((float)(i    ))/((float)N_DIVS)),        (((float)(j    ))/((float)N_DIVS))     );
                                          glVertex3f(-0.5 + (((float)(i    ))/((float)N_DIVS)), -0.5 + (((float)(j    ))/((float)N_DIVS)), 0.0);
                                        glTexCoord2f(       (((float)(i + 1))/((float)N_DIVS)),        (((float)(j    ))/((float)N_DIVS))     );
                                          glVertex3f(-0.5 + (((float)(i + 1))/((float)N_DIVS)), -0.5 + (((float)(j    ))/((float)N_DIVS)), 0.0);
                                        glTexCoord2f(       (((float)(i + 1))/((float)N_DIVS)),        (((float)(j + 1))/((float)N_DIVS))     );
                                          glVertex3f(-0.5 + (((float)(i + 1))/((float)N_DIVS)), -0.5 + (((float)(j + 1))/((float)N_DIVS)), 0.0);

                                        glTexCoord2f(       (((float)(i + 1))/((float)N_DIVS)),        (((float)(j + 1))/((float)N_DIVS))     );
                                          glVertex3f(-0.5 + (((float)(i + 1))/((float)N_DIVS)), -0.5 + (((float)(j + 1))/((float)N_DIVS)), 0.0);
                                        glTexCoord2f(       (((float)(i    ))/((float)N_DIVS)),        (((float)(j + 1))/((float)N_DIVS))     );
                                          glVertex3f(-0.5 + (((float)(i    ))/((float)N_DIVS)), -0.5 + (((float)(j + 1))/((float)N_DIVS)), 0.0);
                                        glTexCoord2f(       (((float)(i    ))/((float)N_DIVS)),        (((float)(j    ))/((float)N_DIVS))     );
                                          glVertex3f(-0.5 + (((float)(i    ))/((float)N_DIVS)), -0.5 + (((float)(j    ))/((float)N_DIVS)), 0.0);
                                }
                        }
                glEnd();
        glEndList();

        glNewList(cuadrado_hd, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                        glNormal3f(0, 0, 1);
                        for (i = 0; i < N_DIVS_HD; i++) {
                                for (j = 0; j < N_DIVS_HD; j++) {
                                        glTexCoord2f(       (((float)(i    ))/((float)N_DIVS_HD)),        (((float)(j    ))/((float)N_DIVS_HD))     );
                                          glVertex3f(-0.5 + (((float)(i    ))/((float)N_DIVS_HD)), -0.5 + (((float)(j    ))/((float)N_DIVS_HD)), 0.0);
                                        glTexCoord2f(       (((float)(i + 1))/((float)N_DIVS_HD)),        (((float)(j    ))/((float)N_DIVS_HD))     );
                                          glVertex3f(-0.5 + (((float)(i + 1))/((float)N_DIVS_HD)), -0.5 + (((float)(j    ))/((float)N_DIVS_HD)), 0.0);
                                        glTexCoord2f(       (((float)(i + 1))/((float)N_DIVS_HD)),        (((float)(j + 1))/((float)N_DIVS_HD))     );
                                          glVertex3f(-0.5 + (((float)(i + 1))/((float)N_DIVS_HD)), -0.5 + (((float)(j + 1))/((float)N_DIVS_HD)), 0.0);

                                        glTexCoord2f(       (((float)(i + 1))/((float)N_DIVS_HD)),        (((float)(j + 1))/((float)N_DIVS_HD))     );
                                          glVertex3f(-0.5 + (((float)(i + 1))/((float)N_DIVS_HD)), -0.5 + (((float)(j + 1))/((float)N_DIVS_HD)), 0.0);
                                        glTexCoord2f(       (((float)(i    ))/((float)N_DIVS_HD)),        (((float)(j + 1))/((float)N_DIVS_HD))     );
                                          glVertex3f(-0.5 + (((float)(i    ))/((float)N_DIVS_HD)), -0.5 + (((float)(j + 1))/((float)N_DIVS_HD)), 0.0);
                                        glTexCoord2f(       (((float)(i    ))/((float)N_DIVS_HD)),        (((float)(j    ))/((float)N_DIVS_HD))     );
                                          glVertex3f(-0.5 + (((float)(i    ))/((float)N_DIVS_HD)), -0.5 + (((float)(j    ))/((float)N_DIVS_HD)), 0.0);
                                }
                        }
                glEnd();
        glEndList();

        glNewList(cuadrado_simple, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                        glNormal3f(0, 0, 1);
                        glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.0);
                        glTexCoord2f(1, 0); glVertex3f( 0.5, -0.5, 0.0);
                        glTexCoord2f(1, 1); glVertex3f( 0.5,  0.5, 0.0);

                        glTexCoord2f(1, 1); glVertex3f( 0.5,  0.5, 0.0);
                        glTexCoord2f(0, 1); glVertex3f(-0.5,  0.5, 0.0);
                        glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.0);
                glEnd();
        glEndList();

        glNewList(cubo, GL_COMPILE);
                glPushMatrix();
                        glTranslatef(0, 0, 0.5);
                        glCallList(cuadrado);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(0, 0, -0.5);
                        glRotatef(180, 0, 1, 0);
                        glCallList(cuadrado);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(0, 0.5, 0);
                        glRotatef(-90, 1, 0, 0);
                        glCallList(cuadrado);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(0, -0.5, 0);
                        glRotatef(90, 1, 0, 0);
                        glCallList(cuadrado);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(0.5, 0, 0);
                        glRotatef(90, 0, 1, 0);
                        glCallList(cuadrado);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(-0.5, 0, 0);
                        glRotatef(-90, 0, 1, 0);
                        glCallList(cuadrado);
                glPopMatrix();
        glEndList();

        glNewList(cubo_simple, GL_COMPILE);
                glPushMatrix();
                        glTranslatef(0, 0, 0.5);
                        glCallList(cuadrado_simple);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(0, 0, -0.5);
                        glRotatef(180, 0, 1, 0);
                        glCallList(cuadrado_simple);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(0, 0.5, 0);
                        glRotatef(-90, 1, 0, 0);
                        glCallList(cuadrado_simple);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(0, -0.5, 0);
                        glRotatef(90, 1, 0, 0);
                        glCallList(cuadrado_simple);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(0.5, 0, 0);
                        glRotatef(90, 0, 1, 0);
                        glCallList(cuadrado_simple);
                glPopMatrix();
                glPushMatrix();
                        glTranslatef(-0.5, 0, 0);
                        glRotatef(-90, 0, 1, 0);
                        glCallList(cuadrado_simple);
                glPopMatrix();
        glEndList();

        {
                int p = 0;
                glNewList(checker, GL_COMPILE);
                        glBegin(GL_QUADS);
                                glNormal3f(0, 0, 1);
                                for (i = -100; i < 100; i += 1) {
                                        for (j = -100; j < 100; j++) {
                                                p ^= 1;
                                                if (p) continue;
                                                glVertex3f(i    , j    , 0);
                                                glVertex3f(i + 1, j    , 0);
                                                glVertex3f(i + 1, j + 1, 0);
                                                glVertex3f(i    , j + 1, 0);
                                        }
                                        p ^= 1;
                                }
                        glEnd();
                glEndList();
        }

        glNewList(borde, GL_COMPILE);
                glPushMatrix();
                        glTranslatef(0, H_TABLERO / 2.0, 0);
                        glScalef(W_TABLERO + (2 * D_TABLERO), D_TABLERO, 1);
                        glTranslatef(0, 0.5, 0);
                        glColor4ubv(color_borde);
                        glCallList(cubo);
                glPopMatrix();

                glPushMatrix();
                        glTranslatef(0, -H_TABLERO / 2.0, 0);
                        glScalef(W_TABLERO + (2 * D_TABLERO), D_TABLERO, 1);
                        glTranslatef(0, -0.5, 0);
                        glColor4ubv(color_borde);
                        glCallList(cubo);
                glPopMatrix();

                glPushMatrix();
                        glTranslatef(W_TABLERO / 2.0, 0, 0);
                        glScalef(D_TABLERO, H_TABLERO, 1);
                        glTranslatef(0.5, 0, 0);
                        glColor4ubv(color_borde);
                        glCallList(cubo);
                glPopMatrix();

                glPushMatrix();
                        glTranslatef(-W_TABLERO / 2.0, 0, 0);
                        glScalef(D_TABLERO, H_TABLERO, 1);
                        glTranslatef(-0.5, 0, 0);
                        glColor4ubv(color_borde);
                        glCallList(cubo);
                glPopMatrix();
        glEndList();

        glNewList(bala, GL_COMPILE);
                glPushMatrix();
                        glScalef(0.1, 0.5, 0.1);
                        glRotatef(-90, 1, 0, 0);
                        glTranslatef(0, 0, -0.55);
                        {
                                GLUquadric *quad = gluNewQuadric();
                                gluQuadricTexture(quad, GL_TRUE);
                                gluQuadricDrawStyle(quad, GLU_FILL);
                                gluQuadricNormals(quad, GLU_SMOOTH);
                                glPushMatrix();
                                        gluQuadricOrientation(quad, GLU_INSIDE);
                                        gluDisk(quad, 0, 0.6, N_SLICES, N_LOOPS);
                                        gluQuadricOrientation(quad, GLU_OUTSIDE);
                                        gluCylinder(quad, 0.6, 0.6, 1.0/3.0, N_SLICES, N_LOOPS);
                                        glTranslatef(0, 0, 1.0/3.0);
                                        gluCylinder(quad, 0.6, 0, 1.0/6.0, N_SLICES, N_LOOPS);
                                glPopMatrix();
                                gluDeleteQuadric(quad);
                        }
                glPopMatrix();
        glEndList();

        glNewList(barra, GL_COMPILE);
                glPushMatrix();
                        glBegin(GL_QUADS);
                                glVertex3f(-1, -1, 0);
                                glVertex3f( 1, -1, 0);
                                glVertex3f( 1,  1, 0);
                                glVertex3f(-1,  1, 0);
                        glEnd();
                glPopMatrix();
        glEndList();

        glNewList(cielo, GL_COMPILE);
                {
                        GLUquadric *quad = gluNewQuadric();
                        gluQuadricTexture(quad, GL_TRUE);
                        gluQuadricDrawStyle(quad, GLU_FILL);
                        gluQuadricNormals(quad, GLU_SMOOTH);
                        gluQuadricOrientation(quad, GLU_INSIDE);
                        gluSphere(quad, 400.0, 100, 100);
                        gluDeleteQuadric(quad);
                }
        glEndList();

        glNewList(segmento, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                        glVertex3f(-W_SEGMENT / 2.0              ,  H_SEGMENT / 2.0, 0);
                        glVertex3f(-W_SEGMENT / 2.0 - W_SEGMENT_T,                0, 0);
                        glVertex3f(-W_SEGMENT / 2.0              , -H_SEGMENT / 2.0, 0);

                        glVertex3f( W_SEGMENT / 2.0,  H_SEGMENT / 2.0, 0);
                        glVertex3f(-W_SEGMENT / 2.0,  H_SEGMENT / 2.0, 0);
                        glVertex3f(-W_SEGMENT / 2.0, -H_SEGMENT / 2.0, 0);

                        glVertex3f(-W_SEGMENT / 2.0, -H_SEGMENT / 2.0, 0);
                        glVertex3f( W_SEGMENT / 2.0, -H_SEGMENT / 2.0, 0);
                        glVertex3f( W_SEGMENT / 2.0,  H_SEGMENT / 2.0, 0);

                        glVertex3f( W_SEGMENT / 2.0              , -H_SEGMENT / 2.0, 0);
                        glVertex3f( W_SEGMENT / 2.0 + W_SEGMENT_T,  0              , 0);
                        glVertex3f( W_SEGMENT / 2.0              ,  H_SEGMENT / 2.0, 0);
                glEnd();

                glLineWidth(1);
                glBegin(GL_LINE_LOOP);
                        glColor4ub(0, 0, 0, 255);
                        glVertex3f(-W_SEGMENT / 2.0              ,  H_SEGMENT / 2.0, 0);
                        glVertex3f(-W_SEGMENT / 2.0 - W_SEGMENT_T,  0, 0);
                        glVertex3f(-W_SEGMENT / 2.0              , -H_SEGMENT / 2.0, 0);
                        glVertex3f( W_SEGMENT / 2.0              , -H_SEGMENT / 2.0, 0);
                        glVertex3f( W_SEGMENT / 2.0 + W_SEGMENT_T,  0, 0);
                        glVertex3f( W_SEGMENT / 2.0              ,  H_SEGMENT / 2.0, 0);
                glEnd();
        glEndList();

        for (i = 0; i <= 11; i++) {
                glNewList(segs[i], GL_COMPILE);
                        /* a */
                        if (ss[i][0]) glColor4ubv(color_ss_on );
                        else          glColor4ubv(color_ss_off);
                        glPushMatrix();
                                glTranslatef(0, W_SEGMENT + 2.0 * W_SEGMENT_T, 0);
                                glCallList(segmento);
                        glPopMatrix();

                        /* b */
                        if (ss[i][1]) glColor4ubv(color_ss_on );
                        else          glColor4ubv(color_ss_off);
                        glPushMatrix();
                                glTranslatef(W_SEGMENT / 2.0 + W_SEGMENT_T, W_SEGMENT / 2.0 + W_SEGMENT_T, 0);
                                glRotatef(90, 0, 0, 1);
                                glCallList(segmento);
                        glPopMatrix();

                        /* c */
                        if (ss[i][2]) glColor4ubv(color_ss_on );
                        else          glColor4ubv(color_ss_off);
                        glPushMatrix();
                                glTranslatef(W_SEGMENT / 2.0 + W_SEGMENT_T, -(W_SEGMENT / 2.0 + W_SEGMENT_T), 0);
                                glRotatef(90, 0, 0, 1);
                                glCallList(segmento);
                        glPopMatrix();

                        /* d */
                        if (ss[i][3]) glColor4ubv(color_ss_on );
                        else          glColor4ubv(color_ss_off);
                        glPushMatrix();
                                glTranslatef(0, -(W_SEGMENT + 2.0 * W_SEGMENT_T), 0);
                                glCallList(segmento);
                        glPopMatrix();

                        /* e */
                        if (ss[i][4]) glColor4ubv(color_ss_on );
                        else          glColor4ubv(color_ss_off);
                        glPushMatrix();
                                glTranslatef(-(W_SEGMENT / 2.0 + W_SEGMENT_T), -(W_SEGMENT / 2.0 + W_SEGMENT_T), 0);
                                glRotatef(90, 0, 0, 1);
                                glCallList(segmento);
                        glPopMatrix();

                        /* f */
                        if (ss[i][5]) glColor4ubv(color_ss_on );
                        else          glColor4ubv(color_ss_off);
                        glPushMatrix();
                                glTranslatef(-(W_SEGMENT / 2.0 + W_SEGMENT_T), W_SEGMENT / 2.0 + W_SEGMENT_T, 0);
                                glRotatef(90, 0, 0, 1);
                                glCallList(segmento);
                        glPopMatrix();

                        /* g */
                        if (ss[i][6]) glColor4ubv(color_ss_on );
                        else          glColor4ubv(color_ss_off);
                        glPushMatrix();
                                glCallList(segmento);
                        glPopMatrix();
                glEndList();
        }
}
