#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <vector>

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
               std::vector<Mobile*> boids;

                Flock(std::string name, Mobile *character, double targetRadius, double slowRadius, double flockRadius, double maxAcceleration);

                virtual std::vector<Triple> getVelIncr(unsigned int ticks, unsigned int delta_ticks);

                void addBoid(Mobile *boid);
};

#endif
