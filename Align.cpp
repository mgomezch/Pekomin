#include "Align.hpp"

Align::Align(Mobile character, Mobile target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius) {

	character = character;
	target = target;
	maxAngularAcceleration = maxAngularAcceleration;
	maxRotation = maxRotation;
	targetRadius = targetRadius;
	slowRadius = slowRadius;

}

pair<Triple,double> Align::getSteering() {

	pair<Triple,double> steering;
	double rotation, rotationSize, targetRotation, angularAcceleration;

	rotation = target.orientation - character.orientation;
	mapToRange(&rotation);
	rotationSize = abs(rotation);

	if (rotationSize >= targetRadius) {

		if (rotationSize > slowRadius)
			targetRotation = maxRotation;
		else
			targetRotation = maxRotation * rotationSize / slowRadius;

		targetRotation *= rotation / rotationSize;
		steering.second = targetRotation - character.rotation;
		steering.second /= timeToTarget;
		angularAcceleration = abs(steering.second);

		if (angularAcceleration > maxAngularAcceleration) {
			steering.second /= angularAcceleration;
			steering.second *= maxAngularAcceleration;
		}

		steering.first = 0;

	}

	return steering;

}

void Align::mapToRange(double *value) {

	if (*value > M_PI) {
		*value -= 2 * M_PI;
		mapToRange(value);
	}
	else if(*value < -M_PI) {
		*value += 2 * M_PI;
		mapToRange(value);
	}

}

string Align::name() {

	return "Align";

}