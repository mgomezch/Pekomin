#ifndef MOBILE_HPP
#define MOBILE_HPP

#include "Ent.hpp"
#include "Triple.hpp"

class Mobile : public virtual Ent {
        public:
                Triple vel;
                double vrot;

                Mobile(
                                string name = "",
                                Triple pos = Triple(), double  ang = 0,
                                Triple vel = Triple(), double vrot = 0
                      );

                virtual void update();

        protected:
                Triple new_vel;
                double new_vrot;
};

tuple<Triple, Triple> points(Ent    *e1, Mobile *e2);
tuple<Triple, Triple> points(Mobile *e1, Ent    *e2);
tuple<Triple, Triple> points(Mobile *e1, Mobile *e2);

#endif
