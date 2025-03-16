#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    // Initialize distances to INF, and -1 for previous
    vector<int> dist(n, INF);
    dist[source] = 0;
    previous.assign(n, -1);

    // Track visited vertices to avoid re-processing
    vector<bool> visited(n, false);

    // Min-heap (priority queue) storing pairs <distance, vertex>
    using Node = pair<int, int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Start from source with distance 0
    pq.push({0, source});

    while (!pq.empty()) {
        auto [currDist, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        // Explore neighbors of u
        for (auto &edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;
            // Relaxation step
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                previous[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous,
                                  int destination) {
    vector<int> path;
    // Out-of-bounds or unreachable check
    if (destination < 0 || destination >= (int)distances.size() ||
        distances[destination] == INF) {
        return path;  // empty => no path
    }

    // Follow the 'previous' chain backwards from destination to source
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    // Reverse to get path from source to destination
    reverse(path.begin(), path.end());
    return path;
}


void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path" << endl;
        return;
    }
    // Print the path vertices
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " ";
    }
    cout << endl;
    // Print the total cost
    cout << "Total cost is " << total << endl;
}
