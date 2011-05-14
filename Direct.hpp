#ifndef _DIRECT_HPP
#define _DIRECT_HPP

#include <tuple>

#include "Behavior.hpp"

using namespace std;

class Direct : public Behavior {
        public:
                virtual unsigned int family();
                virtual tuple<bool, Triple, double> getPos() = 0;
};

#endif
