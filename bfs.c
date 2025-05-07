#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 100
int graph[MAX][MAX], visited[MAX], queue[MAX];
int front = -1, rear = -1, n;

void enqueue(int v) {
    if (rear == MAX - 1) return;
    queue[++rear] = v;
}

int dequeue() {
    if (front == rear) return -1;
    return queue[++front];
}

int isQueueEmpty() {
    return front == rear;
}

void bfs(int start) {
    visited[start] = 1;
    enqueue(start);

    while (!isQueueEmpty()) {
        int v = dequeue();
        printf("%d ", v);

        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            if (graph[v][i] && !visited[i]) {
                #pragma omp critical
                {
                    if (!visited[i]) {
                        visited[i] = 1;
                        enqueue(i);
                    }
                }
            }
        }
    }
}

int main() {
    int i, j, start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    bfs(start);
    printf("\n");

    return 0;
}

/*
Compile using:
   gcc -fopenmp bfs.c -o bfs

Run the program:
   ./bfs
*/

/*
Example Input:
Enter number of vertices: 4
Enter adjacency matrix:
1 0 1 1
1 0 0 0
0 1 1 0
0 1 0 1
Enter starting vertex: 0
*/
