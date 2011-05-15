#ifndef _STATIC_HPP
#define _STATIC_HPP

#include <tuple>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class Static : public Behavior {
        public:
                virtual tuple<bool, Triple, double> getPosIncr() = 0;
};

#endif
