#ifndef _VOLUMEPLANE_HPP
#define _VOLUMEPLANE_HPP

#include <tuple>

#include "Triple.hpp"
#include "Plane.hpp"

using namespace std;

class VolumePlane : public virtual Plane {};

tuple<Triple, Triple> points(VolumePlane *, Ent         *);
tuple<Triple, Triple> points(Ent         *, VolumePlane *);
tuple<Triple, Triple> points(VolumePlane *, Mobile      *);
tuple<Triple, Triple> points(Mobile      *, VolumePlane *);
tuple<Triple, Triple> points(VolumePlane *, VolumePlane *);

#endif
