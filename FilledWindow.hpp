#ifndef PEKOMIN_FILLEDWINDOW_HPP
#define PEKOMIN_FILLEDWINDOW_HPP

#include <GL/gl.h>
#include <list>

#include "FilledWindow.hpp"
#include "Window.hpp"

class FilledWindow : public virtual Window {
        public:
                double width, height;
                GLubyte color[4];

                FilledWindow(
                        std::string name,
                        double width,
                        double heigh,
                        GLubyte r = 255,
                        GLubyte g = 255,
                        GLubyte b = 255,
                        GLubyte a = 255
                );

                virtual void draw() const;

                virtual void set_color(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);

                virtual void set_opacity(GLubyte a);
};

#endif
