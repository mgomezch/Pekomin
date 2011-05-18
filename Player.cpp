#include <GL/glut.h>

#include "gl.hpp"
#include "Player.hpp"

//#define DEBUG_PLAYER

#ifdef DEBUG_PLAYER
#include <iostream>
#endif

Player::~Player() {}

Player::Player(const Player &p) {
        this->pos     = p.pos          ;
        this->ang     = p.ang          ;
        this->vel     = p.vel          ;
        this->vrot    = p.vrot         ;
        control_u     = p.control_u    ;
        control_d     = p.control_d    ;
        control_l     = p.control_l    ;
        control_r     = p.control_r    ;
        control_rot_l = p.control_rot_l;
        control_rot_r = p.control_rot_r;
        control_jump  = p.control_jump ;
        control_shoot = p.control_shoot;
}

Player::Player() {
        this->pos     = Triple(0, 0, 0);
        this->ang     = 0;
        this->vel     = Triple(0, 0, 0);
        this->vrot    = 0;
        control_u     = false;
        control_d     = false;
        control_l     = false;
        control_r     = false;
        control_rot_l = false;
        control_rot_r = false;
        control_jump  = false;
        control_shoot = false;
}

Player::Player(Triple pos, double ang) {
        Player();
        this->pos = pos;
        this->ang = ang;
}

Player::Player(Triple pos, double ang, Triple vel, double vang) {
        Player(pos, ang);
        this->vel  = vel;
        this->vrot = vrot;
}

void Player::update(unsigned int ticks) {
        // TODO: mover actualización de estado del jugador de main.cpp pacá
}

void Player::draw() {
        glPushMatrix();
                glColor4ub(0, 255, 0, 255);
                glTranslatef(0, 0, 0.5);
                glCallList(cubo);
                glBegin(GL_LINES);
                        glVertex3f(0, 0, 0);
                        glVertex3f(0, 2, 0);
                glEnd();
        glPopMatrix();
#ifdef DEBUG_PLAYER
        cout << "player: drawing at (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << endl;
#endif
}
