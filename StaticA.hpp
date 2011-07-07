#ifndef _STATICA_HPP
#define _STATICA_HPP

#include <utility>

#include "Behavior.hpp"

using namespace std;

class StaticA : public virtual Behavior {
        public:
                virtual pair<bool, double> getAngIncr(unsigned int ticks) = 0;
};

#endif
