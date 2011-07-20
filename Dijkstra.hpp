#ifndef _DIJKSTRA_HPP_
#define _DIJKSTRA_HPP_

#include <vector>

#include "Ent.hpp"
#include "Node.hpp"

std::vector<Node *> dijkstra(Ent *e, Node *begin, Node *end);
double distanceNode(Ent *e, Node *n1, Node *n2);

#endif
