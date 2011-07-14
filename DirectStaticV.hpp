#ifndef DIRECTSTATICV_HPP
#define DIRECTSTATICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define DirectStaticV_CALL_NAME getPos

class DirectStaticV : public virtual Behavior {
        public:
                virtual pair<bool, Triple> DirectStaticV_CALL_NAME(unsigned int ticks) = 0;
};

#endif
