#include "Seek.hpp"

Seek::Seek(Mobile character, Mobile target, double maxAcceleration) {

	character = character;
	target = target;
	maxAcceleration = maxAcceleration;

}

pair<Triple,double> Seek::getSteering() {

	pair<Triple,double> steering;

	steering.first = target.position - character.position;
	steering.first.normalize();
	steering.first *= maxAcceleration;
	steering.second = 0;

	return steering;

}

string Seek::name() {

	return "Seek";

}