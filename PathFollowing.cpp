#include <vector>

#include "Dijkstra.hpp"
#include "game.hpp"
#include "Mobile.hpp"
#include "PathFollowing.hpp"

PathFollowing::PathFollowing(std::string name, Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius):
        DirectKinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        targetRadius(targetRadius),
        slowRadius(slowRadius),
        create(false),
        begin(NULL),
        end(NULL)
{}

void PathFollowing::create_Path() {
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

        path = dijkstra(character, begin, end);

        for (unsigned int i = 0; i < path.size(); i++)
                path[i]->print_node();

        for (unsigned int i = 0; i < path.size(); i++)
                path[i]->add_mod(character, 500);

}

std::vector<Triple> PathFollowing::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        Triple dir;
        double d, targetSpeed;

        if (!create) {
                this->create = true;
                this->create_Path();
        }

        if (path.size() > 0) {
                dir = path.front()->pos - character->pos;
                d = dir.length();
                if (d < targetRadius) {
                        for (auto it = path.front()->mods.begin(); it != path.front()->mods.end(); ++it) {
                                if (std::get<0>(*it) == character) {
                                        path.front()->mods.erase(it);
                                        break;
                                }
                        }
                        path.erase(path.begin());
                }
                steering = dir.normalized();
                steering *= maxSpeed;
        } else {
                Triple cp, tp;
                std::tie(cp, tp) = points(character, target);

                dir = tp - cp;
                d = dir.length();

                if (d < targetRadius) {
                        dead = true;
                        create = false;
                        return std::vector<Triple>();
                }

                targetSpeed = maxSpeed;
                if (d < slowRadius) targetSpeed *= (d - targetRadius) / (slowRadius - targetRadius);

                steering = dir * targetSpeed;
        }

        return std::vector<Triple>(1, steering);
}
