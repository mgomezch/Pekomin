#include <vector>

#include "Dijkstra.hpp"
#include "game.hpp"
#include "Mobile.hpp"
#include "PathFollowing.hpp"

PathFollowing::PathFollowing(string name, Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius):
        DirectKinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        targetRadius(targetRadius),
        slowRadius(slowRadius)
{
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

vector<Triple> PathFollowing::getVel(unsigned int ticks) {
        Triple steering;
        Triple dir;
        double d, targetSpeed;

        if (path.size() > 0) {
                dir = path.front()->pos - character->pos;
                d = dir.length();
                if (d < targetRadius) path.erase(path.begin());
                steering = dir.normalized();
                steering *= maxSpeed;
        } else {
                Triple cp, tp;
                tie(cp, tp) = points(character, target);

                dir = tp - cp;
                d = dir.length();

                if (d < targetRadius) {
                        dead = true;
                        return vector<Triple>();
                }

                targetSpeed = maxSpeed;
                if (d < slowRadius) targetSpeed *= (d - targetRadius) / (slowRadius - targetRadius);

                steering = dir * targetSpeed;
        }

        return vector<Triple>(1, steering);
}
