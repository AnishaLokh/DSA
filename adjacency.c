#include <stdio.h>

#define MAX 100 // Maximum number of vertices

void createAdjMatrix(int adjMatrix[MAX][MAX], int vertices, int edges) {
    // Initialize adjacency matrix with zeros
    for (int i = 1; i <= vertices; i++) {
        for (int j = 1; j <= vertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    // Read edges and update the matrix
    int u, v;
    for (int i = 1; i <=edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);

        // Validate input
        if (u < 0 || v < 0 || u > vertices || v > vertices) {
            printf("Invalid edge! Please enter vertices between 0 and %d.\n", vertices);
            i--; // Decrement counter to re-enter the edge
            continue;
        }

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // Remove this line for a directed graph
    }
}

void printAdjMatrix(int adjMatrix[MAX][MAX], int vertices) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 1; i <= vertices; i++) {
        for (int j = 1; j <= vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int vertices, edges;
    int adjMatrix[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    createAdjMatrix(adjMatrix, vertices, edges);
    printAdjMatrix(adjMatrix, vertices);

    return 0;
}
