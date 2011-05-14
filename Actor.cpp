#include "Actor.hpp"

using namespace std;

void Actor::update(unsigned int ticks) {
        unsigned int i;

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
                        steering = static_cast<Direct*>(behaviors[i])->getPos();
                        if (get<0>(steering)) {
                                n_direct++;
                                v_direct.push_back(steering);
                        }
                }
                if (family & BEHAVIOR_FAMILY_STATIC) {
                        steering = static_cast<Static*>(behaviors[i])->getPosIncr();
                        if (get<0>(steering)) {
                                n_static++;
                                v_static.push_back(steering);
                        }
                }
                if (family & BEHAVIOR_FAMILY_KINEMATIC) {
                        steering = static_cast<Kinematic*>(behaviors[i])->getVelIncr();
                        if (get<0>(steering)) {
                                n_kinematic++;
                                v_kinematic.push_back(steering);
                        }
                }
                if (family & BEHAVIOR_FAMILY_DYNAMIC) {
                        steering = static_cast<Dynamic*>(behaviors[i])->getForceIncr();
                        if (get<0>(steering)) {
                                n_dynamic++;
                                v_dynamic.push_back(steering);
                        }
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
                this->vel  += sum_kinematic_t;
                this->vrot += sum_kinematic_d;
        }

        if (n_static) {
                for (i = 0; i < n_static; i++) {
                        sum_static_t += get<1>(v_static[i]);
                        sum_static_d += get<2>(v_static[i]);
                }
                this->pos += this->vel  * (double)ticks + sum_static_t;
                this->ang += this->vrot *         ticks + sum_static_d;
        }
}
