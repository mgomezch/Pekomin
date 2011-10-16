#ifndef RECOVERYPOINT_HPP
#define RECOVERYPOINT_HPP

#include "Actor.hpp"
#include "Triple.hpp"

class RecoveryPoint : public virtual Actor {
        public:
                bool active;

                RecoveryPoint(
                                std::string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0
                );

                virtual void draw() const;
};

#endif
