#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>

#include "RuntimePoint.hpp"
#include "Triple.hpp"

class Player : public virtual RuntimePoint {
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

                Player(
                                string name = "",
                                Triple pos = Triple(), double ang = 0,
                                Triple vel = Triple(), double vrot = 0
                      );
                // TODO: destructor!

                virtual void update(unsigned int ticks);
                virtual void draw();
};

#endif
