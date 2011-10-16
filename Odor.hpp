#ifndef ODOR_HPP
#define ODOR_HPP

#include <string>

#include "Ent.hpp"
#include "Triple.hpp"

#define DEFAULT_ODOR_LIFETIME  5000
#define DEFAULT_ODOR_INTENSITY 1
#define DEFAULT_ODOR_SPREAD    1

class Odor : public Ent {
        public:
                unsigned int lifetime;
                double intensity;
                double spread;
                unsigned int accum;

                Odor(std::string name = "", Triple pos = Triple(), unsigned int lifetime = DEFAULT_ODOR_LIFETIME, double intensity = DEFAULT_ODOR_INTENSITY, double spread = DEFAULT_ODOR_SPREAD);

                virtual void draw() const;
                virtual void steer(unsigned int ticks, unsigned int delta_ticks);
                virtual void update();
};

#endif
