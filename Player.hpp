#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "Mobile.hpp"

class Player : public Mobile {
        public:
                bool control_u,
                     control_d,
                     control_l,
                     control_r,
                     control_rot_l,
                     control_rot_r,
                     control_jump,
                     control_shoot;

                Player(Triple pos, double ang, Triple vel, double vang);
                Player(Triple pos, double ang);
                Player(const Player &);
                Player();
                //~Player();

                virtual void update(unsigned int ticks);
                //void addBehavior(Behavior *b);
                virtual void draw();
};

#endif
