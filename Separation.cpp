#include <vector>

#include "Separation.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

//#define DEBUG_SEPARATION

#ifdef DEBUG_SEPARATION
#       include <iostream>
#       define DEBUG_SEPARATION_PRINT(S) std::cout << "DEBUG: Separation " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << std::endl;
#else
#       define DEBUG_SEPARATION_PRINT(S)
#endif

Separation::Separation(std::string name, Mobile *character, Mobile *target, double maxSpeed, double separationRadius):
        KinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        separationRadius(separationRadius)
{}

std::vector<Triple> Separation::getVelIncr(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        double d;

        Triple cp, tp;
        std::tie(cp, tp) = points(character, target);

        steering = cp - tp;
        d = steering.length();
        DEBUG_SEPARATION_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering *= maxSpeed * (d / separationRadius);
                return std::vector<Triple>(1, steering);
        }
        return std::vector<Triple>();

}
