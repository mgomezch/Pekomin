#ifndef STATICA_HPP
#define STATICA_HPP

#include <vector>

#include "Behavior.hpp"

#define StaticA_CALL_NAME getAngIncr

class StaticA : public virtual Behavior {
        public:
                StaticA(std::string name);

                virtual std::vector<double> StaticA_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif
