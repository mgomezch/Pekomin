#ifndef _ENT_HPP
#define _ENT_HPP

#include <string>

#include "Triple.hpp"

class Ent {
        public:
                Triple pos;
                double ang;

                virtual void draw()   = 0;
                virtual void update() = 0;
                virtual string type() = 0;
                Triple orientation();
};

#endif
