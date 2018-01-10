#include <posix_string.h>

#include <cstdio>

constexpr size_t CURRENT_SIGNAL_NAME_SIZE = 128;

static char current_signal_name[CURRENT_SIGNAL_NAME_SIZE];

char *strsignal(int sig) {
    snprintf(current_signal_name, CURRENT_SIGNAL_NAME_SIZE, "Signal #%d", sig);
    return current_signal_name;
}
