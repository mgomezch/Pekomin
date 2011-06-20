#ifndef _BOX_HPP
#define _BOX_HPP

#include <tuple>

#include "Triple.hpp"
#include "Mobile.hpp"

using namespace std;

class Box : public virtual Mobile {
        public:
                double sx, sy, sz;
};

tuple<Triple, Triple> points(Box    *, Ent    *);
tuple<Triple, Triple> points(Ent    *, Box    *);
tuple<Triple, Triple> points(Box    *, Mobile *);
tuple<Triple, Triple> points(Mobile *, Box    *);
tuple<Triple, Triple> points(Box    *, Box    *);

#endif
