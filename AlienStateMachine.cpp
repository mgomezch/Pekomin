#include "Mobile.hpp"
#include "AlienStateMachine.hpp"
#include "Triple.hpp"

#include "Wander.hpp"
#include "Arrive.hpp"
#include "Pursue.hpp"
#include "Evade.hpp"

#define DEBUG_ALIENSTATEMACHINE

#ifdef DEBUG_ALIENSTATEMACHINE
#       include <iostream>
#endif

AlienStateMachine::AlienStateMachine(std::string name    ,
                                     Mobile *character   ,
                                     Mobile *target      ,
                                     double maxRotationW ,
                                     double targetRadiusW,
                                     double slowRadiusW  ,
                                     double wanderOffsetW,
                                     double wanderRadiusW,
                                     double wanderRateW  ,
                                     double wanderTimeW  ,
                                     double maxSpeedW    ,
                                     double maxSpeedA    ,
                                     double targetRadiusA,
                                     double slowRadiusA  ,
                                     double maxSpeedP    ,
                                     double maxSpeedE    ):
        DirectKinematicV(name),
        character(character),
        target(target),
        state(States::Wander),
        wander(new Wander(name + "Wander", character, maxRotationW, targetRadiusW, slowRadiusW, wanderOffsetW, wanderRadiusW, wanderRateW, wanderTimeW, maxSpeedW)),
        arrive(new Arrive(name + "Arrive", character, target, maxSpeedA, targetRadiusA, slowRadiusA)),
        pursue(new Pursue(name + "Pursue", character, target, maxSpeedP)),
        evade(new Evade(name + "Evade", character, target, maxSpeedE))
{
        this->arrive->active = false;
        this->pursue->active = false;
        this->evade->active  = false;
}

std::vector<Triple> AlienStateMachine::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple cp, tp;
        double distance;
        std::vector<Triple> out;

        std::tie(cp, tp) = points(character, target);
        distance = (tp - cp).length();

        if (state != States::Wander && distance > 20) {
                this->state = States::Wander;
                this->wander->active = true ;
                this->arrive->active = false;
                this->pursue->active = false;
                this->evade->active  = false;
                out = (dynamic_cast<DirectKinematicV *>(wander)->getVel(ticks, delta_ticks));
        }
        else if (state != States::Arrive && distance <= 20) {
                this->state = States::Arrive;
                this->wander->active = false;
                this->arrive->active = true ;
                this->pursue->active = false;
                this->evade->active  = false;
                out = (dynamic_cast<DirectKinematicV *>(arrive)->getVel(ticks, delta_ticks));
        }

        return out;
}
