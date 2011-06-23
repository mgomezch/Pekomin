#include <tuple>
#include <vector>

#include "Node.hpp"
#include "Dijkstra.hpp"

vector<Node *> dijkstra(Node *begin, Node *end) {
        tuple<vector<Node *>, double> path, path_temp;
        vector<tuple<vector<Node *>, double> > open;
        vector<tuple<vector<Node *>, double> > close;
        vector<Node *> nodes_temp, out;
        tuple<Node *, bool, double> adj_temp;
        Node *suc;
        bool ready;

        get<0>(path).push_back(begin);
        get<1>(path) = 0.0;
        open.push_back(path);

        while (!open.empty()) {
                path = open.front();
                open.erase(open.begin());
                close.push_back(path);
                for (unsigned int i = 0; i < (get<0>(path).back())->adj.size(); i++) {
                        suc = get<0>(get<0>(path).back()->adj[i]);
                        ready = false;
                        for (unsigned int j = 0; j < close.size(); j++) {
                                if (suc == get<0>(close[j]).back()) {
                                        ready = true;
                                        break;
                                }
                        }
                        if (!ready) {
                                nodes_temp = get<0>(path);
                                nodes_temp.push_back(suc);
                                get<0>(path_temp) = nodes_temp;
                                adj_temp = (get<0>(path).back())->adj[i];
                                get<1>(path_temp) += distanceNode(get<0>(path).back(), get<0>(adj_temp));
                                open.push_back(path_temp);
                        }
                }

                for (unsigned int i = 0; i < open.size(); i++) {
                        for (unsigned int j = 0; j < open.size(); j++) {
                                if (open[i] != open[j]) {
                                        if (get<0>(open[i]).back() == get<0>(open[j]).back()) {
                                                if (get<1>(open[i]) < get<1>(open[j])) open.erase(open.begin() + j);
                                                else open.erase(open.begin() + i);
                                        }
                                }
                        }
                }
        }

        for (unsigned int i = 0; i < close.size(); i++) {
                if (get<0>(close[i]).front() == begin && get<0>(close[i]).back() == end) {
                        out = get<0>(close[i]);
                        break;
                }
        }

        return out;
}

double distanceNode(Node *n1, Node *n2) {
        return ((n2->pos - n1->pos).length());
}
