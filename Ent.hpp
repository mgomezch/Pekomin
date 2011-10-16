#ifndef ENT_HPP
#define ENT_HPP

#include <string>
#include <tuple>
#include <vector>

#include "Triple.hpp"

class Segment;
class SurfacePlane;
class VolumePlane;
class BBox;

class Ent {
        public:
                std::string name;
                Triple pos;
                double ang;

                std::vector<Triple> normals;
                bool collides;
                bool dead;

                Triple new_pos;
                double new_ang;

                Ent(std::string name = "", Triple pos = Triple(), double ang = 0);
                virtual ~Ent() = 0;

                void addNormal(const Triple &n);
                void collide();

                virtual void draw() const = 0;
                virtual void steer(unsigned int ticks, unsigned int delta_ticks) = 0;
                virtual void update() = 0;

                const Triple orientation() const;
};

const std::tuple<const Triple, const Triple> points(const Ent * const e1, const Ent * const e2);

const std::tuple<const Triple, const Triple> points(const Segment      * const s, SurfacePlane * const f);
const std::tuple<const Triple, const Triple> points(const Segment      * const s, VolumePlane  * const v);
const std::tuple<const Triple, const Triple> points(const Segment      * const s, BBox          * const b);
const std::tuple<const Triple, const Triple> points(const SurfacePlane * const f, VolumePlane  * const v);
const std::tuple<const Triple, const Triple> points(const SurfacePlane * const f, BBox          * const b);
const std::tuple<const Triple, const Triple> points(const VolumePlane  * const v, BBox          * const b);

const std::tuple<const Triple, const Triple> points(const SurfacePlane * const p, Segment      * const s);
const std::tuple<const Triple, const Triple> points(const VolumePlane  * const p, Segment      * const s);
const std::tuple<const Triple, const Triple> points(const BBox          * const s, Segment      * const b);
const std::tuple<const Triple, const Triple> points(const VolumePlane  * const v, SurfacePlane * const s);
const std::tuple<const Triple, const Triple> points(const BBox          * const b, SurfacePlane * const s);
const std::tuple<const Triple, const Triple> points(const BBox          * const b, VolumePlane  * const v);

#endif
