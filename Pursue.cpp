#include "Pursue.hpp"
#include "Mobile.hpp"

#define DEBUG_PURSUE

#ifdef DEBUG_PURSUE
#include <iostream>
#endif

Pursue::Pursue(Mobile *character, Mobile *target, double maxSpeed) {
        this->character = character;
        this->target    = target   ;
        this->maxSpeed  = maxSpeed ;
        this->dead      = false    ;
}

pair<bool, Triple> Pursue::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple direction;
        double distance, targetRadius = 2.0, speed, prediction;

        if (character->vel.length() == 0) {
                steering.first = false;
#ifdef DEBUG_PURSUE
                cout << "Pursue : " << dynamic_cast<void *>(this) << "1 distancia : " << distance << " velocidad : " << endl; steering.second.print();
#endif
                return steering;
        }

        direction = target->pos - character->pos;
        distance = direction.length();

        if (distance < targetRadius) {
                steering.first = false;
#ifdef DEBUG_PURSUE
                cout << "Pursue : " << dynamic_cast<void *>(this) << "2 distancia : " << distance << " velocidad : " << endl; steering.second.print();
#endif
                return steering;
        }

        speed = character->vel.length();

        if (speed <= (distance / maxPrediction)) prediction = maxPrediction;
        else                                     prediction = distance / speed;

        steering.first = true;
        steering.second = target->pos + target->vel * prediction - character->pos;

#ifdef DEBUG_PURSUE
        cout << "Pursue : " << dynamic_cast<void *>(this) << "3 distancia : " << distance << " velocidad : " << endl; steering.second.print();
#endif

        steering.second = steering.second.normalized() * maxSpeed;

        return steering;
}
