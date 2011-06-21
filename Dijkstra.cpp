#include "Dijkstra.hpp"

vector<Node *> dijkstra(Node *begin, Node *end) {
        tuple< vector<Node*>, double> path, path_temp;
        vector< tuple < vector<Node*>, double> > open;
        vector< tuple < vector<Node*>, double> > close;

        vector<Node*> nodes_temp, out;
        tuple<Node*, bool, double> adj_temp;
        double min_value, cost = 0.0;

        begin->check = true;
        get<0>(path).push_back(begin);
        get<1>(path) = 0.0;
        open.push_back(path);

        int k = 0;
        while (!open.empty()) {
                cout << "Open size : " << open.size() << endl;
                k++;
                path = open.front();
                open.erase(open.begin());
                for (unsigned int i = 0; i < (get<0>(path).back())->adj.size(); i++) {
                        nodes_temp = get<0>(path);
                        nodes_temp.push_back(get<0>(get<0>(path).back()->adj[i]));
                        get<0>(path_temp) = nodes_temp;
                        adj_temp = (get<0>(path).back())->adj[i];
                        get<1>(path_temp) = get<1>(path) + distanceNode(get<0>(path).back(), get<0>(adj_temp));
                        open.push_back(path_temp);
                }
                close.push_back(path);

                for (unsigned int i = 0; i < open.size(); i++) {
                        for (unsigned int j = 0; j < open.size(); j++) {
                                if (open[i] != open[j]) {
                                        if (get<0>(open[i]).back() == get<0>(open[j]).back()) {
                                                if (get<1>(open[i]) < get<1>(open[j]))
                                                        open.erase(open.begin()+j);
                                                else
                                                        open.erase(open.begin()+i);
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
        }

        return out;
}

double distanceNode(Node *n1, Node *n2) {
        return ((n2->pos - n1->pos).length());
}
