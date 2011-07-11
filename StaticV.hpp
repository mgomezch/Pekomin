#ifndef _STATICV_HPP
#define _STATICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class StaticV : public virtual Behavior {
        public:
                virtual pair<bool, Triple> getPosIncr(unsigned int ticks) = 0;
};

#endif
