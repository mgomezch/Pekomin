#include "Face.hpp"

pair<Triple,double> Face::getSteering() {

	Triple direction;

	direction = target.position - character.position;

	if (direction.length() > 0) {
		Align::target = target;
		Align::target.orientation = atan2(-direction.x, direction.z);
	}

	return Align::getSteering();
}

string Face::name() {

	return "Face";

}
