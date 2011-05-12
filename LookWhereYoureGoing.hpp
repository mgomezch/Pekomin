#ifndef _LOOKWHEREYOUREGOING_HPP
#define _LOOKWHEREYOUREGOING_HPP

#include "Align.hpp"

class LookWhereYoureGoing : public Align {
	public:
		static const unsigned int type = BEHAVIOR_LOOKWHEREYOUREGOING;

		LookWhereYoureGoing(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius);		

		tuple<bool, Triple, double> getVelInc();

};

#endif
