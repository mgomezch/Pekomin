#ifndef VOLUMEPLANE_HPP
#define VOLUMEPLANE_HPP

#include <tuple>

#include "Triple.hpp"
#include "Plane.hpp"

class VolumePlane : public virtual Plane {
        public:
                VolumePlane(
                                std::string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                Triple pp = Triple(), Triple n = Triple(0, 0, 1)
                           );
};

std::tuple<Triple, Triple> points(VolumePlane *, Ent         *);
std::tuple<Triple, Triple> points(Ent         *, VolumePlane *);
std::tuple<Triple, Triple> points(VolumePlane *, Mobile      *);
std::tuple<Triple, Triple> points(Mobile      *, VolumePlane *);
std::tuple<Triple, Triple> points(VolumePlane *, VolumePlane *);

#endif
