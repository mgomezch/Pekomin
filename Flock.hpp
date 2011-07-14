#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <vector>
#include <utility>

#include "KinematicV.hpp"

class Mobile;

class Flock : public KinematicV {
        public:
                Mobile* character     ;
                Mobile* target        ;
                vector<Mobile*> boids ;
                double targetRadius   ;
                double slowRadius     ;
                double flockRadius    ;
                double maxAcceleration;
                unsigned int accum    ;

                Flock(Mobile *character     ,
                      double targetRadius   ,
                      double slowRadius     ,
                      double flockRadius    ,
                      double maxAcceleration);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);

                void addBoid(Mobile *boid);
};

#endif
