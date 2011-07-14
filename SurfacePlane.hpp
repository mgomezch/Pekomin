#ifndef SURFACEPLANE_HPP
#define SURFACEPLANE_HPP

#include <tuple>

#include "Ent.hpp"
#include "Mobile.hpp"
#include "Plane.hpp"
#include "Triple.hpp"

using namespace std;

class SurfacePlane : public virtual Plane {
        public:
                SurfacePlane(
                                string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                Triple pp = Triple(), Triple n = Triple(0, 0, 1)
                     );
};

tuple<Triple, Triple> points(SurfacePlane  *, Ent           *);
tuple<Triple, Triple> points(Ent           *, SurfacePlane  *);
tuple<Triple, Triple> points(SurfacePlane  *, Mobile        *);
tuple<Triple, Triple> points(Mobile        *, SurfacePlane  *);
tuple<Triple, Triple> points(SurfacePlane  *, SurfacePlane  *);

#endif
