#include "keyboard.h"
#include "sys/idt.h"
#include "libstl/stdio.h"

struct kbd_mod_t kbd_mod;

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b',   /* Backspace */
    '\t',           /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',   /* Enter key */
    0,          /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',   /* 39 */
    '\'', '`',   0,     /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',         /* 49 */
    'm', ',', '.', '/',   0,                /* Right shift */
    '*',
    0,  /* Alt */
    ' ',    /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
    '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
    '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
0,  /* All other keys are undefined */
};

unsigned char kbdus_shft[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
    '(', ')', '_', '+', '\b',   /* Backspace */
    '\t',           /* Tab */
    'Q', 'W', 'E', 'R', /* 19 */
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',   /* Enter key */
    0,          /* 29   - Control */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',   /* 39 */
    '\"', '~',   0,     /* Left shift */
    '|', 'Z', 'X', 'C', 'V', 'B', 'N',          /* 49 */
    'M', '<', '>', '?',   0,                /* Right shift */
    '*',
    0,  /* Alt */
    ' ',    /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
    '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
    '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};
unsigned char kbdus_caps[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b',   /* Backspace */
    '\t',           /* Tab */
    'Q', 'W', 'E', 'R', /* 19 */
    'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n',   /* Enter key */
    0,          /* 29   - Control */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',   /* 39 */
    '\'', '`',   0,     /* Left shift */
    '\\', 'Z', 'X', 'C', 'V', 'B', 'N',         /* 49 */
    'M', ',', '.', '/',   0,                /* Right shift */
    '*',
    0,  /* Alt */
    ' ',    /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
    '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
    '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

unsigned char kbdus_capsshft[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',     /* 9 */
    '(', ')', '_', '+', '\b',     /* Backspace */
    '\t',                 /* Tab */
    'q', 'w', 'e', 'r',   /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n', /* Enter key */
    0,                  /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ':',     /* 39 */
    '\"', '~',   0,                /* Left shift */
    '|', 'z', 'x', 'c', 'v', 'b', 'n',                     /* 49 */
    'm', '<', '>', '?',   0,                              /* Right shift */
    '*',
    0,  /* Alt */
    ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
    '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
    '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

char get_ascii_char(uint8_t key_code)
{
    if (!kbd_mod.shift && !kbd_mod.capslock)
    {
        return kbdus[key_code];
    }
    if (kbd_mod.shift && !kbd_mod.capslock)
    {
        return kbdus_shft[key_code];
    }
    if (!kbd_mod.shift && kbd_mod.capslock)
    {
        return kbdus_caps[key_code];
    }
    if (kbd_mod.shift && kbd_mod.capslock)
    {
        return kbdus_capsshft[key_code];
    }
    return 0;
}

volatile bool pressed = false;
char c[2] = { 0 };

char getchar()
{
    while (!pressed);
    pressed = false;
    print(c);
    return c[0];
}

bool wait_in()
{
    uint64_t timeout = 100000U;
    while (--timeout) if (!(inb(0x64) & (1 << 1))) return false;
    return true;
}

bool wait_out()
{
    uint64_t timeout = 100000;
    while (--timeout) if (inb(0x64) & (1 << 0)) return false;
    return true;
}

uint8_t kbd_write(uint8_t write)
{
    wait_in();
    outb(0x60, write);
    wait_out();
    return inb(0x60);
}

void update_leds()
{
    uint8_t value = 0b000;
    if (kbd_mod.scrolllock) value |= (1 << 0);
    if (kbd_mod.numlock) value |= (1 << 1);
    if (kbd_mod.capslock) value |= (1 << 2);
    kbd_write(0xED);
    kbd_write(value);
}

void kbd_handler(struct registers_t *regs)
{
    uint8_t scancode = inb(0x60);
    if (scancode & 0x80)
    {
        switch (scancode)
        {
            case L_SHIFT_UP:
            case R_SHIFT_UP:
                kbd_mod.shift = false;
                break;
            case CTRL_UP:
                kbd_mod.ctrl = false;
                break;
            case ALT_UP:
                kbd_mod.alt = false;
                break;
        }
    }
    else
    {
        switch (scancode)
        {
            case L_SHIFT_DOWN:
            case R_SHIFT_DOWN:
                kbd_mod.shift = true;
                break;
            case CTRL_DOWN:
                kbd_mod.ctrl = true;
                break;
            case ALT_DOWN:
                kbd_mod.alt = true;
                break;
            case CAPSLOCK:
                kbd_mod.capslock = (!kbd_mod.capslock) ? true : false;
                update_leds();
                break;
            case NUMLOCK:
                kbd_mod.numlock = (!kbd_mod.numlock) ? true : false;
                update_leds();
                break;
            case SCROLLLOCK:
                kbd_mod.scrolllock = (!kbd_mod.scrolllock) ? true : false;
                update_leds();
                break;
            case UP:
                print("\033[A");
                break;
            case DOWN:
                print("\033[B");
                break;
            case RIGHT:
                print("\033[C");
                break;
            case LEFT:
                print("\033[D");
                break;
            default:
                c[0] = get_ascii_char(scancode);
                if (kbd_mod.ctrl && (c[0] == 'l' || c[0] == 'L'))
                {
                    print("\033[H\033[2J");
                    break;
                }
                pressed = true;
                // print(c);
                break;
        }
    }
}

void ps2_init()
{
    register_interrupt_handler(33, kbd_handler);
}