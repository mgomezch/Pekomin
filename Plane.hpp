#ifndef PLANE_HPP
#define PLANE_HPP

#include <tuple>

#include "Triple.hpp"
#include "Mobile.hpp"

class Plane : public virtual Mobile {
        public:
                Triple pp;
                Triple n;

                Plane(
                                std::string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                Triple pp = Triple(), Triple n = Triple(0, 0, 1)
                     );

                Triple normal() const;
                Triple point() const;
};

#endif
