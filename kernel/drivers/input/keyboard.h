#pragma once
#include <stdbool.h>

#define CAPSLOCK 0x3A
#define NUMLOCK 0x45
#define SCROLLLOCK 0x46
#define L_SHIFT_DOWN 0x2A
#define R_SHIFT_DOWN 0x36
#define L_SHIFT_UP 0xAA
#define R_SHIFT_UP 0xB6
#define CTRL_DOWN 0x1D
#define CTRL_UP 0x9D
#define ALT_DOWN 0x38
#define ALT_UP 0xB8
#define ARROW_UP 0x48
#define ARROW_DOWN 0x50
#define ARROW_LEFT 0x4B
#define ARROW_RIGHT 0x4D

struct kbd_mod_t
{
    bool shift : 1;
    bool ctrl : 1;
    bool alt : 1;
    bool numlock : 1;
    bool capslock : 1;
    bool scrolllock : 1;
};

extern struct kbd_mod_t kbd_mod;

void kbd_init();
char getchar();