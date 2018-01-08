#include <posix_stdlib.h>

int getloadavg(double loadavg[], int nelem) {
    for(int i = 0; i < nelem; ++i)
        loadavg[i] = 0.;
    return nelem;
}
