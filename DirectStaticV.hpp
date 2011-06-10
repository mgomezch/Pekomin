#ifndef _DIRECTSTATICV_HPP
#define _DIRECTSTATICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class DirectStaticV : public Behavior {
        public:
                virtual pair<bool, Triple> getPos(unsigned int ticks) = 0;
};

#endif
