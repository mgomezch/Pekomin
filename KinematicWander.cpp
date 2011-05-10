#include "KinematicWander.hpp"

KinematicWander::KinematicWander(Static character, double maxSpeed, double maxRotation) {

	character = character;
	maxSpeed = maxSpeed;
	maxRotation = maxRotation;

}

pair<Triple,double> KinematicWander::getSteering() {

	pair<Triple,double> steering;
	steering.first = character.asVector() * maxSpeed;
	steering.second = randomBinomial() * maxRotation;

	return steering;

}

string KinematicWander::name() {

	return "KinematicWander";

}