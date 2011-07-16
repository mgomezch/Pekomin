#ifndef STATICV_HPP
#define STATICV_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

#define StaticV_CALL_NAME getPosIncr

class StaticV : public virtual Behavior {
        public:
                StaticV(std::string name);

                virtual std::vector<Triple> StaticV_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif
