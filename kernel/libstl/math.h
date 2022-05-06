#pragma once
#include <stdint.h>

typedef struct {
    int x;
    int y;
} point;

int abs(int x);
const char *formatTime(long int seconds);