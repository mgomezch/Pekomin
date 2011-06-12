#ifndef _SEGMENT_HPP
#define _SEGMENT_HPP

#include "Mobile.hpp"

using namespace std;

class Segment : public Mobile {
        public:
                Triple p1, p2;

                Triple v1();
                Triple v2();

                friend double dist(Segment &, Ent     &);
                friend double dist(Ent     &, Segment &);
                friend double dist(Segment &, Segment &);
};

double dist(Segment &, Ent     &);
double dist(Ent     &, Segment &);
double dist(Segment &, Segment &);

#endif
