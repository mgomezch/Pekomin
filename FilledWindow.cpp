#include <cmath>
#include <string>

#include "HUDElement.hpp"
#include "FilledWindow.hpp"
#include "gl.hpp"

FilledWindow::FilledWindow(
        std::string name,
        double width,
        double height,
        GLubyte r,
        GLubyte g,
        GLubyte b,
        GLubyte a
):
        Window(name  ),
        width (width ),
        height(height),
        color({r, g, b, a})
{}

void FilledWindow::draw() const {
        glLoadName(select_uid);

        glPushMatrix();
                glScalef(width, height, 1);
                glColor4ubv(color);
                glCallList(cuadrado_simple);
        glPopMatrix();
        Window::draw();
}

void FilledWindow::set_color(
        GLubyte r,
        GLubyte g,
        GLubyte b,
        GLubyte a
) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        color[3] = a;
}

void FilledWindow::set_opacity(GLubyte a) {
        color[3] = a;
}
