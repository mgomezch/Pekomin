#ifndef STATICA_HPP
#define STATICA_HPP

#include <vector>

#include "Behavior.hpp"

using namespace std;

#define StaticA_CALL_NAME getAngIncr

class StaticA : public virtual Behavior {
        public:
                StaticA(string name);

                virtual vector<double> StaticA_CALL_NAME(unsigned int ticks) = 0;
};

#endif
