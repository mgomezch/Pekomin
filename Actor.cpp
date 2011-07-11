#include <utility>

#include "Actor.hpp"
#include "Families.hpp"
#include "Mobile.hpp"
#include "Player.hpp" // TODO: quitar esto y quitar la piratería del salto
#include "Triple.hpp"
#include "util.hpp"

//#define DEBUG_ACTOR

#ifdef DEBUG_ACTOR
#include <iostream>
#include <stdio.h>
#endif

#define RUN_V_STEERING(FAMILY, CALL)                                                              \
        if (behaviors[i]->active) {                                                                \
                if ((( p_ ## FAMILY ) = dynamic_cast< FAMILY *>(behaviors[i])) != NULL) { \
                        v_steering = ( p_ ## FAMILY )-> CALL (ticks);                             \
                        if (v_steering.first) {                                                   \
                                ( n_ ## FAMILY )++;                                               \
                                ( v_ ## FAMILY ).push_back(v_steering.second);                    \
                        }                                                                         \
                }                                                                                 \
        }

#define RUN_A_STEERING(FAMILY, CALL)                                                              \
        if (behaviors[i]->active) {                                                                \
                if ((( p_ ## FAMILY ) = dynamic_cast< FAMILY *>(behaviors[i])) != NULL) { \
                        a_steering = ( p_ ## FAMILY )-> CALL (ticks);                             \
                        if (a_steering.first) {                                                   \
                                ( n_ ## FAMILY )++;                                               \
                                ( v_ ## FAMILY ).push_back(a_steering.second);                    \
                        }                                                                         \
                }                                                                                 \
        }

using namespace std;

Actor::Actor(string name, Triple pos, double ang, Triple vel, double vrot):
        Mobile(name, pos, ang, vel, vrot)
{}

Behavior &Actor::addBehavior(Behavior *b) {
        behaviors.push_back(b);
#ifdef DEBUG_ACTOR
        cout << "actor " << static_cast<void>(this) << " : adding behavior " << static_cast<void *>(b) << endl;
#endif
        return *(behaviors.back());
}

void Actor::steer(unsigned int ticks) {
        unsigned int i;
        Triple vdir;

        DirectStaticV    *p_DirectStaticV   ;
        StaticV          *p_StaticV         ;
        DirectKinematicV *p_DirectKinematicV;
        KinematicV       *p_KinematicV      ;
        DynamicV         *p_DynamicV        ;

        DirectStaticA    *p_DirectStaticA   ;
        StaticA          *p_StaticA         ;
        DirectKinematicA *p_DirectKinematicA;
        KinematicA       *p_KinematicA      ;
        DynamicA         *p_DynamicA        ;

        vector<Triple> v_DirectStaticV   ,
                       v_StaticV         ,
                       v_DirectKinematicV,
                       v_KinematicV      ,
                       v_DynamicV        ;

        vector<double> v_DirectStaticA   ,
                       v_StaticA         ,
                       v_DirectKinematicA,
                       v_KinematicA      ,
                       v_DynamicA        ;

        Triple sum_DirectStaticV    = Triple(0, 0, 0),
               sum_StaticV          = Triple(0, 0, 0),
               sum_DirectKinematicV = Triple(0, 0, 0),
               sum_KinematicV       = Triple(0, 0, 0),
               sum_DynamicV         = Triple(0, 0, 0);

        double sum_DirectStaticA    = 0,
               sum_StaticA          = 0,
               sum_DirectKinematicA = 0,
               sum_KinematicA       = 0,
               sum_DynamicA         = 0;

        pair<bool, Triple> v_steering;
        pair<bool, double> a_steering;

        unsigned int n_DirectStaticV    = 0,
                     n_StaticV          = 0,
                     n_DirectKinematicV = 0,
                     n_KinematicV       = 0,
                     n_DynamicV         = 0,
                     n_DirectStaticA    = 0,
                     n_StaticA          = 0,
                     n_DirectKinematicA = 0,
                     n_KinematicA       = 0,
                     n_DynamicA         = 0;

        this->ang = mapToRange(this->ang);

        for (i = 0; i < behaviors.size(); i++) {
                RUN_V_STEERING(DirectStaticV   , getPos    )
                RUN_V_STEERING(StaticV         , getPosIncr)
                RUN_V_STEERING(DirectKinematicV, getVel    )
                RUN_V_STEERING(KinematicV      , getVelIncr)
                RUN_V_STEERING(DynamicV        , getForce  )

                RUN_A_STEERING(DirectStaticA   , getAng       )
                RUN_A_STEERING(StaticA         , getAngIncr   )
                RUN_A_STEERING(DirectKinematicA, getAngVel    )
                RUN_A_STEERING(KinematicA      , getAngVelIncr)
                RUN_A_STEERING(DynamicA        , getTorque    )
        }

        for (i = 0; i < n_DirectStaticV   ; i++) sum_DirectStaticV    += v_DirectStaticV[i];
        for (i = 0; i < n_DirectKinematicV; i++) sum_DirectKinematicV += v_DirectKinematicV[i];
        for (i = 0; i < n_DynamicV        ; i++) sum_DynamicV         += v_DynamicV[i];
        for (i = 0; i < n_KinematicV      ; i++) sum_KinematicV       += v_KinematicV[i];
        for (i = 0; i < n_StaticV         ; i++) sum_StaticV          += v_StaticV[i];

        for (i = 0; i < n_DirectStaticA   ; i++) sum_DirectStaticA    += v_DirectStaticA[i];
        for (i = 0; i < n_DirectKinematicA; i++) sum_DirectKinematicA += v_DirectKinematicA[i];
        for (i = 0; i < n_DynamicA        ; i++) sum_DynamicA         += v_DynamicA[i];
        for (i = 0; i < n_KinematicA      ; i++) sum_KinematicA       += v_KinematicA[i];
        for (i = 0; i < n_StaticA         ; i++) sum_StaticA          += v_StaticA[i];

        this->new_pos  = this->pos;
        this->new_ang  = this->ang;
        this->new_vel  = this->vel;
        this->new_vrot = this->vrot;

        if (n_DirectStaticV   ) this->new_pos   = sum_DirectStaticV / n_DirectStaticV;
        if (n_DirectKinematicV) this->new_vel   = sum_DirectKinematicV;
        if (n_DynamicV        ) this->new_vel  += sum_DynamicV * (double)ticks; // TODO: divide by mass
        if (n_KinematicV      ) this->new_vel  += sum_KinematicV;
        if (n_StaticV         ) this->new_pos  += sum_StaticV;

        if (n_DirectStaticA   ) this->new_ang   = sum_DirectStaticA / n_DirectStaticA;
        if (n_DirectKinematicA) this->new_vrot  = sum_DirectKinematicA;
        if (n_DynamicA        ) this->new_vrot += sum_DynamicA * ticks; // TODO: divide by inertia
        if (n_KinematicA      ) this->new_vrot += sum_KinematicA;
        if (n_StaticA         ) this->new_ang  += sum_StaticA;

#ifdef DEBUG_ACTOR
        cout << "actor " << this->name << ": final vel == " << this->new_vel.to_string() << ", vrot == " << this->new_vrot << endl;
#endif

        // TODO: chequear que estés en el piso antes de calcular roce
        if (this->new_pos.z == 0) {
                vdir = this->new_vel.normalized();
                this->new_vel += Triple(this->new_vel.x, this->new_vel.y, 0) * (-0.005) * static_cast<double>(ticks);
                if (vdir.dot(this->new_vel) < 0) this->new_vel = Triple(0, 0, 0);

                if      (this->new_vrot > 0 && (this->new_vrot += this->new_vrot * (-0.030) * static_cast<double>(ticks)) < 0) this->new_vrot = 0;
                else if (this->new_vrot < 0 && (this->new_vrot += this->new_vrot * (-0.030) * static_cast<double>(ticks)) > 0) this->new_vrot = 0;
        }

        this->new_pos += this->new_vel  * static_cast<double>(ticks);
        this->new_ang += this->new_vrot * static_cast<double>(ticks);
        this->new_ang  = mapToRange(this->new_ang);

        // TODO: piratería para que el salto funcione
        // BUG: esto hace que la diferencia de posición vertical produzca distancias grandes en los comportamientos a pesar de que el movimiento se hace solo en un plano... las distancias deberían, en cambio, calcularse en base al plano!
        if (dynamic_cast<Player *>(this) == NULL) {
                this->new_pos.z = 0;
                this->new_vel.z = 0;
        }
}

void Actor::update() {
        this->pos  = this->new_pos;
        this->ang  = this->new_ang;
        this->vel  = this->new_vel;
        this->vrot = this->new_vrot;
}
