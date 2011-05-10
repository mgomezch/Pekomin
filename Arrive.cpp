#include "Arrive.hpp"

Arrive::Arrive(Mobile character, Mobile target, double maxAcceleration, double maxSpeed, double targetRadius, double slowRadius) {

	character = character;
	target = target;
	maxAcceleration = maxAcceleration;
	maxSpeed = maxSpeed;
	targetRadius = targetRadius;
	slowRadius = slowRadius;

}

pair<Triple,double> Arrive::getSteering() {

	pair<Triple,double> steering;
	Triple direction, targetVelocity;
	double distance, targetSpeed;

	direction = target.position - character.position;
	distance = direction.length();

	//cuando no se cumple esto que se retorna? o que tiene el steering? o usar una referencia e instanciar a NULL y echarnos agua :D
	if (distance < targetRadius) { 

		if (distance > slowRadius)
			targetSpeed = maxSpeed;
		else
			targetSpeed = maxSpeed * distance / slowRadius;

		targetVelocity = direction;
		targetVelocity.normalize();
		targetVelocity *= targetSpeed;
		steering.first = targetVelocity - character.velocity;
		steering.first /= timeToTarget;

		if (steering.first.length() > maxAcceleration) {
			steering.first.normalize();
			steering.first *= maxAcceleration;
		}

		steering.second = 0;
	}
		
	return steering;

}

string Arrive::name() {

	return "Arrive";

}