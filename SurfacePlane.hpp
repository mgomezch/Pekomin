#ifndef SURFACEPLANE_HPP
#define SURFACEPLANE_HPP

#include <tuple>

#include "Ent.hpp"
#include "Mobile.hpp"
#include "Plane.hpp"
#include "Triple.hpp"

class SurfacePlane : public virtual Plane {
        public:
                SurfacePlane(
                                std::string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                Triple pp = Triple(), Triple n = Triple(0, 0, 1)
                     );
};

std::tuple<Triple, Triple> points(SurfacePlane  *, Ent           *);
std::tuple<Triple, Triple> points(Ent           *, SurfacePlane  *);
std::tuple<Triple, Triple> points(SurfacePlane  *, Mobile        *);
std::tuple<Triple, Triple> points(Mobile        *, SurfacePlane  *);
std::tuple<Triple, Triple> points(SurfacePlane  *, SurfacePlane  *);

#endif
