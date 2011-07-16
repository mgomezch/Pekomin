#include <vector>

#include "Separation.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

//#define DEBUG_SEPARATION

#ifdef DEBUG_SEPARATION
#       include <iostream>
#       define DEBUG_SEPARATION_PRINT(S) cout << "DEBUG: Separation " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << endl;
#else
#       define DEBUG_SEPARATION_PRINT(S)
#endif

Separation::Separation(string name, Mobile *character, Mobile *target, double maxSpeed, double separationRadius):
        KinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        separationRadius(separationRadius)
{}

vector<Triple> Separation::getVelIncr(unsigned int ticks) {
        Triple steering;
        double d;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering = cp - tp;
        d = steering.length();
        DEBUG_SEPARATION_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering *= maxSpeed * (d / separationRadius);
                return vector<Triple>(1, steering);
        }
        return vector<Triple>();

}
