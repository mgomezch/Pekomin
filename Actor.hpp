#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <vector>

#include "Behavior.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

using namespace std;

class Actor : public virtual Mobile {
        public:
                vector<Behavior *> behaviors;

                Actor(
                                string name = "",
                                Triple pos = Triple(),
                                double ang = 0,
                                Triple vel = Triple(),
                                double vrot = 0
                     );

                Behavior &addBehavior(Behavior *);

                virtual void steer(unsigned int ticks);
                virtual void update();
};

#endif
