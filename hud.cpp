#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>

#include "game.hpp"
#include "gl.hpp"
#include "hud.hpp"

#include "Window.hpp"
#include "FilledWindow.hpp"
#include "Tabs.hpp"
#include "Tab.hpp"
#include "Label.hpp"
#include "Image.hpp"

void make_hud() {
        Image * img;
        Label * l  ;
        {
                hud_state = HUDState::Inicio;
                hud_states.push_back(new std::list<HUDElement *>());

                FilledWindow * fw = new FilledWindow(
                        24, 18,
                        20, 96, 20, 250,
                        HUDElement::Highlighting::scale_wobble,
                        nullptr,
                        "inicial",
                        HUDElement::Visibility::visible
                );

                l = new Label(
                        "Bienvenido a",
                        0.025, 2,
                        0, 0, 0, 255,
                        Label::Alignment::center,
                        HUDElement::Highlighting::scale_wobble,
                        fw,
                        "título (línea 1)",
                        HUDElement::Visibility::visible,
                        Triple(0, 3.5, -0.1)
                );
                fw->children.push_back(l);

                l = new Label(
                        "Tamagotchi",
                        0.025, 3.5,
                        0, 0, 0, 255,
                        Label::Alignment::center,
                        HUDElement::Highlighting::scale_wobble,
                        fw,
                        "título (línea 2)",
                        HUDElement::Visibility::visible,
                        Triple(0, 2, -0.1)
                );
                fw->children.push_back(l);

                img = new Image(
                        "tamagotchi_icons/mantenimiento/aceptar.png",
                        2, 2,
                        255,
                        HUDElement::Highlighting::scale_wobble,
                        fw,
                        "inicio->aceptar",
                        HUDElement::Visibility::visible,
                        Triple(0, -1, -0.1)
                );
                img->set_callback_leftclick ([](HUDElement * self) { hud_state = HUDState::Juego   ; });
                img->set_callback_rightclick([](HUDElement * self) { hud_state = HUDState::Registro; });
                fw->children.push_back(img);

                hud_states[HUDSTATE]->push_back(fw);
        }



        {
                hud_state = HUDState::Registro;
                hud_states.push_back(new std::list<HUDElement *>());

                Tabs * tabcitos = new Tabs(
                        14, 16,
                        1,
                        nullptr, nullptr,
                        5,
                        20, 96, 20, 255,
                        Tabs::Hideable::no,
                        HUDElement::Highlighting::scale_wobble,
                        nullptr,
                        "tabs de registro",
                        HUDElement::Visibility::visible,
                        Triple(9, -0.5, 0)
                );

                tabcitos->headers[0]->children.push_back(new FilledWindow(1, 1, 255,   0,   0, 200, HUDElement::Highlighting::scale_wobble, tabcitos->headers[0], "tab[0]->header", HUDElement::Visibility::visible));
                tabcitos->headers[1]->children.push_back(new FilledWindow(1, 1,   0, 255,   0, 200, HUDElement::Highlighting::scale_wobble, tabcitos->headers[0], "tab[0]->header", HUDElement::Visibility::visible));
                tabcitos->headers[2]->children.push_back(new FilledWindow(1, 1,   0,   0, 255, 200, HUDElement::Highlighting::scale_wobble, tabcitos->headers[0], "tab[0]->header", HUDElement::Visibility::visible));
                tabcitos->headers[3]->children.push_back(new FilledWindow(1, 1, 255,   0, 255, 200, HUDElement::Highlighting::scale_wobble, tabcitos->headers[0], "tab[0]->header", HUDElement::Visibility::visible));
                tabcitos->headers[4]->children.push_back(new FilledWindow(1, 1, 255, 255,   0, 200, HUDElement::Highlighting::scale_wobble, tabcitos->headers[0], "tab[0]->header", HUDElement::Visibility::visible));

                tabcitos->pages[0]->children.push_back(new Label("Tab 0", 0.025, 5, 0, 0, 0, 255, Label::Alignment::center, HUDElement::Highlighting::scale_wobble, tabcitos->pages[0]));
                tabcitos->pages[1]->children.push_back(new Label("Tab 1", 0.025, 5, 0, 0, 0, 255, Label::Alignment::center, HUDElement::Highlighting::scale_wobble, tabcitos->pages[0]));
                tabcitos->pages[2]->children.push_back(new Label("Tab 2", 0.025, 5, 0, 0, 0, 255, Label::Alignment::center, HUDElement::Highlighting::scale_wobble, tabcitos->pages[0]));
                tabcitos->pages[3]->children.push_back(new Label("Tab 3", 0.025, 5, 0, 0, 0, 255, Label::Alignment::center, HUDElement::Highlighting::scale_wobble, tabcitos->pages[0]));
                tabcitos->pages[4]->children.push_back(new Label("Tab 4", 0.025, 5, 0, 0, 0, 255, Label::Alignment::center, HUDElement::Highlighting::scale_wobble, tabcitos->pages[0]));

                tabcitos->active_page = 0;

                hud_states[HUDSTATE]->push_back(tabcitos);
        }



        {
                hud_state = HUDState::Juego;
                hud_states.push_back(new std::list<HUDElement *>());

                Tabs * tabcitos = new Tabs(
                        32, 6,
                        2,
#define PEKOMIN_DRAWER_TABS_HEADER_CALLBACK(visibility, op)                              \
[](HUDElement * e) {                                                             \
auto ts = dynamic_cast<Tabs *>(e);                                       \
std::for_each(                                                           \
        ts->headers.begin(),                                             \
        ts->headers.end  (),                                             \
        [](FilledWindow * h) { h->visible = visibility; }                \
);                                                                       \
ts->headers[ts->active_page]->visible = HUDElement::Visibility::visible; \
ts->headers[ts->active_page]->pos.y op ts->height;                       \
ts->pages  [ts->active_page]->pos.y op ts->height;                       \
}
                        PEKOMIN_DRAWER_TABS_HEADER_CALLBACK(HUDElement::Visibility::hidden , +=),
                        PEKOMIN_DRAWER_TABS_HEADER_CALLBACK(HUDElement::Visibility::visible, -=),
#undef PEKOMIN_DRAWER_TABS_CALLBACK
                        3,
                        20, 96, 20, 255,
                        Tabs::Hideable::yes,
                        HUDElement::Highlighting::scale_wobble,
                        nullptr,
                        "tabs de abajo",
                        HUDElement::Visibility::visible,
                        Triple(0, -13, 0)
                );

                hud_states[HUDSTATE]->push_back(tabcitos);
        }



        {
                hud_state = HUDState::Relaciones;
                hud_states.push_back(new std::list<HUDElement *>());
        }

        hud_state = HUDState::Inicio;
}
