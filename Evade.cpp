#include "Evade.hpp"
#include "Mobile.hpp"

pair<Triple, double> Evade::getSteering() {
        Triple direction;
        double distance, speed, prediction;

        direction = character->pos - target->pos;
        distance = direction.length();
        speed = character->vel.length();

        if (speed <= distance / maxPrediction) {
                prediction = maxPrediction;
        } else {
                prediction = distance / speed;
        }

        Flee::target = target;
        Flee::target->pos += target->vel* prediction;

        return Flee::getSteering();
}
