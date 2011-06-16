#include <utility>

#include "Actor.hpp"
#include "util.hpp"

//#define DEBUG_ACTOR

#ifdef DEBUG_ACTOR
#include <iostream>
#include <stdio.h>
#endif

#define RUN_V_STEERING(FAMILY, CALL)                                              \
        if ((( p_ ## FAMILY ) = dynamic_cast< FAMILY *>(behaviors[i])) != NULL) { \
                v_steering = ( p_ ## FAMILY )-> CALL (ticks);                     \
                if (v_steering.first) {                                           \
                        ( n_ ## FAMILY )++;                                       \
                        ( v_ ## FAMILY ).push_back(v_steering.second);            \
                }                                                                 \
        }

#define RUN_A_STEERING(FAMILY, CALL)                                              \
        if ((( p_ ## FAMILY ) = dynamic_cast< FAMILY *>(behaviors[i])) != NULL) { \
                a_steering = ( p_ ## FAMILY )-> CALL (ticks);                     \
                if (a_steering.first) {                                           \
                        ( n_ ## FAMILY )++;                                       \
                        ( v_ ## FAMILY ).push_back(a_steering.second);            \
                }                                                                 \
        }

using namespace std;

void Actor::update(unsigned int ticks) {
        unsigned int i;

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

        if (n_DirectStaticV   ) this->pos   = sum_DirectStaticV / n_DirectStaticV;
        if (n_DirectKinematicV) this->vel   = sum_DirectKinematicV;
        if (n_DynamicV        ) this->vel  += sum_DynamicV * (double)ticks; // TODO: divide by mass
        if (n_KinematicV      ) this->vel  += sum_KinematicV;
        if (n_StaticV         ) this->pos  += sum_StaticV;

        if (n_DirectStaticA   ) this->ang   = sum_DirectStaticA / n_DirectStaticA;
        if (n_DirectKinematicA) this->vrot  = sum_DirectKinematicA;
        if (n_DynamicA        ) this->vrot += sum_DynamicA * ticks; // TODO: divide by inertia
        if (n_KinematicA      ) this->vrot += sum_KinematicA;
        if (n_StaticA         ) this->ang  += sum_StaticA;

#ifdef DEBUG_ACTOR
        printf("actor %p: final vel = ", this);
        this->vel.print();
        printf(", vrot = %f>\n", this->vrot);
#endif

        // roce; si se hace un salto, chequear que estés en el piso
        if (this->pos.z == 0) this->vel += Triple(this->vel.x, this->vel.y, 0) * (-0.005) * static_cast<double>(ticks);
        this->vrot += this->vrot * (-0.030) * static_cast<double>(ticks);

        this->pos += this->vel  * static_cast<double>(ticks);
        this->ang += this->vrot * static_cast<double>(ticks);
        this->ang  = mapToRange(this->ang);

        // TODO: piratería para que el salto funcione
        this->pos.z = 0;
        this->vel.z = 0;
}
