#ifndef _GAME_HPP
#define _GAME_HPP

#include <GL/glut.h>

#include <vector>

#include "Node.hpp"
#include "Player.hpp"
#include "Ent.hpp"

#define GRAVEDAD   (-0.0001)

// Mundo
#define H_TABLERO       250.0
#define W_TABLERO       250.0
#define D_TABLERO         2.0

// HUD 7-segment display
#define H_SEGMENT         2.0
#define W_SEGMENT         5.0
#define W_SEGMENT_T       1.0
#define DIGITS_SCORE       10

// Explosiones
#define N_BOOMS             4
#define N_BOOM_SETS         4
#define T_BOOM           3000
#define BOOM_SCALE        0.2

// Cámaras
#define H_LIGHT_TABLERO  25.0
#define H_OVERHEAD       75.0
#define T_CAM_OLD       500.0

// Blur
#define BLUR_TEXTURE_SIZE  64
#define N_BLURS             4
#define D_BLUR          0.025

// Balas
#define BALAS              10
#define N_PBALAS           10
#define V_BALA_MIN     0.0150
#define V_BALA_MAX     0.0425

// Tiempo
#define N_DELTAS           50
#define COSA                3

extern Player *player;
extern vector<Ent *> ents;
extern vector<Node *> graph;

enum cam_enum {
        CAM_STATIC_OVERHEAD = 0,
        CAM_OVERHEAD,
        CAM_FPS,
        CAM_TPS,
        CAM_MANUAL
};
#define N_CAMS 5

extern int ww;
extern int wh;
extern int pass;

enum passes {
        PASS_BLUR = 0,
        PASS_LAST
};
#define FIRST_PASS PASS_BLUR
#define N_PASSES 2

extern int level;
enum levels {
        LEVEL_DESERT = 0,
        LEVEL_SKY,
        LEVEL_SPACE
};
#define START_LEVEL LEVEL_SPACE
#define N_LEVELS 3

extern double aspectratio;
extern double fov        ;
extern double znear      ;
extern double zfar       ;
extern double cam_x      ;
extern double cam_y      ;
extern double cam_z      ;
extern double cam_rotx   ;
extern double cam_roty   ;

extern double cam_old_x;
extern double cam_old_y;
extern double cam_old_z;
extern double cam_old_rotx;
extern double cam_old_roty;
extern int cam_old_t;
extern int cam_old_adj;
extern double retract;

extern int key_fwd         ;
extern int key_back        ;
extern int key_left        ;
extern int key_right       ;
extern int key_cam_up      ;
extern int key_cam_down    ;
extern int key_cam_left    ;
extern int key_cam_right   ;
extern int key_cam_fwd     ;
extern int key_cam_back    ;
extern int key_cam_rotup   ;
extern int key_cam_rotdown ;
extern int key_cam_rotleft ;
extern int key_cam_rotright;
extern int key_cam_switch  ; // STATELESS
extern int key_enter       ;
extern int key_shoot       ;
extern int key_reload      ;
extern int key_jump        ;
extern int key_pause       ; // STATELESS

extern int key_mesh_switch ; // STATELESS

extern int keystate_fwd         ;
extern int keystate_back        ;
extern int keystate_left        ;
extern int keystate_right       ;
extern int keystate_cam_up      ;
extern int keystate_cam_down    ;
extern int keystate_cam_left    ;
extern int keystate_cam_right   ;
extern int keystate_cam_fwd     ;
extern int keystate_cam_back    ;
extern int keystate_cam_rotup   ;
extern int keystate_cam_rotdown ;
extern int keystate_cam_rotleft ;
extern int keystate_cam_rotright;
extern int keystate_enter       ;
extern int keystate_shoot       ;
extern int keystate_reload      ;
extern int keystate_jump        ;
extern int keystate_l           ;
extern int keystate_r           ;
extern int keystate_u           ;
extern int keystate_d           ;

extern int cosa;
extern int cam;
extern int blur;
extern int mesh;

extern int deltas[N_DELTAS];
extern int deltas_cur;
extern int deltas_sum;
extern double max_frame_delay;
extern double frame_delay;

extern unsigned int delta;
extern int delay;
extern int new_time;
extern int old_time;
extern int frozen;
extern int old_cam;

struct boom_data {
        double  x[N_BOOMS];
        double  y[N_BOOMS];
        double  z[N_BOOMS];
        double rx[N_BOOMS];
        double ry[N_BOOMS];
        double rz[N_BOOMS];
        double  a[N_BOOMS];
        double  s[N_BOOMS];
        double vx[N_BOOMS];
        double vy[N_BOOMS];
        double vz[N_BOOMS];
        double va[N_BOOMS];
        double  r[N_BOOMS];
        double  g[N_BOOMS];
        double  b[N_BOOMS];
        int on;
        int level;
};
extern struct boom_data boom[N_BOOM_SETS];
extern int nboom;

extern double px, py, pz, prz, pv, pvx, pvy, pvz, pvrz, pa, pav;
extern int pb[N_PBALAS];
extern int pbl[N_PBALAS];
extern double pbx[N_PBALAS], pby[N_PBALAS], pbz[N_PBALAS], pbvx[N_PBALAS], pbvy[N_PBALAS], pbvz[N_PBALAS];
extern double pbv[N_PBALAS];
extern int pbi, pbn;
extern int pts;
extern int i, j, k;
extern int lives;
extern int balas;

#endif
