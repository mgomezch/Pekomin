#include "gl.hpp"
#include "Phantom.hpp"

#define DEBUG_PHANTOM

#ifdef DEBUG_PHANTOM
#       include <GL/freeglut.h>
#endif

void Phantom::draw() const {
#ifdef DEBUG_PHANTOM
        glColor3ub(255, 0, 255);
        glCallList(cubo);
#endif
}
