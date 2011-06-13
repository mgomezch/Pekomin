#include "Pursue.hpp"
#include "Mobile.hpp"

Pursue::Pursue(Mobile *character, Mobile *target, double maxSpeed) {
        this->character = character;
        this->target    = target;
        this->maxSpeed  = maxSpeed;
}

pair<bool, Triple> Pursue::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple direction;
        double distance, targetRadius = 2.0, speed, prediction;

        if (character->vel.length() == 0) {
                steering.first = false;
                return steering;
        }

        direction = target->pos - character->pos;
        distance = direction.length();

        if (distance < targetRadius) {
                steering.first = false;
                return steering;
        }

        speed = character->vel.length();

        if (speed <= (distance / maxPrediction)) prediction = maxPrediction;
        else                                     prediction = distance / speed;

        steering.first = true;
        steering.second = target->pos + target->vel * prediction - character->pos;

        steering.second.normalize();
        steering.second *= maxSpeed;

        return steering;
}
