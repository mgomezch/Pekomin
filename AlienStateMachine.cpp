#include "Alien.hpp"
#include "Mobile.hpp"
#include "AlienStateMachine.hpp"
#include "Triple.hpp"
#include "game.hpp"
#include "util.hpp"
#include "Wander.hpp"
#include "Arrive.hpp"
#include "Pursue.hpp"
#include "Evade.hpp"
#include "PathFollowing.hpp"

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
                                     double maxSpeedE    ,
                                     double maxSpeed     ,
                                     double targetRadius ,
                                     double slowRadius   ):
        DirectKinematicV(name),
        character(character),
        target(target),
        state(States::Wander),
        wander(new Wander(name + "Wander", character, maxRotationW, targetRadiusW, slowRadiusW, wanderOffsetW, wanderRadiusW, wanderRateW, wanderTimeW, maxSpeedW)),
        arrive(new Arrive(name + "Arrive", character, target, maxSpeedA, targetRadiusA, slowRadiusA)),
        pursue(new Pursue(name + "Pursue", character, target, maxSpeedP)),
        evade(new Evade(name + "Evade", character, target, maxSpeedE)),
        maxSpeed(maxSpeed),
        targetRadius(targetRadius),
        slowRadius(slowRadius),
        path(new PathFollowing(name + "PathFollowing", character, dynamic_cast<Mobile *>(cover[0]), maxSpeed, targetRadius, slowRadius)),
        last_ticks(0)
{
        this->arrive->active = false;
        this->pursue->active = false;
        this->evade->active  = false;
        this->path->active   = false;
}

AlienStateMachine::~AlienStateMachine() {
        delete this->path;
        delete this->evade;
        delete this->pursue;
        delete this->arrive;
        delete this->wander;
}

std::vector<Triple> AlienStateMachine::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple cp, tp;
        double distance;
        std::vector<Triple> temp;
        std::vector<Triple> out;

        if (this->last_ticks != ticks) {
                this->last_ticks = ticks;
                std::tie(cp, tp) = points(character, target);
                distance = (tp - cp).length();

                if (dynamic_cast<Alien *>(character)->hp >= 30) {
                        if (distance > 20) {
                                if (state != States::Wander) {
                                        std::cout << "Wander" << std::endl;
                                        this->state = States::Wander;
                                        this->wander->active = true ;
                                        this->arrive->active = false;
                                        this->pursue->active = false;
                                        this->evade->active  = false;
                                        if (this->path != NULL) this->path->active   = false;
                                }
                        } else {
                                if (state != States::Arrive) {
                                        std::cout << "Arrive" << std::endl;
                                        this->state = States::Arrive;
                                        this->wander->active = false;
                                        this->arrive->active = true ;
                                        this->pursue->active = false;
                                        this->evade->active  = false;
                                        if (this->path != NULL) this->path->active   = false;
                                }
                        }
                } else {
                        if (state != States::Path) {
                                std::cout << "PathFollowing" << std::endl;
                                this->state = States::Path;
                                this->wander->active = false;
                                this->arrive->active = false;
                                this->pursue->active = false;
                                this->evade->active  = false;
                                if (this->path == NULL) {
                                        double a = RandBin(0, 3);
                                        //path = new PathFollowing(name + "PathFollowing", character, dynamic_cast<Mobile *>(cover[static_cast<int>(a)]), maxSpeed, targetRadius, slowRadius);
                                        this->path->active = true; 
                                }
                                if (this->path != NULL) this->path->active == true;
                        }
                }
        }

        if (this->wander->active) {
                temp = wander->getVel(ticks, delta_ticks);
                out.insert(out.begin(), temp.begin(), temp.end());
        }
        if (this->arrive->active) {
                temp = arrive->getVel(ticks, delta_ticks);
                out.insert(out.begin(), temp.begin(), temp.end());
        }
        if (this->pursue->active) {
                temp = pursue->getVel(ticks, delta_ticks);
                out.insert(out.begin(), temp.begin(), temp.end());
        }
        if (this->evade->active) {
                temp = evade->getVel(ticks, delta_ticks);
                out.insert(out.begin(), temp.begin(), temp.end());
        }
        if (this->path->active) {
                temp = path->getVel(ticks, delta_ticks);
                out.insert(out.begin(), temp.begin(), temp.end());
        }

        return out;
}
