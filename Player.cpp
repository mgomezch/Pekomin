//#include <cmath>
#include <GL/glut.h>

//#include "game.hpp"
#include "gl.hpp"
#include "Player.hpp"
#include "Triple.hpp"

//#define DEBUG_PLAYER

#ifdef DEBUG_PLAYER
#       include <iostream>
#endif

Player::Player(const Player &p) {
        this->name    = p.name         ;
        this->pos     = p.pos          ;
        this->ang     = p.ang          ;
        this->vel     = p.vel          ;
        this->vrot    = p.vrot         ;
        control_f     = p.control_f    ;
        control_b     = p.control_b    ;
        control_l     = p.control_l    ;
        control_r     = p.control_r    ;
        control_rot_l = p.control_rot_l;
        control_rot_r = p.control_rot_r;
        control_jump  = p.control_jump ;
        control_shoot = p.control_shoot;
}

Player::Player(string name, Triple pos, double ang, Triple vel, double vrot):
        RuntimePoint(name, pos, ang, vel, vrot),
        control_f(false),
        control_b(false),
        control_l(false),
        control_r(false),
        control_rot_l(false),
        control_rot_r(false),
        control_jump(false),
        control_shoot(false)
{}

void Player::steer(unsigned int ticks) {
        /*
        double pv = 0;

        if (this->control_jump && this->pos.z == 0 && this->vel.z == 0) {
                // TODO: use #define
                this->vel.z = 0.04;
        }

        // TODO: convertir en Behavior "Fall"
        if (this->pos.z != 0 || this->vel.z != 0) {
                this->vel.z += GRAVEDAD * ticks;
                if (this->pos.z <= 0) {
                        this->pos.z = 0;
                        this->vel.z = 0;
                }
        } else {
                if (control_f    ) pv          =  ticks / 10000.0;
                if (control_b    ) pv          = -ticks / 10000.0;
                if (control_rot_l) this->vrot +=  ticks / 5000.0;
                if (control_rot_r) this->vrot -=  ticks / 5000.0;
                // pv += -0.005 * pv * ticks;
                this->vel.x += pv * cos(this->ang);
                this->vel.y += pv * sin(this->ang);
        }

        this->Actor::steer(ticks);
        */
}

void Player::update() {}

void Player::draw() {
        glPushMatrix();
                glColor4ub(0, 255, 0, 255);
                glTranslatef(0, 0, 0.5);
                glCallList(cubo);
                glBegin(GL_LINES);
                        glVertex3f(0, 0, 0);
                        glVertex3f(2, 0, 0);
                glEnd();
        glPopMatrix();
#ifdef DEBUG_PLAYER
        cout << "player: drawing at (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << endl;
#endif
}
