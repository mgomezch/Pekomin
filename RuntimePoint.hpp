#ifndef _RUNTIMEPOINT_HPP
#define _RUNTIMEPOINT_HPP

#include <string>

#include "Actor.hpp"

using namespace std;

class RuntimePoint : public virtual Actor {
        public:
                RuntimePoint(string name = "", Triple pos = Triple(), double ang = 0, Triple vel = Triple(), double vrot = 0);
                // TODO: destructor!

                void addBehavior(Behavior *);
                virtual void draw();
};

#endif
