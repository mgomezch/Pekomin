#include <vector>

#include "BoundedDynamicSeparation.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

#define DEBUG_BOUNDEDDYNAMICSEPARATION

#ifdef DEBUG_BOUNDEDDYNAMICSEPARATION
#       include <iostream>
#       define DEBUG_SEPARATION_PRINT(S) std::cout << "DEBUG: Separation " << reinterpret_cast<void *>(this) << ": " #S << " == " << S << std::endl;
#else
#       define DEBUG_SEPARATION_PRINT(S)
#endif

BoundedDynamicSeparation::BoundedDynamicSeparation(std::string name, Mobile *character, Mobile *target, double maxForce, double separationRadius):
        DynamicV(name),
        character(character),
        target(target),
        maxForce(maxForce),
        separationRadius(separationRadius)
{}

std::vector<Triple> BoundedDynamicSeparation::getForce(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        double d;

        Triple cp, tp;
        std::tie(cp, tp) = points(character, target);

        steering = cp - tp;
        d = steering.length();
        DEBUG_SEPARATION_PRINT(d);
        if (0 < d && d < separationRadius) {
                steering *= maxForce * (d / separationRadius);
                return std::vector<Triple>(1, steering);
        }
        return std::vector<Triple>();

}
