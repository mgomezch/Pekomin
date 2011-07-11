#ifndef _ALIEN_HPP
#define _ALIEN_HPP

#include <vector>
#include <tuple>

#include "Actor.hpp"
#include "Triple.hpp"

using namespace std;

class Alien : public virtual Actor {
        public:
                enum class States : unsigned int { WANDER, SEEK, FLEE, ARRIVE, PURSUE, EVADE, FLOCK, SHOOT };
                int hp;
                States state;
                Behavior *wanderFlag, *arriveFlag, *pursueFlag, *evadeFlag;

                bool leader;
                vector <Behavior *> flock;

                Alien(string name = "", Triple pos = Triple(), double ang = 0, Triple vel = Triple(), double vrot = 0);

                virtual void steer(unsigned int ticks);
                virtual void draw();
};

#endif
