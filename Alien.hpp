#ifndef ALIEN_HPP
#define ALIEN_HPP

#include <vector>

#include "Actor.hpp"
#include "Triple.hpp"

#define ALIEN_DEFAULT_MAX_HP 10

class Alien : public virtual Actor {
        public:
                int hpmax;
                int hp;

                Alien(std::string name = "", Triple pos = Triple(), double ang = 0, Triple vel = Triple(), double vrot = 0, int hpmax = ALIEN_DEFAULT_MAX_HP);

                virtual void draw() const;
};

#endif
