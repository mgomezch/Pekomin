#include "Collide.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

#define DEBUG_COLLIDE

#ifdef DEBUG_COLLIDE
#       include <iostream>
#       define DEBUG_COLLIDE_PRINT(S) cout << "DEBUG: Collide " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << endl;
#else
#       define DEBUG_COLLIDE_PRINT(S)
#endif

Collide::Collide(Mobile *character, Mobile *target) {
        this->character = character;
        this->target    = target;
        this->dead      = false;
}

pair<bool, Triple> Collide::getPosIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        double d;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering.second = cp - tp;
        d = steering.second.length();
/*
        DEBUG_COLLIDE_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering.first = true;
                steering.second *= maxSpeed * (d / separationRadius);
        }
        else steering.first = false;
*/
        return steering;
}

pair<bool, Triple> Collide::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        double d;
/*
        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering.second = cp - tp;
        d = steering.second.length();
        DEBUG_COLLIDE_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering.first = true;
                steering.second *= maxSpeed * (d / separationRadius);
        }
        else steering.first = false;

        return steering;
*/
}
