#include "game.hpp"
#include "Player.hpp"
#include "Ent.hpp"

#include <GL/glut.h>

Player *player = 0;
vector<Ent *> ents;

int ww = 512;
int wh = 384;
int pass = 0;

int level = 0;

GLfloat aspectratio = 4.0/3.0;
GLfloat fov         =    60.0;
GLfloat znear       =    0.01;
GLfloat zfar        =  1000.0;
GLfloat cam_x       =     0.0;
GLfloat cam_y       =     0.0;
GLfloat cam_z       =     0.0;
GLfloat cam_rotx    =     0.0;
GLfloat cam_roty    =     0.0;

GLfloat cam_old_x    = 0;
GLfloat cam_old_y    = 0;
GLfloat cam_old_z    = 0;
GLfloat cam_old_rotx = 0;
GLfloat cam_old_roty = 0;
int old_cam          = 0;
int cam_old_t        = 0;
int cam_old_adj      = 0;
float retract        = 0;

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
int cam  = 0;
int blur = 0;

int deltas[N_DELTAS];
int deltas_cur        = 0;
int deltas_sum        = 0;
unsigned int delta    = 0;
int delay             = 0;
int new_time          = 0;
int old_time          = 0;
float max_frame_delay = 0;
float frame_delay     = 0;
int frozen            = 0;

struct boom_data boom[N_BOOM_SETS];
int nboom = 0;

float px   = 0,
      py   = 0,
      pz   = 0,
      prz  = 0,
      pv   = 0,
      pvx  = 0,
      pvy  = 0,
      pvz  = 0,
      pvrz = 0,
      pa   = 0,
      pav  = 0;
int pb[N_PBALAS];
int pbl[N_PBALAS];
float pbx[N_PBALAS], pby[N_PBALAS], pbz[N_PBALAS], pbvx[N_PBALAS], pbvy[N_PBALAS], pbvz[N_PBALAS];
float pbv[N_PBALAS];
int pbi = 0,
    pbn = 0;
int balas = 0;
int lives = 0;
int pts = 0;

int i = 0,
    j = 0,
    k = 0;

