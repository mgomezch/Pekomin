#ifndef PEKOMIN_TAB_HPP
#define PEKOMIN_TAB_HPP

#include <list>

#include "FilledWindow.hpp"

class Tab : public virtual FilledWindow {
        public:
                FilledWindow * header;
                FilledWindow * contents;

                double header_height;
                double header_start_pct;
                double header_end_pct;

                Tab(
                        std::string name,
                        double width,
                        double heigh,
                        double header_height,
                        double header_start_pct,
                        double header_end_pct,
                        GLubyte r = 255,
                        GLubyte g = 255,
                        GLubyte b = 255,
                        GLubyte a = 255
                );

                virtual ~Tab();

                virtual void draw() const;
                virtual void update();

                virtual void set_leftclick  (std::function<void(HUDElement *)>);
                virtual void set_middleclick(std::function<void(HUDElement *)>);
                virtual void set_rightclick (std::function<void(HUDElement *)>);

                virtual bool identify(GLuint uid);

                virtual void set_color(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);

                virtual void set_opacity(GLubyte a);
};

#endif
