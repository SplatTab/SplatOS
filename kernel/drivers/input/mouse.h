#pragma once
#include <stdbool.h>
#include "libstl/math.h"

#define LEFTCLICK 0b00000001
#define MIDDLECLICK 0b00000010
#define RIGHTCLICK 0b00000100
#define XPOSITION 0b00010000
#define YPOSITION 0b00100000
#define XOVERFLOW 0b01000000
#define YOVERFLOW 0b10000000

struct ps2md_mod_t
{
    bool xNegative;
    bool yNegative;
    bool xOverflow;
    bool yOverflow;
    bool LeftClick;
    bool MiddleClick;
    bool RightClick;
    point position;
    point lastposition;
    uint32_t *buffer;
};

extern struct ps2md_mod_t ps2md_mod;
extern bool packetReady;

void ps2md_process();
void ps2md_init();