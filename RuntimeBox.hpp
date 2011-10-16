#ifndef RUNTIMEBOX_HPP
#define RUNTIMEBOX_HPP

#include <string>

#include "RuntimePoint.hpp"
#include "BBox.hpp"

class RuntimeBox : public virtual RuntimePoint, public virtual BBox {
        public:
                RuntimeBox(
                                std::string name = "",
                                Triple pos = Triple(), double ang  = 0,
                                Triple vel = Triple(), double vrot = 0,
                                double sx = 0.5, double sy = 0.5, double sz = 0.5
                          );
                // TODO: destructor!

                virtual void draw() const;
};

#endif
