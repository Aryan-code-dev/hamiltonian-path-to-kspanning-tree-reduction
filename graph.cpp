#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Graph {
private:
    // Adjacency list representation
    unordered_map<int, vector<int>> adjacencyList;
    int originalVertexCount;

public:
    // Constructor
    Graph(){
        originalVertexCount=0;
    }

    // Add an edge to the graph
    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    // Transform 2-spanning tree graph to k-spanning tree graph
    Graph transformToKSpanningTree(int k) {
        if (k < 2) {
            throw invalid_argument("k must be at least 2");
        }

        Graph transformedGraph = *this;
        originalVertexCount = adjacencyList.size();

        // Add k-2 additional vertices for each original vertex
        for (const auto& vertex : adjacencyList) {
            int originalVertex = vertex.first;
            
            // Add k-2 new vertices for this original vertex
            for (int i = 0; i < k - 2; ++i) {
                int newVertex = originalVertexCount + (originalVertex * (k - 2)) + i;
                
                // Connect new vertex to original vertex
                transformedGraph.addEdge(originalVertex, newVertex);
            }
        }

        return transformedGraph;
    }

    // Print graph details
    void printGraph() {
        cout << "Graph Vertices and Edges:\n";
        for (const auto& vertex : adjacencyList) {
            cout << "Vertex " << vertex.first << " connected to: ";
            for (int neighbor : vertex.second) {
                cout << neighbor << " ";
            }
            cout << "\n";
        }
    }

    // Get the number of vertices
    int getVertexCount() const {
        return adjacencyList.size();
    }
};

int main() {
    Graph originalGraph;
    int numVertices, numEdges, k;

    // User input for original graph
    cout << "Enter number of vertices in the original graph: ";
    cin >> numVertices;

    cout << "Enter number of edges in the original graph: ";
    cin >> numEdges;

    cout << "Enter edges (u v format):\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v;
        originalGraph.addEdge(u, v);
    }

    cout << "Enter k for k-spanning tree (k >= 2): ";
    cin >> k;

    cout << "\nOriginal Graph:\n";
    originalGraph.printGraph();

    // Transform the graph
    Graph transformedGraph = originalGraph.transformToKSpanningTree(k);

    cout << "\nTransformed Graph (k = " << k << "):\n";
    transformedGraph.printGraph();

    cout << "\nVertex count in transformed graph: " 
              << transformedGraph.getVertexCount() << std::endl;

    return 0;
}