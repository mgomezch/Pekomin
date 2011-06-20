#ifndef _ENT_HPP
#define _ENT_HPP

#include <string>
#include <tuple>

#include "Triple.hpp"

class Segment;
class SurfacePlane;

class Ent {
        public:
                string name;
                Triple pos;
                double ang;

                virtual void draw()                     = 0;
                virtual void update(unsigned int ticks) = 0;

                Triple orientation();
};

tuple<Triple, Triple> points(Ent *e1, Ent *e2);

tuple<Triple, Triple> points(Segment      *s, SurfacePlane *p);
tuple<Triple, Triple> points(SurfacePlane *p, Segment      *s);
// TODO: VolumePlane
// TODO: Box

#endif
