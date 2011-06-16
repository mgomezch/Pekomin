#ifndef _RUNTIMEWALL_HPP
#define _RUNTIMEWALL_HPP

#include "Actor.hpp"
#include "Segment.hpp"

using namespace std;

class RuntimeWall : public virtual Actor, public virtual Segment {
        public:
                RuntimeWall(Triple pos, double ang, Triple vel, double vang, Triple p1, Triple p2);
                RuntimeWall(Triple pos, double ang,                          Triple p1, Triple p2);
                RuntimeWall(                                                 Triple p1, Triple p2);
                RuntimeWall(Triple pos, double ang, Triple vel, double vang                      );
                RuntimeWall(Triple pos, double ang                                               );
                RuntimeWall(                                                                     );
                ~RuntimeWall();

                void addBehavior(Behavior *);
                virtual void draw();
};

#endif
