#ifndef _DIRECTSTATIC_HPP
#define _DIRECTSTATIC_HPP

#include <tuple>

#include "Behavior.hpp"

using namespace std;

class DirectStatic : public Behavior {
        public:
                virtual unsigned int family();
                virtual tuple<bool, Triple, double> getPos() = 0;
};

#endif
