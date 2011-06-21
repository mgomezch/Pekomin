#ifndef _PHANTOM_HPP
#define _PHANTOM_HPP

#include "RuntimePoint.hpp"

using namespace std;

class Phantom : public RuntimePoint {
        public:
                virtual void draw();
};

#endif
