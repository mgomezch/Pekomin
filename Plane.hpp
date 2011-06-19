#ifndef _PLANE_HPP
#define _PLANE_HPP

#include <tuple>

#include "Triple.hpp"
#include "Mobile.hpp"

using namespace std;

class Plane : public virtual Mobile {
        public:
                Triple n;
                Triple pp;

                Triple normal();
                Triple point();
};

tuple<Triple, Triple> points(Plane  *, Ent    *);
tuple<Triple, Triple> points(Ent    *, Plane  *);
tuple<Triple, Triple> points(Plane  *, Mobile *);
tuple<Triple, Triple> points(Mobile *, Plane  *);
tuple<Triple, Triple> points(Plane  *, Plane  *);

#endif
