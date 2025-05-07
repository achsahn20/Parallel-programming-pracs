#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000
#define MAX_VAL 100

int main() {
    int data[N], histogram[MAX_VAL] = {0};

    // Generate random data
    for (int i = 0; i < N; i++)
        data[i] = rand() % MAX_VAL;

    // Parallel histogram calculation
    #pragma omp parallel
    {
        int local_histogram[MAX_VAL] = {0};

        #pragma omp for
        for (int i = 0; i < N; i++)
            local_histogram[data[i]]++;

        #pragma omp critical
        for (int i = 0; i < MAX_VAL; i++)
            histogram[i] += local_histogram[i];
    }

    // Print histogram
    for (int i = 0; i < MAX_VAL; i++)
        printf("%d: %d\n", i, histogram[i]);

    return 0;
}

/*
Compile using:
   gcc -fopenmp hist_sort.c -o hist_sort

Run the program:
   ./hist_sort
*/
