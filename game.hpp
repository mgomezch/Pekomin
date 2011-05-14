#ifndef _GAME_HPP
#define _GAME_HPP

#define GRAVEDAD   (-0.00003)

/* Mundo */
#define H_TABLERO       250.0
#define W_TABLERO       250.0
#define D_TABLERO         2.0

/* HUD 7-segment display */
#define H_SEGMENT         2.0
#define W_SEGMENT         5.0
#define W_SEGMENT_T       1.0
#define DIGITS_SCORE       10

/* Explosiones */
#define N_BOOMS             4
#define N_BOOM_SETS         4
#define T_BOOM           3000
#define BOOM_SCALE        0.2

/* Cámaras */
#define H_LIGHT_TABLERO  25.0
#define H_OVERHEAD      100.0
#define T_CAM_OLD       500.0

/* Blur */
#define BLUR_TEXTURE_SIZE  64
#define N_BLURS             4
#define D_BLUR          0.025

/* Balas */
#define BALAS              10
#define N_PBALAS           10
#define V_BALA_MIN     0.0150
#define V_BALA_MAX     0.0425

#endif
