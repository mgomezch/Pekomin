#ifndef _FACE_HPP
#define _FACE_HPP

#include "Align.hpp"

class Mobile;

class Face : public Align {
        public:
                static const unsigned int type = BEHAVIOR_FACE;
                Mobile *target;

                pair<Triple, double> getSteering();
};

#endif
