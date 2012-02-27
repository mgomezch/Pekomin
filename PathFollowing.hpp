#ifndef PATHFOLLOWING_HPP
#define PATHFOLLOWING_HPP

#if PEKOMIN_GRAFO

#include <vector>

#include "DirectKinematicV.hpp"
#include "Node.hpp"
#include "Triple.hpp"

class Mobile;

class PathFollowing : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double targetRadius;
                double slowRadius;
                bool create;

                std::vector<Node *> path;
                Node *begin;
                Node *end;

                PathFollowing(std::string name, Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);

                void create_Path();

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

#endif
