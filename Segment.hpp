#ifndef _SEGMENT_HPP
#define _SEGMENT_HPP

#include <tuple>

#include "Triple.hpp"
#include "Mobile.hpp"

using namespace std;

class Segment : public virtual Mobile {
        public:
                Triple p1, p2;

                Triple v1();
                Triple v2();
};

tuple<Triple, Triple> points(Segment *, Ent     *);
tuple<Triple, Triple> points(Ent     *, Segment *);
tuple<Triple, Triple> points(Segment *, Mobile  *);
tuple<Triple, Triple> points(Mobile  *, Segment *);
tuple<Triple, Triple> points(Segment *, Segment *);

#endif
