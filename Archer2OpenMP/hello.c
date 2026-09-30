#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) 
{
    int nthreads;
    char hostname[100];

    nthreads = omp_get_max_threads();
    printf("Number of threads = %d\n", nthreads);

    gethostname(hostname, 100);
#pragma omp parallel 
    {
        int tid = omp_get_thread_num();
        printf("SLIIT\n"); // run for each thread	  
        for (int r = 1; r < 2; r++) {
            printf("r = %d, thread = %d, host = %s\n", r, tid, hostname);     
        }
    }  

    return 0;
}
