#ifndef VOLUMEPLANE_HPP
#define VOLUMEPLANE_HPP

#include <tuple>

#include "Triple.hpp"
#include "Plane.hpp"

using namespace std;

class VolumePlane : public virtual Plane {
        public:
                VolumePlane(
                                string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                Triple pp = Triple(), Triple n = Triple(0, 0, 1)
                     );
};

tuple<Triple, Triple> points(VolumePlane *, Ent         *);
tuple<Triple, Triple> points(Ent         *, VolumePlane *);
tuple<Triple, Triple> points(VolumePlane *, Mobile      *);
tuple<Triple, Triple> points(Mobile      *, VolumePlane *);
tuple<Triple, Triple> points(VolumePlane *, VolumePlane *);

#endif
