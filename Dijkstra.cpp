#include <tuple>
#include <vector>

#include "Node.hpp"
#include "Dijkstra.hpp"

std::vector<Node *> dijkstra(Node *begin, Node *end) {
        std::tuple<std::vector<Node *>, double> path, path_temp;
        std::vector<std::tuple<std::vector<Node *>, double> > open;
        std::vector<std::tuple<std::vector<Node *>, double> > close;
        std::vector<Node *> nodes_temp, out;
        Node *suc;
        bool ready;

        std::get<0>(path).push_back(begin);
        std::get<1>(path) = 0.0;
        open.push_back(path);

        while (!open.empty()) {
                path = open.front();
                open.erase(open.begin());
                close.push_back(path);
                for (unsigned int i = 0; i < (std::get<0>(path).back())->adj.size(); i++) {
                        suc = std::get<0>(path).back()->adj[i];
                        ready = false;
                        for (unsigned int j = 0; j < close.size(); j++) {
                                if (suc == std::get<0>(close[j]).back()) {
                                        ready = true;
                                        break;
                                }
                        }
                        if (!ready) {
                                nodes_temp = std::get<0>(path);
                                nodes_temp.push_back(suc);
                                std::get<0>(path_temp) = nodes_temp;
                                std::get<1>(path_temp) += distanceNode(std::get<0>(path).back(), suc);
                                open.push_back(path_temp);
                        }
                }

                for (unsigned int i = 0; i < open.size(); i++) {
                        for (unsigned int j = 0; j < open.size(); j++) {
                                if (open[i] != open[j]) {
                                        if (std::get<0>(open[i]).back() == std::get<0>(open[j]).back()) {
                                                if (std::get<1>(open[i]) < std::get<1>(open[j])) open.erase(open.begin() + j);
                                                else open.erase(open.begin() + i);
                                        }
                                }
                        }
                }
        }

        for (unsigned int i = 0; i < close.size(); i++) {
                if (std::get<0>(close[i]).front() == begin && std::get<0>(close[i]).back() == end) {
                        out = std::get<0>(close[i]);
                        break;
                }
        }

        return out;
}

double distanceNode(Node *n1, Node *n2) {
        return ((n2->pos - n1->pos).length());
}
