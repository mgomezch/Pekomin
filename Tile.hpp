#ifndef TILE_HPP
#define TILE_HPP

#if PEKOMIN_GRAFO

#include "Triple.hpp"

class Tile {
        public:
                Triple pos;
                bool active;

                Tile(Triple pos = Triple());

                void draw() const;
};

#endif

#endif
