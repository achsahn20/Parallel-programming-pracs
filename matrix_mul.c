#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500

int main() {
    int A[N][N], B[N][N], C[N][N];
    int i, j, k;

    // Initialize matrices A and B
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }

    double start = omp_get_wtime();

    #pragma omp parallel for private(j, k)
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];

    double end = omp_get_wtime();
    printf("Time taken: %f seconds\n", end - start);

    return 0;
}

/*
Compile using:
   gcc -fopenmp matrix_mul.c -o matrix_mul
   
Run the program:
   ./matrix_mul
*/
