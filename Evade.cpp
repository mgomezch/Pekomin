#include <vector>

#include "Evade.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

#ifdef DEBUG_EVADE
#       include <iostream>
#endif

Evade::Evade(std::string name, Mobile *character, Mobile *target, double maxSpeed):
        DirectKinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed)
{}

std::vector<Triple> Evade::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        Triple direction;
        double distance, targetRadius = 1.0, speed, prediction;
        Triple cp, tp;

        if (character->vel.length() == 0) {
#ifdef DEBUG_EVADE
                std::cout << "Evade : " << dynamic_cast<void *>(this) << "1 distancia : " << distance << " velocidad : " << std::endl; steering.print();
#endif
                return std::vector<Triple>();
        }

        std::tie(cp, tp) = points(this->character, this->target);
        direction = cp - tp;
        distance = direction.length();

        if (distance < targetRadius) {
#ifdef DEBUG_EVADE
                std::cout << "Evade : " << dynamic_cast<void *>(this) << "2 distancia : " << distance << " velocidad : " << std::endl; steering.print();
#endif
                return std::vector<Triple>();
        }

        speed = character->vel.length();

        if (speed <= (distance / maxPrediction)) prediction = maxPrediction;
        else prediction = distance / speed;

        steering = cp - tp + target->vel * prediction;
        steering.normalized();

#ifdef DEBUG_EVADE
        std::cout << "Evade : " << dynamic_cast<void *>(this) << "3 distancia : " << distance << " velocidad : " << std::endl; steering.print();
#endif

        steering *= maxSpeed;

        return std::vector<Triple>(1, steering);
}
