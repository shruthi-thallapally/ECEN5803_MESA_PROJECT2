/*   references:https://github.com/sifive/benchmark-dhrystone                 */
#define _GNU_SOURCE

#include <stdio.h>
#include <time.h>
#include <sched.h>
#include <pthread.h>
#include "dhry.h"

int main() {
    clock_t start_time, end_time;
    double benchtime, dps, DMIPS;
    unsigned long loops;

    printf("Dhrystone Benchmark Program C/1 12/01/84\n");
    
    // Set the initial CPU core to 0 and change the values from 0-3 to see dhrystoen value for each core
    int core = 0;
    // Create a CPU set and set the affinity to the specified core
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    printf("Running on Core: %d\n", sched_getcpu());

    // Start the benchmark loop
    loops = 0;
    start_time = clock();

    do {
        Proc0();  // Execute the benchmark function
        loops += LOOPS;
        end_time = clock();
        benchtime = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        // printf("Benchtime: %lf\n", benchtime); // Optional: Print the elapsed time
    } while (benchtime <= 20.000);  // Continue until the elapsed time exceeds 20 seconds

    // Calculate and display the benchmark results
    dps = (double)loops / benchtime;
    printf("Dhrystone time for %lu passes = %lf seconds\n", loops, benchtime);
    printf("This machine benchmarks at %lf dhrystones/second\n", dps);

    DMIPS = dps / 1757.0;  // Calculate DMIPS based on standard reference
    printf("This machine has %lf DMIPS\n", DMIPS);
    printf("This machine has %lf DMIPS/MHz\n", DMIPS / 18.5);  // Adjust for clock speed

    return 0;
}
