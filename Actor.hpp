#ifndef _ACTOR_HPP
#define _ACTOR_HPP

#include "Mobile.hpp"

using namespace std;

class Actor : public Mobile {
        public:
                unsigned int state;
                vector<Behavior *> behaviors;
};

#endif
