#ifndef _BEHAVIOR_HPP
#define _BEHAVIOR_HPP

#include <stdio.h>

#include <cmath>
#include <iostream>
#include <string>

#include "Triple.hpp"

using namespace std;

class Behavior {
	public:
                Behavior() {}
	
                double getNewOrientation(Triple position, double currentOrientation, Triple velocity);

                virtual string name() = 0;
};

#endif
