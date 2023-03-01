#include "./common.h"

void    err_n_die(const char *fmt) {
    write(2, fmt, strlen(fmt));
    exit(1);
}
