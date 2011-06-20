#ifndef _RUNTIMEWALL_HPP
#define _RUNTIMEWALL_HPP

#include <string>

#include "Actor.hpp"
#include "Segment.hpp"

using namespace std;

class RuntimeWall : public virtual Actor, public virtual Segment {
        public:
                RuntimeWall(string name, Triple pos, double ang, Triple vel, double vrot, Triple p1, Triple p2);
                RuntimeWall(string name, Triple pos, double ang,                          Triple p1, Triple p2);
                RuntimeWall(string name,                                                  Triple p1, Triple p2);
                RuntimeWall(string name, Triple pos, double ang, Triple vel, double vrot                      );
                RuntimeWall(string name, Triple pos, double ang                                               );
                RuntimeWall(string name                                                                       );
                RuntimeWall(             Triple pos, double ang, Triple vel, double vrot, Triple p1, Triple p2);
                RuntimeWall(             Triple pos, double ang,                          Triple p1, Triple p2);
                RuntimeWall(                                                              Triple p1, Triple p2);
                RuntimeWall(             Triple pos, double ang, Triple vel, double vrot                      );
                RuntimeWall(             Triple pos, double ang                                               );
                RuntimeWall(                                                                                  );
                // TODO: destructor!

                void addBehavior(Behavior *);
                virtual void draw();
};

#endif
