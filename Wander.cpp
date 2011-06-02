#include "Wander.hpp"
#include "Mobile.hpp"
#include "util.hpp"
#include "Phantom.hpp"

Wander::Wander(Mobile *character       ,
               double maxRotation      ,
               double targetRadius     ,
               double slowRadius       ,
               double wanderOffset     ,
               double wanderRadius     ,
               double wanderRate       ,
               double wanderOrientation,
               double maxSpeed         ) {
        this->character              = character;
        this->target                 = new Phantom();
        this->maxRotation            = maxRotation;
        this->targetRadius           = targetRadius;
        this->slowRadius             = slowRadius;
        this->wanderOffset           = wanderOffset;
        this->wanderRadius           = wanderRadius;
        this->wanderRate             = wanderRate;
        this->wanderOrientation      = wanderOrientation;
        this->maxSpeed               = maxSpeed;
        this->accum                  = 0;
}

tuple<bool, Triple, double> Wander::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;
	Triple direction;
	double distance, targetSpeed;

        if (this->accum == 0) {
                wanderOrientation += randomBinomial() * wanderRate;
                target->ang = character->ang + wanderOrientation;
                target->pos = character->pos; //+ character->orientation() * wanderOffset;
                target->pos += target->orientation() * wanderRadius;
        }
        if ((this->accum += ticks) >= 1000) this->accum = 0;

        get<0>(steering) = true;
	get<1>(steering) = target->pos - character->pos;
	get<1>(steering).normalized();
	get<1>(steering) *= maxSpeed;
	/*
	direction = target->pos - character->pos;
	distance = direction.length();
	if (distance < targetRadius) {
		get<1>(steering) = target->vel - character->vel;
		if (get<1>(steering).length() > maxSpeed) {
			get<1>(steering).normalized();
			get<1>(steering) *= maxSpeed;
		}
		return steering;
	}
        
	targetSpeed = maxSpeed - character->vel.dot(direction.normalized());
	if (distance < slowRadius) {
		targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
	}
	if (targetSpeed < 0) targetSpeed = 0;
	if (targetSpeed > maxSpeed) targetSpeed = maxSpeed;

	get<1>(steering) = direction.normalized() * targetSpeed;
	*/

        return steering;
}
