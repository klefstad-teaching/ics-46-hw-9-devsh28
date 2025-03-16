#include "dijkstras.h"
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> dist(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    dist[source] = 0;
    using Node = pair<int, int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, source});
    while (!pq.empty()) {
        auto [currDist, u] = pq.top();
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (auto &edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                previous[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (destination < 0 || destination >= (int)distances.size() || distances[destination] == INF)
        return path;
    for (int v = destination; v != -1; v = previous[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "\nTotal cost is " << total << "\n";
        return;
    }
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}
