#include "DynamicSeparation.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

#define DEBUG_DYNAMICSEPARATION

#ifdef DEBUG_DYNAMICSEPARATION
#       include <iostream>
#       define DEBUG_SEPARATION_PRINT(S) cout << "DEBUG: Separation " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << endl;
#else
#       define DEBUG_SEPARATION_PRINT(S)
#endif

DynamicSeparation::DynamicSeparation(Mobile *character, Mobile *target, double minForce, double separationRadius):
        character(character),
        target(target),
        minForce(minForce),
        separationRadius(separationRadius)
{}

pair<bool, Triple> DynamicSeparation::getForce(unsigned int ticks) {
        pair<bool, Triple> steering;
        double d;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering.second = cp - tp;
        d = steering.second.length();
        DEBUG_SEPARATION_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering.first = true;
                steering.second *= (minForce * separationRadius) / d;
        }
        else steering.first = false;

        return steering;
}
