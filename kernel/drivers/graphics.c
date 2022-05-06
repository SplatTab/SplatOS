#include <limine.h>
#include "graphics.h"
#include "libstl/stdio.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

struct limine_framebuffer *fb;

void graphics_init()
{
    fb = framebuffer_request.response->framebuffers[0];
}

void putpixel(int x, int y, uint32_t color)
{
    *(uint32_t*)((uint64_t)fb->address + (x*4) + (y * fb->width * 4)) = color;
}

uint32_t getpixel(int x, int y)
{
    return *(uint32_t*)((uint64_t)fb->address + (x*4) + (y * fb->width * 4));
}

// This is slow but it's better than writing every pixel manually
void drawbitmap(uint8_t *bitmap, point position, point imageres, uint32_t color, uint32_t *buffer, uint32_t *bufferswap)
{
    int xMax = imageres.x, yMax = imageres.y;
    int differenceX = fb->width - position.x;
    int differenceY = fb->height - position.y;

    if (differenceX < imageres.x) xMax = differenceX;
    if (differenceY < imageres.y) yMax = differenceY;

    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            int bit = y * imageres.x + x;
            int byte = bit / 8;
            if ((bitmap[byte] & (0b10000000 >> (x % 8))))
            {
                buffer[x + y * imageres.x] = getpixel(position.x + x, position.y + y);
                putpixel(position.x + x, position.y + y, color);
                bufferswap[x + y * imageres.x] = getpixel(position.x + x, position.y + y);
            }
        }
    }
}

void clearbitmap(uint8_t *bitmap, point position, point imageres, uint32_t *buffer, uint32_t *bufferswap)
{
    int xMax = imageres.x, yMax = imageres.y;
    int differenceX = fb->width - position.x;
    int differenceY = fb->height - position.y;

    if (differenceX < imageres.x) xMax = differenceX;
    if (differenceY < imageres.y) yMax = differenceY;

    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            int bit = y * imageres.x + x;
            int byte = bit / 8;
            if ((bitmap[byte] & (0b10000000 >> (x % 8))))
            {
                if (getpixel(position.x + x, position.y + y) == bufferswap[x + y * imageres.x]) putpixel(position.x + x, position.y + y, buffer[x + y * imageres.x]);
            }
        }
    }
}