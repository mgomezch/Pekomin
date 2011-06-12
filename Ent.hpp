#ifndef _ENT_HPP
#define _ENT_HPP

#include "Triple.hpp"

class Ent {
        public:
                Triple pos;
                double ang;

                virtual void draw()                     = 0;
                virtual void update(unsigned int ticks) = 0;
                Triple orientation();

                friend double dist(Ent &e1, Ent &e2);
};

double dist(Ent &e1, Ent &e2);

#endif
