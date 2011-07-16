#include <vector>

#include "Flock.hpp"
#include "Mobile.hpp"
#include "Phantom.hpp"
#include "Triple.hpp"

Flock::Flock(std::string name, Mobile *character, double targetRadius, double slowRadius, double flockRadius, double maxAcceleration):
        KinematicV(name),
        character(character),
        targetRadius(targetRadius),
        slowRadius(slowRadius),
        flockRadius(flockRadius),
        maxAcceleration(maxAcceleration),

        target(new Phantom()),
        accum(0)
{}

std::vector<Triple> Flock::getVelIncr(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        Triple direction;
        int tam = 0;
        double distance, targetSpeed;
        Triple cp, tp;

        //if (this->accum == 0) {
                for (unsigned int i = 0; i < boids.size(); i++) {
                        if (target->pos.length() < flockRadius) {
                                target->pos += boids[i]->pos;
                                tam++;
                        }
                }
                if (tam > 0) target->pos /= tam;
        //}
        //if (this->accum++ == 3000) this->accum = 0;

        std::tie(cp, tp) = points(this->character, this->target);
        /*
        steering = tp - cp;
        if (steering.length() > 0.001) {
                steering.normalized();
                steering *= maxAcceleration;
        }*/

        // TODO: distance
        direction = tp - cp;
        distance = direction.length();

        if (distance < targetRadius) {
                steering = target->vel - character->vel;
                if (steering.length() > maxAcceleration) {
                        steering.normalized();
                        steering *= maxAcceleration;
                }
                return std::vector<Triple>(1, steering);
        }

        targetSpeed = maxAcceleration - character->vel.dot(direction.normalized());
        if (distance < slowRadius) {
                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
        }
        if (targetSpeed < 0) targetSpeed = 0;
        if (targetSpeed > maxAcceleration) targetSpeed = maxAcceleration;

        steering = direction.normalized() * targetSpeed;

        return std::vector<Triple>(1, steering);
}

void Flock::addBoid(Mobile *boid) {
        this->boids.push_back(boid);
}
