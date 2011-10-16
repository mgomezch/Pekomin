#ifndef PHANTOM_HPP
#define PHANTOM_HPP

#include "RuntimePoint.hpp"

class Phantom : public RuntimePoint {
        public:
                virtual void draw() const;
};

#endif
