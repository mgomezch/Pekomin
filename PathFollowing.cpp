#include "Dijkstra.hpp"
#include "game.hpp"
#include "Mobile.hpp"
#include "PathFollowing.hpp"

PathFollowing::PathFollowing(Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius) {
        this->character    = character   ;
        this->target       = target      ;
        this->maxSpeed     = maxSpeed    ;
        this->targetRadius = targetRadius;
        this->slowRadius   = slowRadius  ;

        double d;

        d = (nodes[0]->pos - character->pos).length();
        this->begin = nodes[0];
        for (unsigned int i = 1; i < nodes.size(); i++) {
                if (d > (nodes[i]->pos - character->pos).length()) {
                        d = (nodes[i]->pos - character->pos).length();
                        this->begin = nodes[i];
                }
        }

        d = (nodes[0]->pos - target->pos).length();
        this->end = nodes[0];
        for (unsigned int i = 1; i < nodes.size(); i++) {
                if (d > (nodes[i]->pos - target->pos).length()) {
                        d = (nodes[i]->pos - target->pos).length();
                        this->end = nodes[i];
                }
        }

        path = dijkstra(begin, end);
}

pair<bool, Triple> PathFollowing::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple dir;
        double d, targetSpeed;

        steering.first = true;
        if (path.size() > 0) {
                dir = path.front()->pos - character->pos;
                d = dir.length();
                if (d < targetRadius) path.erase(path.begin());
                steering.second = dir.normalized();
                steering.second *= maxSpeed;
        } else {
                Triple cp, tp;
                tie(cp, tp) = points(character, target);

                dir = tp - cp;
                d = dir.length();

                if (d < targetRadius) {
                        steering.first = false;
                        dead = true;
                        return steering;
                }

                targetSpeed = maxSpeed;
                if (d < slowRadius) targetSpeed *= (d - targetRadius) / (slowRadius - targetRadius);

                steering.second = dir * targetSpeed;
        }

        return steering;
}
