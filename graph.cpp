#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;
    int vertexCount;

public:
    Graph(int n = 0) : vertexCount(n) {}

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }
    void addEdgeOnce(int u, int v) {
        adjacencyList[u].push_back(v);
        
    }

    // Find Hamiltonian Path using backtracking
    std::vector<int> findHamiltonianPath() {
        std::vector<int> path;
        std::unordered_set<int> visited;

        // Try starting from each vertex
        for (const auto& start : adjacencyList) {
            path.clear();
            visited.clear();
            if (hamiltonianPathUtil(start.first, path, visited)) {
                return path;
            }
        }

        return {}; // No Hamiltonian path found
    }

private:
    bool hamiltonianPathUtil(int v, std::vector<int>& path, std::unordered_set<int>& visited) {
        path.push_back(v);
        visited.insert(v);

        // If path includes all vertices, we found a Hamiltonian path
        if (path.size() == vertexCount) {
            return true;
        }

        // Try all adjacent vertices
        for (int neighbor : adjacencyList[v]) {
            if (visited.find(neighbor) == visited.end()) {
                if (hamiltonianPathUtil(neighbor, path, visited)) {
                    return true;
                }
            }
        }

        // Backtrack
        path.pop_back();
        visited.erase(v);
        return false;
    }

public:
    // Transform 2-spanning tree (Hamiltonian path) to k-spanning tree
    Graph transformToKSpanningTree(int k) {
        if (k < 2) {
            throw std::invalid_argument("k must be at least 2");
        }

        Graph transformedGraph = *this;
        int originalVertexCount = vertexCount;

        // Add k-2 additional vertices for each original vertex
        for (int v = 1; v <= originalVertexCount; ++v) {
            for (int i = 0; i < k - 2; ++i) {
                int newVertex = originalVertexCount + (v * (k - 2)) + i;
                transformedGraph.addEdge(v, newVertex);
            }
        }

        return transformedGraph;
    }

    // Convert k-spanning tree back to 2-spanning tree by removing degree 1 nodes
    Graph convertToTwoSpanningTree() {
        Graph twoSpanningTree;
        std::unordered_map<int, int> degreeMap;

        // Calculate degrees
        for (const auto& vertex : adjacencyList) {
            degreeMap[vertex.first] = vertex.second.size();
        }

        // Copy edges, excluding degree 1 vertices
        for (const auto& vertex : adjacencyList) {
            for (int neighbor : vertex.second) {
                if (degreeMap[vertex.first] > 1 && degreeMap[neighbor] > 1) {
                    twoSpanningTree.addEdgeOnce(vertex.first, neighbor);
                }
            }
        }

        return twoSpanningTree;
    }

    // Print graph details
    void printGraph() {
        std::cout << "Graph Vertices and Edges:\n";
        for (const auto& vertex : adjacencyList) {
            std::cout << "Vertex " << vertex.first << " connected to: ";
            for (int neighbor : vertex.second) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }

    void setVertexCount(int count) {
        vertexCount = count;
    }
};

int main() {
    Graph graph;
    int numVertices, numEdges, k;

    // User input for original graph
    std::cout << "Enter number of vertices: ";
    std::cin >> numVertices;
    graph.setVertexCount(numVertices);

    std::cout << "Enter number of edges: ";
    std::cin >> numEdges;

    std::cout << "Enter edges (u v format):\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }

    // Find Hamiltonian Path (2-spanning tree)
    std::vector<int> hamiltonianPath = graph.findHamiltonianPath();
    
    if (hamiltonianPath.empty()) {
        std::cout << "No Hamiltonian path exists in the graph.\n";
        return 1;
    }

    std::cout << "Hamiltonian Path: ";
    for (int vertex : hamiltonianPath) {
        std::cout << vertex << " ";
    }
    std::cout << "\n";
    std::cout << "Therefore there exists a 2-spanning tree in the graph\n ";

    // Get k value
    std::cout << "Enter k for k-spanning tree (k >= 2): ";
    std::cin >> k;

    // Transform to k-spanning tree
    Graph kSpanningTree = graph.transformToKSpanningTree(k);
    std::cout << "\nk-Spanning Tree:\n";
    kSpanningTree.printGraph();

    // Convert back to 2-spanning tree
    Graph twoSpanningTree = kSpanningTree.convertToTwoSpanningTree();
    std::cout << "\n2-Spanning Tree (after removing degree 1 nodes):\n";
    twoSpanningTree.printGraph();

    return 0;
}