#ifndef _MOBILE_HPP
#define _MOBILE_HPP

#include "Ent.hpp"

class Mobile : public virtual Ent {
        public:
                Triple vel;
                double vrot;
};

double dist(Mobile *e1, Mobile *e2);

#endif
