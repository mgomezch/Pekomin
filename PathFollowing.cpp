#include "PathFollowing.hpp"
#include "Mobile.hpp"

PathFollowing::PathFollowing(Mobile *character, double maxSpeed, double targetRadius, double slowRadius) {
        this->character    = character;
        this->maxSpeed     = maxSpeed;
        this->targetRadius = targetRadius;
        this->slowRadius   = slowRadius; 
}

void PathFollowing::add_Nodes(Node *begin, Node *end) {
        this->begin = begin;
        this->end   = end;
}

pair<bool, Triple> PathFollowing::getVel(unsigned int ticks){
        pair<bool, Triple> steering;
        Triple direction;
        double distance, targetSpeed;

        if (path.empty()) {
                path = dijkstra(begin, end);
                steering.first = false;
        }
        else {
                steering.first = true;
                if (path.size() > 0) {
                        direction = path.front()->pos - character->pos;
                        distance = direction.length();
                        if (distance < targetRadius) 
                                path.erase(path.begin());
                        steering.second = direction.normalized();
                        steering.second *= maxSpeed;
                }
                else if (path.size() == 1) {
                        direction = path.front()->pos - character->pos;
                        distance = direction.length();
                        direction.normalize();

                        if (distance < targetRadius) {
                                steering.second = character->vel;;
                                path.erase(path.begin());
                                if (steering.second.length() > maxSpeed) {
                                        steering.second.normalize();
                                        steering.second *= maxSpeed;
                                }
                                return steering;
                        }

                        targetSpeed = maxSpeed;
                        if (distance < slowRadius) {
                                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
                        }

                        steering.second = direction * targetSpeed;
                }
        }

        return steering; 
}
