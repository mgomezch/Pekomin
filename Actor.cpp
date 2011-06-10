#include <utility>

#include "Actor.hpp"
#include "util.hpp"

//#define DEBUG_ACTOR

#ifdef DEBUG_ACTOR
#include <iostream>
#include <stdio.h>
#endif

using namespace std;

void Actor::update(unsigned int ticks) {
        unsigned int i;

        DirectStaticV    *p_v_directstatic   ;
        StaticV          *p_v_static         ;
        DirectKinematicV *p_v_directkinematic;
        KinematicV       *p_v_kinematic      ;
        DynamicV         *p_v_dynamic        ;

        DirectStaticA    *p_a_directstatic   ;
        StaticA          *p_a_static         ;
        DirectKinematicA *p_a_directkinematic;
        KinematicA       *p_a_kinematic      ;
        DynamicA         *p_a_dynamic        ;

        vector<Triple> v_directstatic   ,
                       v_static         ,
                       v_directkinematic,
                       v_kinematic      ,
                       v_dynamic        ;

        vector<double> a_directstatic   ,
                       a_static         ,
                       a_directkinematic,
                       a_kinematic      ,
                       a_dynamic        ;

        Triple sum_v_directstatic    = Triple(0, 0, 0),
               sum_v_static          = Triple(0, 0, 0),
               sum_v_directkinematic = Triple(0, 0, 0),
               sum_v_kinematic       = Triple(0, 0, 0),
               sum_v_dynamic         = Triple(0, 0, 0);

        double sum_a_directstatic    = 0,
               sum_a_static          = 0,
               sum_a_directkinematic = 0,
               sum_a_kinematic       = 0,
               sum_a_dynamic         = 0;

        pair<bool, Triple> v_steering;
        pair<bool, double> a_steering;

        unsigned int n_v_directstatic    = 0,
                     n_v_static          = 0,
                     n_v_directkinematic = 0,
                     n_v_kinematic       = 0,
                     n_v_dynamic         = 0,
                     n_a_directstatic    = 0,
                     n_a_static          = 0,
                     n_a_directkinematic = 0,
                     n_a_kinematic       = 0,
                     n_a_dynamic         = 0;

        this->ang = mapToRange(this->ang);

        for (i = 0; i < behaviors.size(); i++) {
                if ((p_v_directstatic = dynamic_cast<DirectStaticV *>(behaviors[i])) != NULL) {
                        v_steering = p_v_directstatic->getPos(ticks);
                        if (v_steering.first) {
                                n_v_directstatic++;
                                v_directstatic.push_back(v_steering.second);
                        }
                }
                if ((p_v_static = dynamic_cast<StaticV *>(behaviors[i])) != NULL) {
                        v_steering = p_v_static->getPosIncr(ticks);
                        if (v_steering.first) {
                                n_v_static++;
                                v_static.push_back(v_steering.second);
                        }
                }
                if ((p_v_directkinematic = dynamic_cast<DirectKinematicV *>(behaviors[i])) != NULL) {
                        v_steering = p_v_directkinematic->getVel(ticks);
                        if (v_steering.first) {
                                n_v_directkinematic++;
                                v_directkinematic.push_back(v_steering.second);
                        }
                }
                if ((p_v_kinematic = dynamic_cast<KinematicV *>(behaviors[i])) != NULL) {
                        v_steering = p_v_kinematic->getVelIncr(ticks);
                        if (v_steering.first) {
                                n_v_kinematic++;
                                v_kinematic.push_back(v_steering.second);
                        }
                }
                if ((p_v_dynamic = dynamic_cast<DynamicV *>(behaviors[i])) != NULL) {
                        v_steering = p_v_dynamic->getForce(ticks);
                        if (v_steering.first) {
                                n_v_dynamic++;
                                v_dynamic.push_back(v_steering.second);
                        }
                }

                if ((p_a_directstatic = dynamic_cast<DirectStaticA *>(behaviors[i])) != NULL) {
                        a_steering = p_a_directstatic->getAng(ticks);
                        if (a_steering.first) {
                                n_v_directstatic++;
                                a_directstatic.push_back(a_steering.second);
                        }
                }
                if ((p_a_static = dynamic_cast<StaticA *>(behaviors[i])) != NULL) {
                        a_steering = p_a_static->getAngIncr(ticks);
                        if (a_steering.first) {
                                n_v_static++;
                                a_static.push_back(a_steering.second);
                        }
                }
                if ((p_a_directkinematic = dynamic_cast<DirectKinematicA *>(behaviors[i])) != NULL) {
                        a_steering = p_a_directkinematic->getAngVel(ticks);
                        if (a_steering.first) {
                                n_v_directkinematic++;
                                a_directkinematic.push_back(a_steering.second);
                        }
                }
                if ((p_a_kinematic = dynamic_cast<KinematicA *>(behaviors[i])) != NULL) {
                        a_steering = p_a_kinematic->getAngVelIncr(ticks);
                        if (a_steering.first) {
                                n_v_kinematic++;
                                a_kinematic.push_back(a_steering.second);
                        }
                }
                if ((p_a_dynamic = dynamic_cast<DynamicA *>(behaviors[i])) != NULL) {
                        a_steering = p_a_dynamic->getTorque(ticks);
                        if (a_steering.first) {
                                n_v_dynamic++;
                                a_dynamic.push_back(a_steering.second);
                        }
                }
        }

        if (n_v_directstatic) {
                for (i = 0; i < n_v_directstatic; i++) {
                        sum_v_directstatic += v_directstatic[i];
                }
                // NOTA: se SUSTITUYE la posición actual
                this->pos = sum_v_directstatic / n_v_directstatic;
        }

        if (n_v_directkinematic) {
                for (i = 0; i < n_v_directkinematic; i++) {
                        sum_v_directkinematic += v_directkinematic[i];
                }
                // NOTA: se SUSTITUYE la velocidad actual
                this->vel  = sum_v_directkinematic;
        }

        if (n_v_dynamic) {
                for (i = 0; i < n_v_dynamic; i++) {
                        sum_v_dynamic += v_dynamic[i];
                }
                // Δv = t * ΣF / m
                // TODO: mass
                this->vel  += sum_v_dynamic * (double)ticks;
        }

        if (n_v_kinematic) {
                for (i = 0; i < n_v_kinematic; i++) {
                        sum_v_kinematic += v_kinematic[i];
                }
                this->vel  += sum_v_kinematic;
        }

        if (n_v_static) {
                for (i = 0; i < n_v_static; i++) {
                        sum_v_static += v_static[i];
                }
                this->pos += sum_v_static;
        }

        if (n_a_directstatic) {
                for (i = 0; i < n_a_directstatic; i++) {
                        sum_a_directstatic += a_directstatic[i];
                }
                // NOTA: se SUSTITUYE el ángulo actual
                this->ang = sum_a_directstatic / n_a_directstatic;
        }

        if (n_a_directkinematic) {
                for (i = 0; i < n_a_directkinematic; i++) {
                        sum_a_directkinematic += a_directkinematic[i];
                }
                // NOTA: se SUSTITUYE la velocidad angular actual
                this->vrot = sum_a_directkinematic;
        }

        if (n_a_dynamic) {
                for (i = 0; i < n_a_dynamic; i++) {
                        sum_a_dynamic += a_dynamic[i];
                }
                // Δw = t * ΣT / I
                // TODO: mass
                this->vrot += sum_a_dynamic * ticks;
        }

        if (n_a_kinematic) {
                for (i = 0; i < n_a_kinematic; i++) {
                        sum_a_kinematic += a_kinematic[i];
                }
                this->vrot += sum_a_kinematic;
        }

        if (n_a_static) {
                for (i = 0; i < n_a_static; i++) {
                        sum_a_static += a_static[i];
                }
                this->ang += sum_a_static;
        }

#ifdef DEBUG_ACTOR
        printf("actor %p: final vel = ", this);
        this->vel.print();
        printf(", vrot = %f>\n", this->vrot);
#endif

        // roce; si se hace un salto, chequear que estés en el piso
        // TODO: 
        if (this->pos.z != 0) this->vel  += Triple(this->vel.x, this->vel.y, 0) * (-0.005) * static_cast<double>(ticks);
        this->vrot += this->vrot                          * (-0.030) * static_cast<double>(ticks);

        this->pos  += this->vel  * static_cast<double>(ticks);
        this->ang  += this->vrot * static_cast<double>(ticks);
        this->ang   = mapToRange(this->ang);

        // TODO: piratería para que el salto funcione
        this->pos.z = 0;
        this->vel.z = 0;
}
