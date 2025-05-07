#include <stdio.h>
#include <limits.h>
#include <omp.h>

#define V 6
#define INF 9999

int minDistance(int dist[], int visited[]) {
    int min = INF, min_index;

    #pragma omp parallel for
    for (int v = 0; v < V; v++) {
        #pragma omp critical
        {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
    }

    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int visited[V] = {0};

    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        #pragma omp parallel for
        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    for (int i = 0; i < V; i++)
        printf("Distance from %d to %d is %d\n", src, i, dist[i]);
}

int main() {
    int graph[V][V] = {
        {0, 3, INF, INF, INF, 1},
        {3, 0, 1, INF, INF, 4},
        {INF, 1, 0, 6, INF, 4},
        {INF, INF, 6, 0, 2, INF},
        {INF, INF, INF, 2, 0, 1},
        {1, 4, 4, INF, 1, 0}
    };

    dijkstra(graph, 0);
    return 0;
}

/*
Compile using:
   gcc -fopenmp dijkstra.c -o dijkstra

Run the program:
   ./dijkstra
*/
