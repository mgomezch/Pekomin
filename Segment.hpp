#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <tuple>

#include "Mobile.hpp"
#include "Triple.hpp"

class Segment : public virtual Mobile {
        public:
                Triple p1, p2;

                Segment(
                                std::string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                Triple p1 = Triple(-1, 0, 0),
                                Triple p2 = Triple( 1, 0, 0)
                       );

                Triple v1();
                Triple v2();
};

std::tuple<Triple, Triple> points(Segment *, Ent     *);
std::tuple<Triple, Triple> points(Ent     *, Segment *);
std::tuple<Triple, Triple> points(Segment *, Mobile  *);
std::tuple<Triple, Triple> points(Mobile  *, Segment *);
std::tuple<Triple, Triple> points(Segment *, Segment *);

#endif
