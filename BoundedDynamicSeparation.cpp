#include <vector>

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

BoundedDynamicSeparation::BoundedDynamicSeparation(string name, Mobile *character, Mobile *target, double maxForce, double separationRadius):
        DynamicV(name),
        character(character),
        target(target),
        maxForce(maxForce),
        separationRadius(separationRadius)
{}

vector<Triple> BoundedDynamicSeparation::getForce(unsigned int ticks) {
        Triple steering;
        double d;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering = cp - tp;
        d = steering.length();
        DEBUG_SEPARATION_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering *= maxForce * (d / separationRadius);
                return vector<Triple>(1, steering);
        }
        return vector<Triple>();

}
