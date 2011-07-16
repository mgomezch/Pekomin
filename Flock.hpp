#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <vector>
#include <utility>

#include "KinematicV.hpp"

class Mobile;

class Flock : public virtual KinematicV {
        public:
                Mobile* character;
                double targetRadius;
                double slowRadius;
                double flockRadius;
                double maxAcceleration;

                Mobile* target;
                unsigned int accum;
                vector<Mobile*> boids;

                Flock(string name, Mobile *character, double targetRadius, double slowRadius, double flockRadius, double maxAcceleration);

                virtual vector<Triple> getVelIncr(unsigned int ticks);

                void addBoid(Mobile *boid);
};

#endif
