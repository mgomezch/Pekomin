#ifndef _ACTOR_HPP
#define _ACTOR_HPP

#include "Mobile.hpp"
#include "Behavior.hpp"
#include "Direct.hpp"
#include "Static.hpp"
#include "Kinematic.hpp"
#include "Dynamic.hpp"

#include <vector>
#include <tuple>

using namespace std;

class Actor : public Mobile {
        public:
                unsigned int state;
                vector<Behavior *> behaviors;

                virtual void update(unsigned int ticks);
};

#endif
