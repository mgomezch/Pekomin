#ifndef _DIRECTSTATICA_HPP
#define _DIRECTSTATICA_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class DirectStaticA : public Behavior {
        public:
                virtual pair<bool, double> getAng(unsigned int ticks) = 0;
};

#endif
