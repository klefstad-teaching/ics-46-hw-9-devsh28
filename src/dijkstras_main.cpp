#include "dijkstras.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

int main() {
    // List of graph files to process
    vector<string> filenames = {"small.txt", "medium.txt", "large.txt", "largest.txt"};
    
    // Iterate through each file
    for (const auto& filename : filenames) {
        cout << "Processing file: " << filename << "\n";
        
        Graph G;
        try {
            file_to_graph(filename, G);
        } catch (const runtime_error& err) {
            cerr << "Error processing file " << filename << ": " << err.what() << "\n";
            continue;  // Move on to the next file
        }
        
        // Run Dijkstra's algorithm from vertex 0
        vector<int> previous;
        vector<int> distances = dijkstra_shortest_path(G, 0, previous);
        
        // Print shortest paths from vertex 0 to every other vertex
        for (int v = 0; v < G.numVertices; v++) {
            vector<int> path = extract_shortest_path(distances, previous, v);
            cout << "Path to vertex " << v << ": ";
            print_path(path, (distances[v] == INF ? -1 : distances[v]));
            cout << "\n";
        }

    }
    
    return 0;
}
