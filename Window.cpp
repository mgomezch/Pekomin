#include <cmath>
#include <string>

#include "HUDElement.hpp"
#include "Window.hpp"

Window::Window(std::string name):
        HUDElement(name)
{}

void Window::draw() const {
        for (auto it = children.begin(); it != children.end(); ++it) {
                HUDElement * child;

                glPushMatrix();
                        child = *it;
                        glTranslatef(child->pos.x, child->pos.y, child->pos.z);
                        glRotatef((child->ang * 180.0)/M_PI, 0, 0, 1);
                        child->draw();
                glPopMatrix();
        }
}

void Window::update() {
        for (auto it = children.begin(); it != children.end(); ++it) {
                (*it)->update();
        }
}

bool Window::identify(GLuint uid) {
        return HUDElement::identify(uid); // TODO: ver todos los hijos
}
