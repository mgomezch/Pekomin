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
        this->dead         = false       ;

        double distance;

        distance = (nodes[0]->pos - character->pos).length();
        this->begin = nodes[0];
        for (unsigned int i = 1; i < nodes.size(); i++) {
                if (distance > (nodes[i]->pos - character->pos).length()) {
                        distance = (nodes[i]->pos - character->pos).length();
                        this->begin = nodes[i];
                }
        }

        distance = (nodes[0]->pos - target->pos).length();
        this->end = nodes[0];
        for (unsigned int i = 1; i < nodes.size(); i++) {
                if (distance > (nodes[i]->pos - target->pos).length()) {
                        distance = (nodes[i]->pos - target->pos).length();
                        this->end = nodes[i];
                }
        }

        path = dijkstra(begin, end);
}

pair<bool, Triple> PathFollowing::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple direction;
        double distance, targetSpeed;

        steering.first = true;
        if (path.size() > 0) {
                direction = path.front()->pos - character->pos;
                distance = direction.length();
                if (distance < targetRadius)
                        path.erase(path.begin());
                steering.second = direction.normalized();
                steering.second *= maxSpeed;
        }
        else {
                direction = target->pos - character->pos;
                distance = direction.length();
                direction.normalize();

                if (distance < targetRadius) {
                        steering.second = target->vel;
                        dead = true; // MATANDO PATHFOLLOWING
                        if (steering.second.length() > maxSpeed) {
                                steering.second.normalize();
                                steering.second *= maxSpeed;
                        }
                        return steering;
                }

                targetSpeed = maxSpeed;
                if (distance < slowRadius) targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);

                steering.second = direction * targetSpeed;
        }

        return steering;
}
