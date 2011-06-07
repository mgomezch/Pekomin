#ifndef _PHANTOM_HPP
#define _PHANTOM_HPP

#include "RuntimePekomin.hpp"

using namespace std;

class Phantom : public RuntimePekomin {
        public:
                /*
                Phantom(Triple pos, double ang, Triple vel, double vang);
                Phantom(Triple pos, double ang);
                Phantom();
                ~Phantom();
                */

                //void addBehavior(Behavior *b);
                virtual void draw();
};

#endif
