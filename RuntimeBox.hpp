#ifndef RUNTIMEBOX_HPP
#define RUNTIMEBOX_HPP

#include <string>

#include "RuntimePoint.hpp"
#include "Box.hpp"

class RuntimeBox : public virtual RuntimePoint, public virtual Box {
        public:
                RuntimeBox(
                                std::string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                double sx = 0.5, double sy = 0.5, double sz = 0.5
                          );
                // TODO: destructor!

                virtual void draw();
};

#endif
