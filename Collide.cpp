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

Collide::Collide(string name, Mobile *character, Mobile *target):
        KinematicV(name),
        StaticV(name),
        character(character),
        target(target)
{}

vector<Triple> Collide::getPosIncr(unsigned int ticks) {
        Triple steering;
        double d;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering = cp - tp;
        d = steering.length();

#if 0
        DEBUG_COLLIDE_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering *= maxSpeed * (d / separationRadius);
                return vector<Triple>(1, steering);
        }
#endif

        return vector<Triple>();
}

vector<Triple> Collide::getVelIncr(unsigned int ticks) {
        Triple steering;
        double d;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering = cp - tp;
        d = steering.length();

#if 0
        DEBUG_COLLIDE_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering *= maxSpeed * (d / separationRadius);
                return vector<Triple>(1, steering);
        }
#endif

        return vector<Triple>();
}
