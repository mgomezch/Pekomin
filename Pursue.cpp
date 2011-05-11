#include "Pursue.hpp"
#include "Mobile.hpp"

pair<Triple, double> Pursue::getSteering() {
        Triple direction;
        double distance, speed, prediction;

        direction = target->pos - character->pos;
        distance = direction.length();
        speed = character->vel.length();

        if (speed <= distance / maxPrediction) {
                prediction = maxPrediction;
        } else {
                prediction = distance / speed;
        }

        Seek::target = target;
        Seek::target->pos += target->vel * prediction;

        return Seek::getSteering();
}
