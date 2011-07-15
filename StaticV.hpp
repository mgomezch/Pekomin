#ifndef STATICV_HPP
#define STATICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define StaticV_CALL_NAME getPosIncr

class StaticV : public virtual Behavior {
        public:
                StaticV(string name);

                virtual pair<bool, Triple> StaticV_CALL_NAME(unsigned int ticks) = 0;
};

#endif
