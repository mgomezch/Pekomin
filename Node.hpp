#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <list>
#include <tuple>

#include "Ent.hpp"
#include "Triple.hpp"

class Node : public Ent {
        public:
                std::list<Node *> adj;
                std::list<std::tuple <Ent *, double> > mods;

                Node(std::string name = "", Triple pos = Triple());

                void add_adj(Node *node);
                bool is_adj(Node *adj);
                void print_adj();
                void print_node();
                void add_mod(Ent *e, double c);

                virtual void draw() const;
                virtual void steer(unsigned int ticks, unsigned int delta_ticks);
                virtual void update();
};

std::tuple<Triple, Triple> points(Node *n1, Node *n2);

#endif
