#include "Separation.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

#define DEBUG_SEPARATION

#ifdef DEBUG_SEPARATION
#       include <iostream>
#       define DEBUG_SEPARATION_PRINT(S) cout << "DEBUG: Separation " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << endl;
#else
#       define DEBUG_SEPARATION_PRINT(S)
#endif

Separation::Separation(Mobile *character, Mobile *target, double maxSpeed, double separationRadius):
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        separationRadius(separationRadius),
        active(true)
{}

pair<bool, Triple> Separation::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        double d;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering.second = cp - tp;
        d = steering.second.length();
        DEBUG_SEPARATION_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering.first = true;
                steering.second *= maxSpeed * (d / separationRadius);
        }
        else steering.first = false;

        return steering;
}
