#ifndef _RUNTIMESEGMENT_HPP
#define _RUNTIMESEGMENT_HPP

#include <string>

#include "RuntimePoint.hpp"
#include "Segment.hpp"

using namespace std;

class RuntimeSegment : public virtual RuntimePoint, public virtual Segment {
        public:
                RuntimeSegment(
                                string name = ""      ,
                                Triple pos  = Triple(),
                                double ang  = 0       ,
                                Triple vel  = Triple(),
                                double vrot = 0       ,
                                Triple p1   = Triple(-1, 0, 0),
                                Triple p2   = Triple( 1, 0, 0)
                              );
                // TODO: destructor!

                void addBehavior(Behavior *);
                virtual void draw();
};

#endif
