#ifndef MOBILE_HPP
#define MOBILE_HPP

#include "Ent.hpp"
#include "Triple.hpp"

class Mobile : public virtual Ent {
        public:
                Triple vel;
                double vrot;

                Mobile(
                                std::string name = "",
                                Triple pos = Triple(), double  ang = 0,
                                Triple vel = Triple(), double vrot = 0
                      );

                virtual void update();

        protected:
                Triple new_vel;
                double new_vrot;
};

std::tuple<Triple, Triple> points(Ent    *e1, Mobile *e2);
std::tuple<Triple, Triple> points(Mobile *e1, Ent    *e2);
std::tuple<Triple, Triple> points(Mobile *e1, Mobile *e2);

#endif
