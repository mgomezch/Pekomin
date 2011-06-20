#ifndef _NODE_HPP
#define _NODE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include "Triple.hpp"
#include "Mobile.hpp"

using namespace std;

class Node : public Mobile {
        public :
                string id;
                //Triple pos;
                bool check;
                vector<tuple<Node*, bool, double> > adj;

                Node();
                Node(Triple pos);
                Node(string id, Triple pos);

                Triple get_Pos();
                bool is_Visited();
                void add_adj(tuple<Node*, bool, double> node);
                bool is_adj(Node *adj);
                void print_node();
                void print_adj();

                virtual void draw();
                virtual void update(unsigned int ticks);
};

#endif
