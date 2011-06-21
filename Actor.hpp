#ifndef _ACTOR_HPP
#define _ACTOR_HPP

#include "Mobile.hpp"
#include "Behavior.hpp"
#include "Families.hpp"

#include <vector>

using namespace std;

class Actor : public virtual Mobile {
        public:
                vector<Behavior *> behaviors;

                Actor(string name = "", Triple pos = Triple(), double ang = 0, Triple vel = Triple(), double vrot = 0);

                virtual void update(unsigned int ticks);
};

#endif
