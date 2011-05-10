#ifndef _MOBILE_HPP
#define _MOBILE_HPP

#include "Ent.hpp"

class Mobile : Ent {
        public:
                Triple vel;
                double vrot;

                string type();
};

#endif
