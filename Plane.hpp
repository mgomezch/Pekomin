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

#endif
