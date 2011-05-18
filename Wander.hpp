#ifndef _WANDER_HPP
#define _WANDER_HPP

#include "Kinematic.hpp"
#include "Mobile.hpp"

class Wander : public Kinematic {
        public:
                Mobile* character;
                Mobile* target;
                double maxAngularAcceleration;
                double maxRotation;
                double targetRadius;
                double slowRadius;
                double wanderOffset;
                double wanderRadius;
                double wanderRate;
                double wanderOrientation;
                double maxAcceleration;
                unsigned int accum;

                Wander(Mobile *character            ,
                       double maxAngularAcceleration,
                       double maxRotation           ,
                       double targetRadius          ,
                       double slowRadius            ,
                       double wanderOffset          ,
                       double wanderRadius          ,
                       double wanderRate            ,
                       double wanderOrientation     ,
                       double maxAcceleration       );

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
};

#endif
