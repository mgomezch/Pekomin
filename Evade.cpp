#include "Evade.hpp"

pair<Triple,double> Evade::getSteering() {

	Triple direction;
	double distance, speed, prediction;

	direction = character.position - target.position;
	distance = direction.length();
	speed = character.velocity.length();

	if (speed <= distance / maxPrediction)
		prediction = maxPrediction;
	else
		prediction = distance / speed;

	Flee::target = target;
	Flee::target.position += target.velocity * prediction;

	return Flee::getSteering();

}

string Evade::name() {

	return "Evade";

}