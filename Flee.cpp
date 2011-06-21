#include "Flee.hpp"
#include "Mobile.hpp"

#define DEBUG_FLEE

#ifdef DEBUG_FLEE
#       include <iostream>
#       define DEBUG_FLEE_PRINT(S) cout << "DEBUG: Flee " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << endl;
#else
#       define DEBUG_FLEE_PRINT(S)
#endif

Flee::Flee(Mobile *character, Mobile *target, double maxSpeed, double fleeRadius) {
        this->character  = character ;
        this->target     = target    ;
        this->maxSpeed   = maxSpeed  ;
        this->fleeRadius = fleeRadius;
        this->dead       = false     ;
}

pair<bool, Triple> Flee::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering.second = cp - tp;
        DEBUG_FLEE_PRINT((cp - tp).length());
        if (steering.second.length() < fleeRadius) {
                steering.first = true;
                steering.second.normalize();
                steering.second *= maxSpeed;
        }
        return steering;
}
