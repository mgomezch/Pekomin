#include <vector>

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

DynamicSeparation::DynamicSeparation(string name, Mobile *character, Mobile *target, double minForce, double separationRadius):
        DynamicV(name),
        character(character),
        target(target),
        minForce(minForce),
        separationRadius(separationRadius)
{}

vector<Triple> DynamicSeparation::getForce(unsigned int ticks) {
        Triple steering;
        double d;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering = cp - tp;
        d = steering.length();
        DEBUG_SEPARATION_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering *= (minForce * separationRadius) / d;
                return vector<Triple>(1, steering);
        }
        return vector<Triple>();

}
