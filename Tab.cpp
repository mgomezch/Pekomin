#include <cmath>
#include <string>

#include "Tab.hpp"
#include "FilledWindow.hpp"

#define PEKOMIN_ABS(x) ((x) >= 0 ? (x) : -(x))

Tab::Tab(
        std::string name,
        double width,
        double height,
        double header_height,
        double header_start_pct,
        double header_end_pct,
        GLubyte r,
        GLubyte g,
        GLubyte b,
        GLubyte a
):
        Window(name), // FIXME: wtf?
        FilledWindow(
                name,
                width,
                height,
                r,
                g,
                b,
                a
        ),
        header(
                new FilledWindow(
                        name + "->header",
                        PEKOMIN_ABS(header_end_pct - header_start_pct) * width,
                        header_height,
                        r,
                        g,
                        b,
                        a
                )
        ),
        contents(
                new FilledWindow(
                        name + "->contents",
                        width,
                        height,
                        r,
                        g,
                        b,
                        a
                )
        ),
        header_height(header_height),
        header_start_pct(header_start_pct),
        header_end_pct(header_end_pct)
{
        header->pos.x = -width/2.0 + PEKOMIN_ABS(header_end_pct - header_start_pct) * width/2.0 + header_start_pct * width,
        header->pos.y = (header_height + height)/2.0;
}

void Tab::draw() const {
        glPushMatrix();
                glTranslatef(header->pos.x, header->pos.y, header->pos.z);
                glRotatef((header->ang * 180.0)/M_PI, 0, 0, 1);
                header->draw();
        glPopMatrix();
        glPushMatrix();
                glTranslatef(contents->pos.x, contents->pos.y, contents->pos.z);
                glRotatef((contents->ang * 180.0)/M_PI, 0, 0, 1);
                contents->draw();
        glPopMatrix();
}

void Tab::update() {
        header->update();
        contents->update();
}

Tab::~Tab() {
        delete header;
        delete contents;
}

void Tab::set_leftclick  (std::function<void(HUDElement *)> callback) { leftclick   = header->leftclick   = contents->leftclick   = callback; }
void Tab::set_middleclick(std::function<void(HUDElement *)> callback) { middleclick = header->middleclick = contents->middleclick = callback; }
void Tab::set_rightclick (std::function<void(HUDElement *)> callback) { rightclick  = header->rightclick  = contents->rightclick  = callback; }

bool Tab::identify(GLuint uid) {
        return FilledWindow::identify(uid) || header->identify(uid) || contents->identify(uid);
}

void Tab::set_color(
        GLubyte r,
        GLubyte g,
        GLubyte b,
        GLubyte a
) {
        FilledWindow::set_color(r, g, b, a);
        header      ->set_color(r, g, b, a);
        contents    ->set_color(r, g, b, a);
}

void Tab::set_opacity(GLubyte a) {
        FilledWindow::set_opacity(a);
        header      ->set_opacity(a);
        contents    ->set_opacity(a);
}
