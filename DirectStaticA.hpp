#ifndef DIRECTSTATICA_HPP
#define DIRECTSTATICA_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define DirectStaticA_CALL_NAME getAng

class DirectStaticA : public virtual Behavior {
        public:
                DirectStaticA(string name);

                virtual vector<double> DirectStaticA_CALL_NAME(unsigned int ticks) = 0;
};

#endif
