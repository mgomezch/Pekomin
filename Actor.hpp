#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <vector>

#include "Mobile.hpp"
#include "Triple.hpp"

class Behavior;

class Actor : public virtual Mobile {
        public:
                std::vector<Behavior *> behaviors;

                Actor(std::string name = "", Triple pos = Triple(), double ang = 0, Triple vel = Triple(), double vrot = 0);

                Behavior &addBehavior(Behavior *);

                virtual void steer(unsigned int ticks, unsigned int delta_ticks);
                virtual void update();
};

#endif
