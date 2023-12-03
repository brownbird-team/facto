#ifndef _INCLUDE_HELPERS_H_
#define _INCLUDE_HELPERS_H_

#include <ctype.h>
#include <string.h>
#include <constants.h>
#include <sys/time.h>

// Check if char array contains only digits
int digits_only(char *str) {

    while (*str != '\0') {
        if (!isdigit(*(str++)))
            return 0;
    }

    return 1;
}

// Returns pointer to string representation of facto mode
char * facto_mode_name(int mode_code) {

    static char normal[] = "NORMAL";
    static char precise[] = "PRECISE";
    static char stirling[] = "STIRLING";

    static char unknown[] = "UNKNOWN";

    switch (mode_code) {
        case FACTO_MODE_NORMAL:
            return normal;
        case FACTO_MODE_PRECISE:
            return precise;
        case FACTO_MODE_STIRLING:
            return stirling;
    }

    return unknown;
}

// Check if number stored in first char array is smaller than
int number_smaller_or_equal(char *number, char *max_value) {

    int i, nlen = strlen(number), mlen = strlen(max_value);

    if (nlen > mlen)
        return 0;

    if (nlen == mlen) {
        for (i = 0; i < nlen; i++) {
            if (number[i] < max_value[i])
                return 1;
            if (number[i] > max_value[i]) {
                return 0;
            }
        }
    }

    return 1;
}

// Calculate time passed between two timevals
int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y) {
    if (x->tv_usec < y->tv_usec) {
        x->tv_sec -= 1;
        x->tv_usec += 1000000;
    }

    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;

    if (result->tv_usec > 1000000) {
        result->tv_sec += 1;
        result->tv_usec -= 1000000;
    }

    return x->tv_sec < y->tv_sec;
}

#endif