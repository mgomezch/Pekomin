#include "BoundedDynamicSeparation.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

#define DEBUG_BOUNDEDDYNAMICSEPARATION

#ifdef DEBUG_BOUNDEDDYNAMICSEPARATION
#       include <iostream>
#       define DEBUG_SEPARATION_PRINT(S) cout << "DEBUG: Separation " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << endl;
#else
#       define DEBUG_SEPARATION_PRINT(S)
#endif

BoundedDynamicSeparation::BoundedDynamicSeparation(Mobile *character, Mobile *target, double maxForce, double separationRadius):
        character(character),
        target(target),
        maxForce(maxForce),
        separationRadius(separationRadius),
        active(false)
{}

pair<bool, Triple> BoundedDynamicSeparation::getForce(unsigned int ticks) {
        pair<bool, Triple> steering;
        double d;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering.second = cp - tp;
        d = steering.second.length();
        DEBUG_SEPARATION_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering.first = true;
                steering.second *= maxForce * (d / separationRadius);
        }
        else steering.first = false;

        return steering;
}
