#ifndef PEKOMIN_WINDOW_HPP
#define PEKOMIN_WINDOW_HPP

#include <GL/gl.h>
#include <list>

#include "HUDElement.hpp"

class Window : public virtual HUDElement {
        public:
                std::list<HUDElement *> children;

                Window(std::string name);

                virtual void draw() const;
                virtual void update();

                virtual bool identify(GLuint uid);
};

#endif
