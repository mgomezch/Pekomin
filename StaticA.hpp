#ifndef STATICA_HPP
#define STATICA_HPP

#include <utility>

#include "Behavior.hpp"

using namespace std;

#define StaticA_CALL_NAME getAngIncr

class StaticA : public virtual Behavior {
        public:
                StaticA(string name);

                virtual pair<bool, double> StaticA_CALL_NAME(unsigned int ticks) = 0;
};

#endif
