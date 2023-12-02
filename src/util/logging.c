#include "util.h"

// print program resource usage
void log_rusage(struct rusage *rusage) {
    printf("\t(\n");
    // utime is time in user mode (normal program execution)
    printf("\t\tru_utime=%lf,\n", (double)rusage->ru_utime.tv_sec + ((double)rusage->ru_utime.tv_usec / 1000000.0));
    // stime is time in kernel mode (mostly time spent in syscalls)
    printf("\t\tru_stime=%lf,\n", (double)rusage->ru_stime.tv_sec + ((double)rusage->ru_stime.tv_usec / 1000000.0));
    // maxrss is maximum working set size - largest number of bytes
    // in use by the program at a single time
    printf("\t\tru_maxrss=%ld,\n", rusage->ru_maxrss);
    // minflt is soft pagefaults where the program is able to
    // reclaim a previously used page
    printf("\t\tru_minflt=%ld,\n", rusage->ru_minflt);
    // majflt is hard pagefaults where the program is not able to
    // reclaim a previously used page
    printf("\t\tru_majflt=%ld,\n", rusage->ru_majflt);
    // inblock is block inputs to the filesystem
    printf("\t\tru_inblock=%ld,\n", rusage->ru_inblock);
    // oublock is block outputs from the filesystem
    printf("\t\tru_oublock=%ld,\n", rusage->ru_oublock);
    // nvcsw is number of voluntary context switches,
    // such as blocking for file I/O
    printf("\t\tru_nvcsw=%ld,\n", rusage->ru_nvcsw);
    // nivcsw is number of involuntary context switches,
    // when the program exceeds its time slice or is evicted by
    // a higher priority process
    printf("\t\tru_nivcsw=%ld,\n", rusage->ru_nivcsw);
    printf("\t)\n");
}

void log_perf(struct timespec *start, struct timespec *end, struct rusage *rusage) {
    printf("\nProgram performance:\n");
    printf("---------------------\n");
    double time = (double)(end->tv_sec - start->tv_sec) + ((double)(end->tv_nsec - start->tv_nsec) / 1000000000.0);
    printf("\tTotal Time: %lf seconds\n", time);
    printf("\tResource usage breakdown: \n");
    log_rusage(rusage);
}
