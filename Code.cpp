#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct {
    int numVertices;
    int numEdges;
    int** adjMatrix;
} Graph;

Graph createGraph(int numVertices) {
    Graph graph;
    graph.numVertices = numVertices;
    graph.numEdges = 0;
    graph.adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        graph.adjMatrix[i] = (int*)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            graph.adjMatrix[i][j] = -1;
        }
    }
    return graph;
}

void addEdge(Graph* graph, int u, int v, int weight) {
    graph->adjMatrix[u][v] = weight;
    graph->adjMatrix[v][u] = weight;
    graph->numEdges++;
}

int minDistance(int dist[], int visited[], int numVertices) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < numVertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to find the shortest route and distance using Dijkstra’s algorithm
void chinesePostman(Graph* graph) {
    int numVertices = graph->numVertices;
    int numEdges = graph->numEdges;

    // Array to store the distance of vertices from the source
    int dist[numVertices];

    // Array to track whether a vertex is visited or not
    int visited[numVertices];

    // Initialize the distance and visited arrays
    for (int v = 0; v < numVertices; v++) {
        dist[v] = INT_MAX;
        visited[v] = 0;
    }

    // Start with the first vertex
    int src = 0;
    dist[src] = 0;

    // Calculate the shortest path for all vertices
    for (int count = 0; count < numVertices - 1; count++) {
        int u = minDistance(dist, visited, numVertices);
        visited[u] = 1;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && graph->adjMatrix[u][v] != -1 && dist[u] != INT_MAX && dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
            }
        }
    }

    // Calculate the sum of all edge weights
    int sumOfEdges = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (graph->adjMatrix[i][j] != -1) {
                sumOfEdges += graph->adjMatrix[i][j];
            }
        }
    }

    // Calculate the total distance of the shortest route
    int totalDistance = sumOfEdges + dist[src];

    printf("Shortest route distance: %d\n", totalDistance);
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    Graph graph = createGraph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        printf("Enter edge (u, v, weight): ");
        scanf("%d%d%d", &u, &v, &weight);
        addEdge(&graph, u, v, weight);
    }

    chinesePostman(&graph);
    return 0;
}