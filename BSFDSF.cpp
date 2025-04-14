#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_VERTICES 100

// Graph represented using adjacency list
struct Graph {
    vector<int> adjList[MAX_VERTICES];
    int vertices;
};

// Function to initialize the graph
void initGraph(Graph &g, int V) {
    g.vertices = V;
    for (int i = 0; i < V; i++) {
        g.adjList[i].clear();
    }
}

// Function to add an edge to the graph
void addEdge(Graph &g, int u, int v) {
    g.adjList[u].push_back(v);
    g.adjList[v].push_back(u); // Comment this line for a directed graph
}

// BFS function (Iterative)
void BFS(Graph &g, int start) {
    vector<bool> visited(g.vertices, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal starting from node " << start << ": ";

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : g.adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

// DFS function (Recursive)
void DFSUtil(Graph &g, int node, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : g.adjList[node]) {
        if (!visited[neighbor]) {
            DFSUtil(g, neighbor, visited);
        }
    }
}

void DFS(Graph &g, int start) {
    vector<bool> visited(g.vertices, false);
    cout << "DFS Traversal starting from node " << start << ": ";
    DFSUtil(g, start, visited);
    cout << endl;
}

int main() {
    int V, E, u, v, start;

    // Input number of vertices and edges
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g;
    initGraph(g, V);

    cout << "Enter number of edges: ";
    cin >> E;

    // Input edges
    cout << "Enter edges (u v): \n";
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        addEdge(g, u, v);
    }

    // Input start node for BFS and DFS
    cout << "Enter start vertex for BFS and DFS: ";
    cin >> start;

    // Perform BFS and DFS
    BFS(g, start);
    DFS(g, start);

    return 0;
}
