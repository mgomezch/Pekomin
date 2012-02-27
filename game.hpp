#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glut.h>

#include <list>
#include <vector>

#include "Ent.hpp"
#include "Odor.hpp"
#include "Player.hpp"

#if PEKOMIN_GRAFO
#       include "Node.hpp"
#       include "Tile.hpp"
#endif

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
extern std::list<Ent  *> new_ents;
extern std::list<Odor *> new_odors;
extern std::list<Ent  *> ents;
extern std::list<Odor *> odors;

extern std::vector<Segment *> obstacles;
extern std::vector<Ent *> recovery;
extern std::vector<Ent *> cover;

#if PEKOMIN_GRAFO
extern std::vector<Node *> nodes;
extern std::vector<Tile *> tiles;
#endif

enum cam_enum {
        CAM_STATIC_OVERHEAD = 0,
        CAM_OVERHEAD,
        CAM_FPS,
        CAM_TPS,
        CAM_MANUAL
};
#define N_CAMS 5

extern unsigned int ww;
extern unsigned int wh;
extern unsigned int pass;

enum passes {
        PASS_BLUR = 0,
        PASS_LAST
};
#define FIRST_PASS PASS_BLUR
#define N_PASSES 2

extern unsigned int level;
enum levels {
        LEVEL_DESERT = 0,
        LEVEL_SKY,
        LEVEL_SPACE
};
#define START_LEVEL LEVEL_DESERT
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
extern int    cam_old_t;
extern bool   cam_old_adj;
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
extern int key_mesh        ; // STATELESS

extern bool keystate_fwd         ;
extern bool keystate_back        ;
extern bool keystate_left        ;
extern bool keystate_right       ;
extern bool keystate_cam_up      ;
extern bool keystate_cam_down    ;
extern bool keystate_cam_left    ;
extern bool keystate_cam_right   ;
extern bool keystate_cam_fwd     ;
extern bool keystate_cam_back    ;
extern bool keystate_cam_rotup   ;
extern bool keystate_cam_rotdown ;
extern bool keystate_cam_rotleft ;
extern bool keystate_cam_rotright;
extern bool keystate_enter       ;
extern bool keystate_shoot       ;
extern bool keystate_reload      ;
extern bool keystate_jump        ;
extern bool keystate_l           ;
extern bool keystate_r           ;
extern bool keystate_u           ;
extern bool keystate_d           ;

extern unsigned int cosa;
extern unsigned int cam;
extern bool blur;
extern bool mesh;

extern unsigned int deltas[N_DELTAS];
extern unsigned int deltas_cur;
extern unsigned int deltas_sum;
extern double max_frame_delay;
extern double frame_delay;

extern unsigned int delta;
extern unsigned int delay;
extern unsigned int new_time;
extern unsigned int old_time;
extern unsigned int old_cam;
extern bool         frozen;

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
        unsigned int level;
};
extern struct boom_data boom[N_BOOM_SETS];
extern unsigned int nboom;

extern double px, py, pz, prz, pv, pvx, pvy, pvz, pvrz, pa, pav;
extern bool pb[N_PBALAS];
extern unsigned int pbl[N_PBALAS];
extern double pbx[N_PBALAS], pby[N_PBALAS], pbz[N_PBALAS], pbvx[N_PBALAS], pbvy[N_PBALAS], pbvz[N_PBALAS];
extern double pbv[N_PBALAS];
extern unsigned int pbi, pbn;
extern int pts;
extern unsigned int lives;
extern unsigned int balas;
extern unsigned int i, j, k, n;

#endif
