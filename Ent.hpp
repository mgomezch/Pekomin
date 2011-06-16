#ifndef _ENT_HPP
#define _ENT_HPP

#include <tuple>

#include "Triple.hpp"

class Segment;

class Ent {
        public:
                Triple pos;
                double ang;

                virtual void draw()                     = 0;
                virtual void update(unsigned int ticks) = 0;
                Triple orientation();
};

tuple<Triple, Triple> points(Ent *e1, Ent *e2);

#endif
