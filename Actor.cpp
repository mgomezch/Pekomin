#include "Actor.hpp"

using namespace std;

void Actor::update(unsigned int ticks) {
        int i;

        vector<tuple<bool, Triple, double>> v_direct,
                                            v_static,
                                            v_kinematic,
                                            v_dynamic;

        Triple avg_direct_t    = Triple(0, 0, 0),
               avg_static_t    = Triple(0, 0, 0),
               avg_kinematic_t = Triple(0, 0, 0),
               avg_dynamic_t   = Triple(0, 0, 0);

        double avg_direct_d    = 0,
               avg_static_d    = 0,
               avg_kinematic_d = 0,
               avg_dynamic_d   = 0;

        tuple<bool, Triple, double> steering;

        unsigned int n_direct    = 0,
                     n_static    = 0,
                     n_kinematic = 0,
                     n_dynamic   = 0;

        unsigned int family;

        for (i = 0; i < behaviors.size(); i++) {
                family = behaviors[i]->family();
                if (family == BEHAVIOR_FAMILY_DIRECT) {
                        steering = static_cast<Direct*>(behaviors[i])->getPos();
                        if (get<0>(steering)) {
                                n_direct++;
                                v_direct.push_back(steering);
                        }
                }
                if (family == BEHAVIOR_FAMILY_STATIC) {
                        steering = static_cast<Static*>(behaviors[i])->getPosIncr();
                        if (get<0>(steering)) {
                                n_static++;
                                v_static.push_back(steering);
                        }
                }
                if (family == BEHAVIOR_FAMILY_KINEMATIC) {
                        steering = static_cast<Kinematic*>(behaviors[i])->getVelIncr();
                        if (get<0>(steering)) {
                                n_kinematic++;
                                v_kinematic.push_back(steering);
                        }
                }
                if (family == BEHAVIOR_FAMILY_DYNAMIC) {
                        steering = static_cast<Dynamic*>(behaviors[i])->getForceIncr();
                        if (get<0>(steering)) {
                                n_dynamic++;
                                v_dynamic.push_back(steering);
                        }
                }
        }

        for (i = 0; i < n_direct; i++) {
                avg_direct_t += get<1>(v_direct[i]);
                avg_direct_d += get<2>(v_direct[i]);
        }
        avg_direct_t /= n_direct;
        avg_direct_d /= n_direct;

        for (i = 0; i < n_static; i++) {
                avg_static_t += get<1>(v_static[i]);
                avg_static_d += get<2>(v_static[i]);
        }
        avg_static_t /= n_static;
        avg_static_d /= n_static;

        for (i = 0; i < n_kinematic; i++) {
                avg_kinematic_t += get<1>(v_kinematic[i]);
                avg_kinematic_d += get<2>(v_kinematic[i]);
        }
        avg_kinematic_t /= n_kinematic;
        avg_kinematic_d /= n_kinematic;

        for (i = 0; i < n_dynamic; i++) {
                avg_dynamic_t += get<1>(v_dynamic[i]);
                avg_dynamic_d += get<2>(v_dynamic[i]);
        }
        avg_dynamic_t /= n_dynamic;
        avg_dynamic_d /= n_dynamic;
	
	/*
        pos += vel * time;
        ang += vrot * time;
        vel += behaviors[i].get<2>(steering) * time;
        ang += behaviors[i].get<3>(steering) * time;

       
        int i;
        vector<>;

        for (i = 0; i < behaviors.size; i++) {
               if () behavior->type()
        }
        */
}
