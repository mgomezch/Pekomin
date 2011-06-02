#ifndef _PHANTOM_HPP
#define _PHANTOM_HPP

#include "Actor.hpp"

using namespace std;

class Phantom : public Actor {
        public:
                Phantom(Triple pos, double ang, Triple vel, double vang);
                Phantom(Triple pos, double ang);
                Phantom();
                ~Phantom();

		void addBehavior(Behavior *b);
                virtual void draw();
};

#endif
