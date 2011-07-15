#ifndef PATHFOLLOWING_HPP
#define PATHFOLLOWING_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Node.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class PathFollowing : public DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double targetRadius;
                double slowRadius;

                vector<Node *> path;
                Node *begin;
                Node *end;

                PathFollowing(Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif
