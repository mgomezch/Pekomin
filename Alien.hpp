#ifndef ALIEN_HPP
#define ALIEN_HPP

#include <vector>
#include <tuple>

#include "Actor.hpp"
#include "Triple.hpp"

using namespace std;

#define ALIEN_DEFAULT_MAX_HP 100

class Behavior;
class Mobile;

class Alien : public virtual Actor {
        public:
                enum class States : unsigned int {
                        Wander,
                        Arrive,
                        Pursue,
                        Evade
                };

                Mobile *target;
                int hpmax;
                int hp;
                States state;
                Behavior *wander, *arrive, *pursue, *evade;

                bool leader;
                vector<Behavior *> flock;

                Alien(Mobile *target, string name = "", Triple pos = Triple(), double ang = 0, Triple vel = Triple(), double vrot = 0, int hpmax = ALIEN_DEFAULT_MAX_HP);

                virtual void steer(unsigned int ticks);
                virtual void draw();
};

#endif
