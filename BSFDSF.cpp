#include <iostream>
#include <queue>
using namespace std;

#define MAX_VERTICES 100
#define MAX_EDGES 100  // Max edges per node

// Graph represented using adjacency list (array style)
struct Graph {
    int adjList[MAX_VERTICES][MAX_EDGES]; // Adjacency list
    int adjSize[MAX_VERTICES];            // Tracks number of neighbors
    int vertices;
};

// Initialize graph
void initGraph(Graph &g, int V) {
    g.vertices = V;
    for (int i = 0; i < V; i++) {
        g.adjSize[i] = 0;
    }
}

// Add an edge
void addEdge(Graph &g, int u, int v) {
    g.adjList[u][g.adjSize[u]++] = v;
    g.adjList[v][g.adjSize[v]++] = u; // For undirected graph
}

// BFS using queue (iterative)
void BFS(Graph &g, int start) {
    bool visited[MAX_VERTICES] = {false};
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal starting from node " << start << ": ";

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int i = 0; i < g.adjSize[node]; i++) {
            int neighbor = g.adjList[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

// DFS recursive utility
void DFSUtil(Graph &g, int node, bool visited[]) {
    visited[node] = true;
    cout << node << " ";

    for (int i = 0; i < g.adjSize[node]; i++) {
        int neighbor = g.adjList[node][i];
        if (!visited[neighbor]) {
            DFSUtil(g, neighbor, visited);
        }
    }
}

// DFS wrapper
void DFS(Graph &g, int start) {
    bool visited[MAX_VERTICES] = {false};
    cout << "DFS Traversal starting from node " << start << ": ";
    DFSUtil(g, start, visited);
    cout << endl;
}

int main() {
    int V, E, u, v, start;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g;
    initGraph(g, V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v): \n";
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        addEdge(g, u, v);
    }

    cout << "Enter start vertex for BFS and DFS: ";
    cin >> start;

    BFS(g, start);
    DFS(g, start);

    return 0;
}
