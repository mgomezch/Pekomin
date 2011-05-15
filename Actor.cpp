#include "Actor.hpp"

#define DEBUG_ACTOR

#ifdef DEBUG_ACTOR
#include <stdio.h>
#endif

using namespace std;

void Actor::update(unsigned int ticks) {
        unsigned int i;

        vector<tuple<bool, Triple, double>> v_directstatic,
                                            v_static,
                                            v_directkinematic,
                                            v_kinematic,
                                            v_dynamic;

        Triple sum_directstatic_t    = Triple(0, 0, 0),
               sum_static_t          = Triple(0, 0, 0),
               sum_directkinematic_t = Triple(0, 0, 0),
               sum_kinematic_t       = Triple(0, 0, 0),
               sum_dynamic_t         = Triple(0, 0, 0);

        double sum_directstatic_d    = 0,
               sum_static_d          = 0,
               sum_directkinematic_d = 0,
               sum_kinematic_d       = 0,
               sum_dynamic_d         = 0;

        tuple<bool, Triple, double> steering;

        unsigned int n_directstatic    = 0,
                     n_static          = 0,
                     n_directkinematic = 0,
                     n_kinematic       = 0,
                     n_dynamic         = 0;

        unsigned int family;

        for (i = 0; i < behaviors.size(); i++) {
                family = behaviors[i]->family();
                if (family & BEHAVIOR_FAMILY_DIRECTSTATIC) {
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d is direct static\n", this, i);
#endif
                        steering = static_cast<DirectStatic*>(behaviors[i])->getPos();
                        if (get<0>(steering)) {
                                n_directstatic++;
                                v_directstatic.push_back(steering);
                        }
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d: steering: <%s, ", this, i, get<0>(steering) ? "true" : "false");
                        get<1>(steering).print();
                        printf(", %f>\n", get<2>(steering));
#endif
                }
                if (family & BEHAVIOR_FAMILY_STATIC) {
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d is static\n", this, i); // DEBUG_ACTOR
#endif
                        steering = static_cast<Static*>(behaviors[i])->getPosIncr();
                        if (get<0>(steering)) {
                                n_static++;
                                v_static.push_back(steering);
                        }
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d: steering: <%s, ", this, i, get<0>(steering) ? "true" : "false");
                        get<1>(steering).print();
                        printf(", %f>\n", get<2>(steering));
#endif
                }
                if (family & BEHAVIOR_FAMILY_DIRECTKINEMATIC) {
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d is direct kinematic\n", this, i); // DEBUG_ACTOR
#endif
                        steering = static_cast<DirectKinematic*>(behaviors[i])->getVel();
                        if (get<0>(steering)) {
                                n_directkinematic++;
                                v_directkinematic.push_back(steering);
                        }
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d: steering: <%s, ", this, i, get<0>(steering) ? "true" : "false");
                        get<1>(steering).print();
                        printf(", %f>\n", get<2>(steering));
#endif
                }
                if (family & BEHAVIOR_FAMILY_KINEMATIC) {
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d is kinematic\n", this, i); // DEBUG_ACTOR
#endif
                        steering = static_cast<Kinematic*>(behaviors[i])->getVelIncr();
                        if (get<0>(steering)) {
                                n_kinematic++;
                                v_kinematic.push_back(steering);
                        }
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d: steering: <%s, ", this, i, get<0>(steering) ? "true" : "false");
                        get<1>(steering).print();
                        printf(", %f>\n", get<2>(steering));
#endif
                }
                if (family & BEHAVIOR_FAMILY_DYNAMIC) {
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d: dynamic\n", this, i); // DEBUG_ACTOR
#endif
                        steering = static_cast<Dynamic*>(behaviors[i])->getForceIncr();
                        if (get<0>(steering)) {
                                n_dynamic++;
                                v_dynamic.push_back(steering);
                        }
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d: steering: <%s, ", this, i, get<0>(steering) ? "true" : "false");
                        get<1>(steering).print();
                        printf(", %f>\n", get<2>(steering));
#endif
                }
        }

        if (n_directstatic) {
                for (i = 0; i < n_directstatic; i++) {
                        sum_directstatic_t += get<1>(v_directstatic[i]);
                        sum_directstatic_d += get<2>(v_directstatic[i]);
                }
                // NOTA: se SUSTITUYE la posición actual
                this->pos = sum_directstatic_t / n_directstatic;
                this->ang = sum_directstatic_d / n_directstatic;
        }

        if (n_directkinematic) {
                for (i = 0; i < n_directkinematic; i++) {
                        sum_directkinematic_t += get<1>(v_directkinematic[i]);
                        sum_directkinematic_d += get<2>(v_directkinematic[i]);
                }
                // NOTA: se SUSTITUYE la velocidad actual
                this->vel  = sum_directkinematic_t;
                this->vrot = sum_directkinematic_d;
        }

        if (n_dynamic) {
                for (i = 0; i < n_dynamic; i++) {
                        sum_dynamic_t += get<1>(v_dynamic[i]);
                        sum_dynamic_d += get<2>(v_dynamic[i]);
                }
                // Δv = t * ΣF / m
                // TODO: mass
                this->vel  += sum_dynamic_t * (double)ticks;
                this->vrot += sum_dynamic_d *         ticks;
        }

        if (n_kinematic) {
                for (i = 0; i < n_kinematic; i++) {
                        sum_kinematic_t += get<1>(v_kinematic[i]);
                        sum_kinematic_d += get<2>(v_kinematic[i]);
                }
                this->vel  += sum_kinematic_t;
                this->vrot += sum_kinematic_d;
        }

        if (n_static) {
                for (i = 0; i < n_static; i++) {
                        sum_static_t += get<1>(v_static[i]);
                        sum_static_d += get<2>(v_static[i]);
                }
                this->pos += sum_static_t;
                this->ang += sum_static_d;
        }

#ifdef DEBUG_ACTOR
        printf("actor %p: final vel = ", this);
        this->vel.print();
        printf(", vrot = %f>\n", this->vrot);
#endif
        this->pos += this->vel  * (double)ticks;
        this->ang += this->vrot *         ticks;
}
