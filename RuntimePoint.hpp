#ifndef RUNTIMEPOINT_HPP
#define RUNTIMEPOINT_HPP

#include <string>

#include "Actor.hpp"
#include "Triple.hpp"

class RuntimePoint : public virtual Actor {
        public:
                RuntimePoint(
                                std::string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0
                            );
                // TODO: destructor!

                virtual void draw() const;
};

#endif
