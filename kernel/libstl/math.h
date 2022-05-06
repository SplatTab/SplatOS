#pragma once
#include <stdint.h>

typedef struct {
    int x;
    int y;
} point;

typedef struct time {
    int seconds;
    int minutes;
    int hour;
    int day;
    int wday;
    int month;
    int mday;
    int year;
    int yday;
} time;

#define LEAPOCH (946684800LL + 86400*(31+29))
#define DAYS_PER_400Y (365*400 + 97)
#define DAYS_PER_100Y (365*100 + 24)
#define DAYS_PER_4Y   (365*4   + 1)

int abs(int x);
void itoa(int64_t num, char *str);
time formatTime(int64_t unix);