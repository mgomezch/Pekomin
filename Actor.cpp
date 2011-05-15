#include "Actor.hpp"

#ifdef DEBUG_ACTOR
#include <stdio.h>
#endif

using namespace std;

void Actor::update(unsigned int ticks) {
        unsigned int i;
	int flag = 0;

        vector<tuple<bool, Triple, double>> v_direct,
                                            v_static,
                                            v_kinematic,
                                            v_dynamic;

        Triple sum_direct_t    = Triple(0, 0, 0),
               sum_static_t    = Triple(0, 0, 0),
               sum_kinematic_t = Triple(0, 0, 0),
               sum_dynamic_t   = Triple(0, 0, 0);

        double sum_direct_d    = 0,
               sum_static_d    = 0,
               sum_kinematic_d = 0,
               sum_dynamic_d   = 0;

        tuple<bool, Triple, double> steering;

        unsigned int n_direct    = 0,
                     n_static    = 0,
                     n_kinematic = 0,
                     n_dynamic   = 0;

        unsigned int family;

        for (i = 0; i < behaviors.size(); i++) {
                family = behaviors[i]->family();
                if (family & BEHAVIOR_FAMILY_DIRECT) {
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d is direct\n", this, i);
#endif
                        steering = static_cast<Direct*>(behaviors[i])->getPos();
                        if (get<0>(steering)) {
                                n_direct++;
                                v_direct.push_back(steering);
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
                if (family & BEHAVIOR_FAMILY_KINEMATIC) {
#ifdef DEBUG_ACTOR
                        printf("actor %p: behavior %d is kinematic\n", this, i); // DEBUG_ACTOR
#endif
                        steering = static_cast<Kinematic*>(behaviors[i])->getVelIncr();
                        if (get<0>(steering)) {
                                n_kinematic++;
                                v_kinematic.push_back(steering);
                        }
			if (behaviors[i]->type() == BEHAVIOR_ARRIVE) flag = 1;
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

        if (n_direct) {
                for (i = 0; i < n_direct; i++) {
                        sum_direct_t += get<1>(v_direct[i]);
                        sum_direct_d += get<2>(v_direct[i]);
                }
                // NOTA: se SUSTITUYE la posición actual
                this->pos = sum_direct_t / n_direct;
                this->ang = sum_direct_d / n_direct;
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
                // NOTA: deberían ser += en vez de =, pero pa que lo del libro sirva tiene que ser así :(
                this->vel  = sum_kinematic_t;
                this->vrot = sum_kinematic_d;

		if (flag == 1) {
        		this->pos += this->vel ;
        		this->ang += this->vrot;
		}
        }

        if (n_static) {
                for (i = 0; i < n_static; i++) {
                        sum_static_t += get<1>(v_static[i]);
                        sum_static_d += get<2>(v_static[i]);
                }
                this->pos += sum_static_t;
                this->ang += sum_static_d;
        }

	if (flag == 0) {
		this->pos += this->vel ;
		this->ang += this->vrot; 
	}

}
