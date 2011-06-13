#ifndef _RUNTIMEPEKOMIN_HPP
#define _RUNTIMEPEKOMIN_HPP

#include "Actor.hpp"

using namespace std;

class RuntimePekomin : public virtual Actor {
        public:
                RuntimePekomin(Triple pos, double ang, Triple vel, double vang);
                RuntimePekomin(Triple pos, double ang);
                RuntimePekomin();
                ~RuntimePekomin();

                void addBehavior(Behavior *);
                virtual void draw();
};

#endif
