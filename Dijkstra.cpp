#include "Dijkstra.hpp"

vector<Node *> dijkstra(Node *begin, Node *end) {
        stack<Node *> unvisited;
        vector<Node *> visited;
        Node *actual, *temp;
        double min_value, cost = 0.0;

        cout << "Inicio " << endl;
        begin->print_node();
        unvisited.push(begin);

        int k = 0;
        while (true) {
                if (!unvisited.empty()) {
                        cout << " iteration : " << k << endl;
                        k++;
                        actual = unvisited.top();
                        min_value = 1000000000;
                        if (!actual->adj.empty()) {
                                for (unsigned int i = 0; i < actual->adj.size(); i++) {
                                        if (!get<1>(actual->adj[i])) {
                                                get<1>(actual->adj[i]) = true;
                                                get<2>(actual->adj[i]) = distanceNode(actual, get<0>(actual->adj[i]));
                                        }       
                                }
                                for (unsigned int i = 0; i < actual->adj.size(); i++) {
                                        if (!get<0>(actual->adj[i])->is_Visited()) { 
                                                if (get<2>(actual->adj[i]) < min_value){
                                                        get<0>(actual->adj[i])->print_node();
                                                        min_value = get<2>(actual->adj[i]);
                                                        temp = get<0>(actual->adj[i]);
                                                }
                                        }
                                        else    {
                                                cout << "Visitado" << endl;
                                                continue;
                                        }
                                }
                        }

                        unvisited.pop();
                        actual->check = true;
                        visited.push_back(actual);
                        cost += min_value;
                        if (actual == end)
                                break;

                        unvisited.push(temp);       
                } 
        }
        return visited;
}

double distanceNode(Node *n1, Node *n2) {
        return ((n2->pos - n1->pos).length());        
}
