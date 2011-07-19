#include <GL/glut.h>

#include "Ent.hpp"
#include "game.hpp"
#include "Node.hpp"
#include "Player.hpp"

#include "Tile.hpp"

std::vector<Node *> nodes;
std::vector<Ent *> ents;

std::vector<Ent *> obstacles;
std::vector<Tile *> tiles;

Player *player = NULL;

unsigned int ww   = 512;
unsigned int wh   = 384;
unsigned int pass = 0;

unsigned int level = 0;

double aspectratio = 4.0/3.0;
double fov         =    60.0;
double znear       =    0.01;
double zfar        =  1000.0;
double cam_x       =     0.0;
double cam_y       =     0.0;
double cam_z       =     0.0;
double cam_rotx    =     0.0;
double cam_roty    =     0.0;

double retract       = 0;
double cam_old_x     = 0;
double cam_old_y     = 0;
double cam_old_z     = 0;
double cam_old_rotx  = 0;
double cam_old_roty  = 0;
int    cam_old_t     = 0;
bool   cam_old_adj   = false;

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
int key_cam_switch   = '\t'; // STATELESS
int key_enter        =   13;
int key_shoot        =  'z';
int key_reload       =  'r';
int key_jump         =  ' ';
int key_pause        = '\\'; // STATELESS
int key_mesh         =  'm'; // STATELESS

bool keystate_fwd          = false;
bool keystate_back         = false;
bool keystate_left         = false;
bool keystate_right        = false;
bool keystate_cam_up       = false;
bool keystate_cam_down     = false;
bool keystate_cam_left     = false;
bool keystate_cam_right    = false;
bool keystate_cam_fwd      = false;
bool keystate_cam_back     = false;
bool keystate_cam_rotup    = false;
bool keystate_cam_rotdown  = false;
bool keystate_cam_rotleft  = false;
bool keystate_cam_rotright = false;
bool keystate_enter        = false;
bool keystate_shoot        = false;
bool keystate_reload       = false;
bool keystate_jump         = false;
bool keystate_l            = false;
bool keystate_r            = false;
bool keystate_u            = false;
bool keystate_d            = false;

unsigned int cosa = 0;
unsigned int cam  = 0;
bool         blur = 0;
bool         mesh = 0;

unsigned int deltas[N_DELTAS];
unsigned int deltas_cur      = 0;
unsigned int deltas_sum      = 0;
unsigned int delta           = 0;
unsigned int delay           = 0;
unsigned int new_time        = 0;
unsigned int old_time        = 0;
double       max_frame_delay = 0;
double       frame_delay     = 0;
bool         frozen          = false;

struct boom_data boom[N_BOOM_SETS];
unsigned int nboom = 0;

double px   = 0,
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
bool pb[N_PBALAS];
unsigned int pbl[N_PBALAS];
double pbx[N_PBALAS], pby[N_PBALAS], pbz[N_PBALAS], pbvx[N_PBALAS], pbvy[N_PBALAS], pbvz[N_PBALAS];
double pbv[N_PBALAS];
unsigned int pbi = 0,
             pbn = 0;
unsigned int balas = 0;
unsigned int lives = 0;
int pts = 0;

unsigned int i = 0,
             j = 0,
             k = 0,
             n = 0;
