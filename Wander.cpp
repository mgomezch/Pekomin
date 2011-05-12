#include "Wander.hpp"

Wander::Wander(double wanderOffset, double wanderRadius, double wanderRate, double wanderOrientation, double maxAcceleration) {

	this->wanderOffset = wanderOffset;
	this->wanderRadius = wanderRadius;
	this->wanderRate = wanderRate;
	this->wanderOrientation = wanderOrientation;
	this->maxAcceleration = maxAcceleration;

}

tuple<bool,Triple,double> Wander::getSteering() {

	tuple<bool,Triple,double> steering;
	Triple center;

	wanderOrientation += randomBinomial() * wanderRate;
	target.orientation = wanderOrientation + character.orientation;
	center = character.position + character.asVector() * wanderOffset;
	center += target.asVector() * wanderRadius;
	steering = Face::getSteering();
	get<1>(steering) = character.asVector() * maxAcceleration;

	return steering;

}

string Wander::name() {

	return "Wander";

}