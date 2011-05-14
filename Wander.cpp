#include "Wander.hpp"
#include "Mobile.hpp"
#include "util.hpp"

unsigned int Wander::type() {
        return BEHAVIOR_WANDER;
}

Wander::Wander(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius, double wanderOffset, double wanderRadius, double wanderRate, double wanderOrientation, double maxAcceleration) : Face(character, target, maxAngularAcceleration, maxRotation, targetRadius, slowRadius) {
        //Face::Face(character, target, maxAngularAcceleration, maxRotation, targetRadius, slowRadius);
        this->wanderOffset      = wanderOffset;
        this->wanderRadius      = wanderRadius;
        this->wanderRate        = wanderRate;
        this->wanderOrientation = wanderOrientation;
        this->maxAcceleration   = maxAcceleration;
}

tuple<bool, Triple, double> Wander::getVelIncr() {
        tuple<bool, Triple, double> steering;
        Triple center;

        wanderOrientation += randomBinomial() * wanderRate;
        target->ang = wanderOrientation + character->ang;
        center = character->pos + character->orientation() * wanderOffset;
        center += target->orientation() * wanderRadius;
        steering = Face::getVelIncr();
	get<0>(steering) = true;
        get<1>(steering) += character->orientation() * maxAcceleration;

        return steering;
}
