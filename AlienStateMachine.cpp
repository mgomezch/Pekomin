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
        last_ticks(0)
{
        for (auto it = cover.begin(); it != cover.end(); ++it) {
                paths.push_back(new PathFollowing(name + "PathFollowing", character, dynamic_cast<Mobile *>(*it), maxSpeed, targetRadius, slowRadius));
                this->paths.back()->active = false;
        }
        for (auto it = recovery.begin(); it != recovery.end(); ++it) {
                paths.push_back(new PathFollowing(name + "PathFollowing", character, dynamic_cast<Mobile *>(*it), maxSpeed, targetRadius, slowRadius));
                this->paths.back()->active = false;
        }

        std::cout << "Alien paths size" << paths.size() << std::endl;
        this->arrive->active = false;
        this->pursue->active = false;
        this->evade->active  = false;
}

AlienStateMachine::~AlienStateMachine() {
        for (unsigned int i = paths.size() - 1; i >= 0; i--)
                delete this->paths[i];
        delete this->evade;
        delete this->pursue;
        delete this->arrive;
        delete this->wander;
}

std::vector<Triple> AlienStateMachine::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple cp, tp;
        double distance, p;
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
                                        for (unsigned int i = 0; i < paths.size(); i++) {
                                                if(this->paths[i]->active)
                                                        this->paths[i]->active = false;
                                        }
                                }
                        } else {
                                if (state != States::Arrive) {
                                        std::cout << "Arrive" << std::endl;
                                        this->state = States::Arrive;
                                        this->wander->active = false;
                                        this->arrive->active = true ;
                                        this->pursue->active = false;
                                        this->evade->active  = false;
                                        for (unsigned int i = 0; i < paths.size(); i++) {
                                                if(this->paths[i]->active)
                                                        this->paths[i]->active = false;
                                        }
                                }
                        }
                } else {
                        if (distance > 20) {
                                if (state != States::Path) {
                                        std::cout << "PathFollowing" << std::endl;
                                        this->state = States::Path;
                                        this->wander->active = false;
                                        this->arrive->active = false;
                                        this->pursue->active = false;
                                        this->evade->active  = false;
                                        if (paths.size() > 0) {
                                                p = RandBin(0, paths.size() - 1);
                                                this->paths[p]->active = true;
                                        }
                                        else
                                                this->evade->active = true;
                                }
                        }
                        else if (distance < 5) {
                                if (state != States::Evade) {
                                        std::cout << "Evade" << std::endl;
                                        this->state = States::Evade;
                                        this->wander->active =  true;
                                        this->arrive->active = false;
                                        this->pursue->active = false;
                                        this->evade->active  =  true;
                                        if (paths.size() > 0) {
                                                p = RandBin(0, paths.size() - 1);
                                                this->paths[p]->active = false;
                                        }
                                }
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
        for (unsigned int i = 0; i < paths.size(); i++) {
                if (this->paths[i]->active) {
                        temp = paths[i]->getVel(ticks, delta_ticks);
                        out.insert(out.begin(), temp.begin(), temp.end());
                }
        }

        return out;
}
