#ifndef _SEGMENT_HPP
#define _SEGMENT_HPP

#include "Triple.hpp"
#include "Mobile.hpp"

using namespace std;

class Segment : public virtual Mobile {
        public:
                Triple p1, p2;

                Triple v1();
                Triple v2();
};

double dist(Segment *, Ent     *);
double dist(Ent     *, Segment *);
double dist(Segment *, Mobile  *);
double dist(Mobile  *, Segment *);
double dist(Segment *, Segment *);

#endif
