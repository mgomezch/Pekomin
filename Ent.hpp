#ifndef _ENT_HPP
#define _ENT_HPP

#include "Triple.hpp"

class Ent {
        Triple pos;
        double ang;

        virtual void draw()   = 0;
        virtual void update() = 0;
};

#endif
