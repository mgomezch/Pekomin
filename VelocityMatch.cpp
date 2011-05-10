#include "VelocityMatch.hpp"

VelocityMatch::VelocityMatch(Mobile character, Mobile target, double maxAcceleration) {

	character = character;
	target = target;
	maxAcceleration = maxAcceleration;

}

pair<Triple,double> VelocityMatch::getSteering() {

	pair<Triple,double> steering;
	
	steering.first = target.velocity - character.velocity;
	steering.first /= timeToTarget;

	if (steering.first.length() > maxAcceleration) {
		steering.first.normalize();
		steering.first *= maxAcceleration;
	}

	steering.second = 0;

	return steering;

}

string VelocityMatch::name() {

	return "VelocityMatch";

}