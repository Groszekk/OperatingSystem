#include "mem.h"

void memory_copy(unsigned char *source, unsigned char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(unsigned char *dest, unsigned char val, unsigned int len) {
    unsigned char *temp = (unsigned char *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}
