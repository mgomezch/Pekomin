#ifndef BOX_HPP
#define BOX_HPP

#include <tuple>

#include "Ent.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

using namespace std;

class Box : public virtual Mobile {
        public:
                double sx, sy, sz;

                Box(
                                string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                double sx = 0, double sy = 0, double sz = 0
                   );
};

tuple<Triple, Triple> points(Box    *, Ent    *);
tuple<Triple, Triple> points(Ent    *, Box    *);
tuple<Triple, Triple> points(Box    *, Mobile *);
tuple<Triple, Triple> points(Mobile *, Box    *);
tuple<Triple, Triple> points(Box    *, Box    *);

#endif
