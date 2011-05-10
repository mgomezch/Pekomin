#include "Flee.hpp"

Flee::Flee(Mobile character, Mobile target, double maxAcceleration) {

	character = character;
	target = target;
	maxAcceleration = maxAcceleration;

}

pair<Triple,double> Flee::getSteering() {

	pair<Triple,double> steering;

	steering.first = character.position - target.position;
	steering.first.normalize();
	steering.first *= maxAcceleration;
	steering.second = 0;

	return steering;

}

string Flee::name() {

	return "Flee";

}