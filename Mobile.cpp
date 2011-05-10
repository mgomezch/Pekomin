#include "Mobile.hpp"

string Mobile::type() {
	
	return "Mobile";
	
}

void Mobile::update(pair<Triple,double> steering, double time) {

	position += velocity * time;
	orientation += rotation * time;
	velocity += steering.first * time;
	orientation += steering.second * time;
	
}

void Mobile::updateReally(pair<Triple,double> steering, double maxSpeed, double time) {

	position += velocity * time;
	orientation += rotation * time;
	velocity += steering.first * time;
	orientation += steering.second * time;

	if (velocity.length() > maxSpeed) {
		velocity.normalize();
		velocity *= maxSpeed;
	}
	
} 