#ifndef DIRECTSTATICA_HPP
#define DIRECTSTATICA_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define DirectStaticA_CALL_NAME getAng

class DirectStaticA : public virtual Behavior {
        public:
                virtual pair<bool, double> DirectStaticA_CALL_NAME(unsigned int ticks) = 0;
};

#endif
