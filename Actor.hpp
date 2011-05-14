#ifndef _ACTOR_HPP
#define _ACTOR_HPP

#include "Mobile.hpp"
#include "Behavior.hpp"

#include <vector>

using namespace std;

class Actor : public Mobile {
        public:
                unsigned int state;
                vector<Behavior *> behaviors;

                virtual void update(unsigned int ticks);
};

#endif
