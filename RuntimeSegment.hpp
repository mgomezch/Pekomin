#ifndef RUNTIMESEGMENT_HPP
#define RUNTIMESEGMENT_HPP

#include <string>

#include "RuntimePoint.hpp"
#include "Segment.hpp"
#include "Triple.hpp"

class RuntimeSegment : public virtual RuntimePoint, public virtual Segment {
        public:
                RuntimeSegment(
                                std::string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                Triple p1 = Triple(-1, 0, 0),
                                Triple p2 = Triple( 1, 0, 0)
                              );
                // TODO: destructor!

                virtual void draw() const;
};

#endif
