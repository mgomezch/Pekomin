#ifndef BOX_HPP
#define BOX_HPP

#include <tuple>

#include "Ent.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

class BBox : public virtual Mobile {
        public:
                double sx, sy, sz;

                BBox(std::string name = "", Triple pos = Triple(), double ang  = 0, Triple vel = Triple(), double vrot = 0, double sx = 0, double sy = 0, double sz = 0);
};

std::tuple<Triple, Triple> points(BBox    *, Ent    *);
std::tuple<Triple, Triple> points(Ent    *, BBox    *);
std::tuple<Triple, Triple> points(BBox    *, Mobile *);
std::tuple<Triple, Triple> points(Mobile *, BBox    *);
std::tuple<Triple, Triple> points(BBox    *, BBox    *);

#endif
