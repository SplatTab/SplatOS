#include "mouse.h"
#include "sys/idt.h"
#include "libstl/stdio.h"
#include "graphics.h"

uint8_t cursorgraphic[] = {
    0x00, 0x40, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00,
    0x00, 0x3f, 0xe0, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x1d, 0xfe, 0x00, 0x00, 0x1e, 0xf8, 0x00,
    0x00, 0x0e, 0x40, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00
};
point imageres = { 32, 16};

struct ps2md_mod_t ps2md_mod;
uint8_t cycle;
uint8_t packet[4];
bool packetReady;
bool mouseLoaded;
uint32_t mousebuffer[32 * 16];
uint32_t mousebufferswap[32 * 16];

bool ps2md_wait_in()
{
    uint64_t timeout = 100000;
    while (timeout--)
    {
        if (inb(0x64) & 0b1) return false;
    }
    return true;
}

bool ps2md_wait_out()
{
    uint64_t timeout = 100000;
    while (timeout--)
    {
        if ((inb(0x64) & 0b10) == 0) return false;
    }
    return true;
}

uint8_t ps2md_write(uint8_t write)
{
    ps2md_wait_out();
    outb(0x64, 0xD4);
    ps2md_wait_out();
    outb(0x60, write);
    ps2md_wait_in();
    return inb(0x60);
}

void ps2md_handler(struct registers_t *regs)
{
    ps2md_process();
    static bool skip = false;
    if (skip)
    {
        skip = false;
        return;
    }

    uint8_t data = inb(0x60);

    switch (cycle)
    {
        case 0:
            if (packetReady) break;
            if (data && (0b00001000 == 0)) break;
            packet[0] = data;
            cycle++;
            break;

        case 1:
            if (packetReady) break;
            packet[1] = data;
            cycle++;
            break;

        case 2:
            if (packetReady) break;
            packet[2] = data;
            packetReady = true;
            cycle = 0;
            break;
    }
}

void ps2md_process()
{
    if (!packetReady) return;
    packetReady = false;

    if (packet[0] & XPOSITION) ps2md_mod.xNegative = true;
    else ps2md_mod.xNegative = false;

    if (packet[0] & YPOSITION) ps2md_mod.yNegative = true;
    else ps2md_mod.yNegative = false;

    if (packet[0] & XOVERFLOW) ps2md_mod.xOverflow = true;
    else ps2md_mod.xOverflow = false;

    if (packet[0] & YOVERFLOW) ps2md_mod.yOverflow = true;
    else ps2md_mod.yOverflow = false;

    if (packet[0] & LEFTCLICK)
    {
        clearbitmap(cursorgraphic, ps2md_mod.lastposition, imageres, mousebuffer, mousebufferswap);
        ps2md_mod.LeftClick = true;
    }
    else
    {
        ps2md_mod.LeftClick = false;
    }

    if (packet[0] & MIDDLECLICK) ps2md_mod.MiddleClick = true;
    else ps2md_mod.MiddleClick = false;

    if (packet[0] & RIGHTCLICK) ps2md_mod.RightClick = true;
    else ps2md_mod.RightClick = false;

    if (!ps2md_mod.xNegative)
    {
        ps2md_mod.position.x += packet[1];
        if (ps2md_mod.xOverflow) ps2md_mod.position.x += 255;
    }
    else
    {
        packet[1] = 256 - packet[1];
        ps2md_mod.position.x -= packet[1];
        if (ps2md_mod.xOverflow) ps2md_mod.position.x -= 255;
    }

    if (!ps2md_mod.yNegative)
    {
        ps2md_mod.position.y -= packet[2];
        if (ps2md_mod.yOverflow) ps2md_mod.position.y -= 255;
    }
    else
    {
        packet[2] = 256 - packet[2];
        ps2md_mod.position.y += packet[2];
        if (ps2md_mod.yOverflow) ps2md_mod.position.y += 255;
    }

    point resolution = getresolution();

    if (ps2md_mod.position.x < 0) ps2md_mod.position.x = 0;
    if (ps2md_mod.position.x > resolution.x) ps2md_mod.position.x = resolution.x;

    if (ps2md_mod.position.y < 0) ps2md_mod.position.y = 0;
    if (ps2md_mod.position.y > resolution.y) ps2md_mod.position.y = resolution.y;

    if (mouseLoaded) clearbitmap(cursorgraphic, ps2md_mod.lastposition, imageres, mousebuffer, mousebufferswap);
    drawbitmap(cursorgraphic, ps2md_mod.position, imageres, 0x3498ebFF, mousebuffer, mousebufferswap);
    ps2md_mod.lastposition = ps2md_mod.position;
    if (!mouseLoaded) mouseLoaded = true;
}

void ps2md_init()
{
    register_interrupt_handler(44, ps2md_handler);

    outb(0x64, 0xA8);
    ps2md_wait_out();
    outb(0x64, 0x20);
    ps2md_wait_in();

    uint8_t status = inb(0x60);
    status |= 0b10;

    ps2md_wait_out();
    outb(0x64, 0x60);
    ps2md_wait_out();
    outb(0x60, status);

    ps2md_write(0xF6);
    ps2md_write(0xF4);
}