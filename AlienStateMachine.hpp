#ifndef ALIENSTATEMACHINE_HPP
#define ALIENSTATEMACHINE_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;
class Wander;
class Arrive;
class Pursue;
class Evade;
class PathFollowing;

class AlienStateMachine : public virtual DirectKinematicV {
        public :
                enum class States : unsigned int {
                        Wander,
                        Arrive,
                        Pursue,
                        Evade,
                        Path,
                };

                Mobile *character;
                Mobile *target;
                States state;
                Wander *wander;
                Arrive *arrive;
                Pursue *pursue;
                Evade *evade;
                PathFollowing *path;
                unsigned int last_ticks;

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
                        double maxSpeedE,
                        double maxSpeed,
                        double targetRadius,
                        double slowRadius
                );

                virtual ~AlienStateMachine();

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif
