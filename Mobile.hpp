#ifndef _MOBILE_HPP
#define _MOBILE_HPP

#include "Ent.hpp"

class Mobile : public virtual Ent {
        public:
                Triple vel;
                double vrot;
};

double dist(Ent    *e1, Mobile *e2);
double dist(Mobile *e1, Ent    *e2);
double dist(Mobile *e1, Mobile *e2);

tuple<Triple, Triple> points(Ent    *e1, Mobile *e2);
tuple<Triple, Triple> points(Mobile *e1, Ent    *e2);
tuple<Triple, Triple> points(Mobile *e1, Mobile *e2);

#endif
