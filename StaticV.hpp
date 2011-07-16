#ifndef STATICV_HPP
#define STATICV_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define StaticV_CALL_NAME getPosIncr

class StaticV : public virtual Behavior {
        public:
                StaticV(string name);

                virtual vector<Triple> StaticV_CALL_NAME(unsigned int ticks) = 0;
};

#endif
