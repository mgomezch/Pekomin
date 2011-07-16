#ifndef DIRECTSTATICA_HPP
#define DIRECTSTATICA_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

#define DirectStaticA_CALL_NAME getAng

class DirectStaticA : public virtual Behavior {
        public:
                DirectStaticA(std::string name);

                virtual std::vector<double> DirectStaticA_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif
