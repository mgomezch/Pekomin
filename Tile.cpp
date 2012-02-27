#if PEKOMIN_GRAFO

#include "Tile.hpp"
#include "Triple.hpp"
#include "gl.hpp"

Tile::Tile(Triple pos) {
        this->pos    = pos ;
        this->active = true;
}

void Tile::draw() const {
        glPushMatrix();
                if (active) {
                        glColor4ub(0, 139, 139, 200);
                } else {
                        glColor4ub(143, 188, 143, 200);
                }
                glCallList(cuadrado_simple);
        glPopMatrix();
}

#endif
