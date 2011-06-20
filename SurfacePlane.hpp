#ifndef _SURFACEPLANE_HPP
#define _SURFACEPLANE_HPP

#include <tuple>

#include "Triple.hpp"
#include "Plane.hpp"

using namespace std;

class SurfacePlane : public virtual Plane {};

tuple<Triple, Triple> points(SurfacePlane  *, Ent           *);
tuple<Triple, Triple> points(Ent           *, SurfacePlane  *);
tuple<Triple, Triple> points(SurfacePlane  *, Mobile        *);
tuple<Triple, Triple> points(Mobile        *, SurfacePlane  *);
tuple<Triple, Triple> points(SurfacePlane  *, SurfacePlane  *);

#endif
