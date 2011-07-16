#ifndef DIRECTSTATICV_HPP
#define DIRECTSTATICV_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

#define DirectStaticV_CALL_NAME getPos

class DirectStaticV : public virtual Behavior {
        public:
                DirectStaticV(std::string name);

                virtual std::vector<Triple> DirectStaticV_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif
