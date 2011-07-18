#ifndef ENT_HPP
#define ENT_HPP

#include <string>
#include <tuple>
#include <vector>

#include "Triple.hpp"

class Segment;
class SurfacePlane;
class VolumePlane;
class Box;

class Ent {
        public:
                std::string name;
                Triple pos;
                double ang;

                std::vector<Triple> normals;
                bool collides;
                bool dead;

                Ent(std::string name = "", Triple pos = Triple(), double ang = 0);
                virtual ~Ent() = 0;

                void addNormal(const Triple &n);
                void collide();

                virtual void draw() = 0;
                virtual void steer(unsigned int ticks, unsigned int delta_ticks) = 0;
                virtual void update() = 0;

                Triple orientation();

        protected:
                Triple new_pos;
                double new_ang;
};

std::tuple<Triple, Triple> points(Ent *e1, Ent *e2);

std::tuple<Triple, Triple> points(Segment      *s, SurfacePlane *f);
std::tuple<Triple, Triple> points(Segment      *s, VolumePlane  *v);
std::tuple<Triple, Triple> points(Segment      *s, Box          *b);
std::tuple<Triple, Triple> points(SurfacePlane *f, VolumePlane  *v);
std::tuple<Triple, Triple> points(SurfacePlane *f, Box          *b);
std::tuple<Triple, Triple> points(VolumePlane  *v, Box          *b);

std::tuple<Triple, Triple> points(SurfacePlane *p, Segment      *s);
std::tuple<Triple, Triple> points(VolumePlane  *p, Segment      *s);
std::tuple<Triple, Triple> points(Box          *s, Segment      *b);
std::tuple<Triple, Triple> points(VolumePlane  *v, SurfacePlane *s);
std::tuple<Triple, Triple> points(Box          *b, SurfacePlane *s);
std::tuple<Triple, Triple> points(Box          *b, VolumePlane  *v);

#endif
