#ifndef _ENT_HPP
#define _ENT_HPP

#include <string>
#include <tuple>

#include "Triple.hpp"

class Segment;
class SurfacePlane;
class VolumePlane;
class Box;

class Ent {
        public:
                string name;
                Triple pos;
                double ang;

                Ent(string name = "", Triple pos = Triple(), double ang = 0);

                virtual void draw()                     = 0;
                virtual void update(unsigned int ticks) = 0;

                Triple orientation();
};

tuple<Triple, Triple> points(Ent *e1, Ent *e2);

tuple<Triple, Triple> points(Segment      *s, SurfacePlane *f);
tuple<Triple, Triple> points(Segment      *s, VolumePlane  *v);
tuple<Triple, Triple> points(Segment      *s, Box          *b);
tuple<Triple, Triple> points(SurfacePlane *f, VolumePlane  *v);
tuple<Triple, Triple> points(SurfacePlane *f, Box          *b);
tuple<Triple, Triple> points(VolumePlane  *v, Box          *b);

tuple<Triple, Triple> points(SurfacePlane *p, Segment      *s);
tuple<Triple, Triple> points(VolumePlane  *p, Segment      *s);
tuple<Triple, Triple> points(Box          *s, Segment      *b);
tuple<Triple, Triple> points(VolumePlane  *v, SurfacePlane *s);
tuple<Triple, Triple> points(Box          *b, SurfacePlane *s);
tuple<Triple, Triple> points(Box          *b, VolumePlane  *v);

#endif
