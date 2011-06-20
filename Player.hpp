#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>

#include "RuntimePekomin.hpp"

class Player : public RuntimePekomin {
        public:
                bool control_f,
                     control_b,
                     control_l,
                     control_r,
                     control_rot_l,
                     control_rot_r,
                     control_jump,
                     control_shoot;

                Player(const Player &);

                Player(string name, Triple pos, double ang, Triple vel, double vrot);
                Player(string name, Triple pos, double ang                         );
                Player(string name                                                 );
                Player(Triple pos, double ang, Triple vel, double vrot             );
                Player(Triple pos, double ang                                      );
                Player(                                                            );
                // TODO: destructor!

                virtual void update(unsigned int ticks);
                virtual void draw();
};

#endif
