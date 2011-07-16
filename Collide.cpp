#include "Collide.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

#define DEBUG_COLLIDE

#ifdef DEBUG_COLLIDE
#       include <iostream>
#       define DEBUG_COLLIDE_PRINT(S) std::cout << "DEBUG: Collide " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << std::endl;
#else
#       define DEBUG_COLLIDE_PRINT(S)
#endif

Collide::Collide(std::string name, Mobile *character, Mobile *target):
        KinematicV(name),
        StaticV(name),
        character(character),
        target(target)
{}

std::vector<Triple> Collide::getPosIncr(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        double d;

        Triple cp, tp;
        std::tie(cp, tp) = points(character, target);

        steering = cp - tp;
        d = steering.length();

#if 0
        DEBUG_COLLIDE_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering *= maxSpeed * (d / separationRadius);
                return std::vector<Triple>(1, steering);
        }
#endif

        return std::vector<Triple>();
}

std::vector<Triple> Collide::getVelIncr(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        double d;

        Triple cp, tp;
        std::tie(cp, tp) = points(character, target);

        steering = cp - tp;
        d = steering.length();

#if 0
        DEBUG_COLLIDE_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering *= maxSpeed * (d / separationRadius);
                return std::vector<Triple>(1, steering);
        }
#endif

        return std::vector<Triple>();
}
