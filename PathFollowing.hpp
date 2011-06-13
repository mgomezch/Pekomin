#ifndef _PATHFOLLOWING_HPP
#define _PATHFOLLOWING_HPP

#include <vector>
#include "DirectKinematicV.hpp"
#include "Node.hpp"
#include "Dijkstra.hpp"

using namespace std;

class Mobile;

class PathFollowing : public DirectKinematicV {
        public:
                Mobile *character;
                vector<Node *> path;
                Node *begin;
                Node *end;
                double maxSpeed;
                double targetRadius;
                double slowRadius;

                PathFollowing(Mobile *character, double maxSpeed, double targetRadius, double slowRadius);

                void add_Nodes(Node *begin, Node *end);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif
