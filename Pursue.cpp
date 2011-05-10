#include "Pursue.hpp"

pair<Triple,double> Pursue::getSteering() {

	Triple direction;
	double distance, speed, prediction;

	direction = target.position - character.position;
	distance = direction.length();
	speed = character.velocity.length();

	if (speed <= distance / maxPrediction)
		prediction = maxPrediction;
	else
		prediction = distance / speed;

	Seek::target = target;
	Seek::target.position += target.velocity * prediction;

	return Seek::getSteering();

}

string Pursue::name() {

	return "Pursue";

}