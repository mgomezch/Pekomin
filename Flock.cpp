#include "Flock.hpp"
#include "Phantom.hpp"

Flock::Flock(Mobile *character     ,
             double targetRadius   ,
             double slowRadius     ,
             double flockRadius    ,
             double maxAcceleration) {
        this->character       = character      ;
        this->target          = new Phantom()  ;
        this->targetRadius    = targetRadius   ;
        this->slowRadius      = slowRadius     ;
        this->flockRadius     = flockRadius    ;
        this->maxAcceleration = maxAcceleration;
        this->accum           = 0              ;
        this->dead            = false          ;
}

pair<bool, Triple> Flock::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
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

        tie(cp, tp) = points(this->character, this->target);
        /*steering.first = true;
        steering.second = tp - cp;
        if (steering.second.length() > 0.001) {
                steering.second.normalized();
                steering.second *= maxAcceleration;
        }*/

        // TODO: distance
        direction = tp - cp;
        distance = direction.length();

        if (distance < targetRadius) {
                steering.second = target->vel - character->vel;
                if (steering.second.length() > maxAcceleration) {
                        steering.second.normalized();
                        steering.second *= maxAcceleration;
                }
                return steering;
        }

        targetSpeed = maxAcceleration - character->vel.dot(direction.normalized());
        if (distance < slowRadius) {
                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
        }
        if (targetSpeed < 0) targetSpeed = 0;
        if (targetSpeed > maxAcceleration) targetSpeed = maxAcceleration;

        steering.second = direction.normalized() * targetSpeed;

        return steering;
}

void Flock::addBoid(Mobile *boid) {
        this->boids.push_back(boid);
}
