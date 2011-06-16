#include "Evade.hpp"
#include "Mobile.hpp"

#ifdef DEBUG_EVADE
#include <iostream>
#endif

Evade::Evade(Mobile *character, Mobile *target, double maxSpeed) {
        this->character = character;
        this->target    = target   ;
        this->maxSpeed  = maxSpeed ;
        this->dead      = false    ;
}

pair<bool, Triple> Evade::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple direction;
        double distance, targetRadius = 5.0, speed, prediction;

        if (character->vel.length() == 0) {
                steering.first = false;
#ifdef DEBUG_EVADE
                cout << "Evade : " << dynamic_cast<void *>(this) << "1 distancia : " << distance << " velocidad : " << endl; steering.second.print();
#endif
                return steering;
        }

        direction = character->pos - target->pos;
        distance = direction.length();

        if (distance < targetRadius) {
                steering.first = false;
#ifdef DEBUG_EVADE
                cout << "Evade : " << dynamic_cast<void *>(this) << "2 distancia : " << distance << " velocidad : " << endl; steering.second.print();
#endif
                return steering;
        }

        speed = character->vel.length();

        if (speed <= (distance / maxPrediction)) prediction = maxPrediction;
        else                                     prediction = distance / speed;

        steering.first = true;
        steering.second = character->pos - target->pos + target->vel * prediction;
        steering.second.normalized();

#ifdef DEBUG_EVADE
                cout << "Evade : " << dynamic_cast<void *>(this) << "3 distancia : " << distance << " velocidad : " << endl; steering.second.print();
#endif

        steering.second *= maxSpeed;

        return steering;
}
