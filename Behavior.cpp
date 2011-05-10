#include "Behavior.hpp"

double Behavior::getNewOrientation(Triple position, double currentOrientation, Triple velocity) {
	
	if (velocity.length() > 0)
		return atan2(-position.x,position.z);
	else
		return currentOrientation;
	
}