#ifndef _RUNTIMEPEKOMIN_HPP
#define _RUNTIMEPEKOMIN_HPP

#include <string>

#include "Actor.hpp"

using namespace std;

class RuntimePekomin : public virtual Actor {
        public:
                RuntimePekomin(string name, Triple pos, double ang, Triple vel, double vrot);
                RuntimePekomin(string name, Triple pos, double ang                         );
                RuntimePekomin(string name                                                 );
                RuntimePekomin(             Triple pos, double ang, Triple vel, double vrot);
                RuntimePekomin(             Triple pos, double ang                         );
                RuntimePekomin(                                                            );
                // TODO: destructor!

                void addBehavior(Behavior *);
                virtual void draw();
};

#endif
