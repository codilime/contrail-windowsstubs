#include <sys/resource.h>

int getrusage(int, struct rusage *) {
    return 0; 
}

int getrlimit(int, struct rlimit *) {
    return 0; 
}

int setrlimit(int, struct rlimit const *) {
    return 0; 
}
