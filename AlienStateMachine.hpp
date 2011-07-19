#ifndef ALIENSTATEMACHINE_HPP
#define ALIENSTATEMACHINE_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class AlienStateMachine : public virtual DirectKinematicV {
        public :
                enum class States : unsigned int {
                        Wander,
                        Arrive,
                        Pursue,
                        Evade
                };

                Mobile *character;
                Mobile *target;
                States state;
                Behavior *wander, *arrive, *pursue, *evade;

                AlienStateMachine(std::string name, Mobile *character, Mobile *target,
                        double maxRotationW,
                        double targetRadiusW,
                        double slowRadiusW,
                        double wanderOffsetW,
                        double wanderRadiusW,
                        double wanderRateW,
                        double wanderTimeW,
                        double maxSpeedW,
                        double maxSpeedA,
                        double targetRadiusA,
                        double slowRadiusA,
                        double maxSpeedP,
                        double maxSpeedE
                );

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif
