#pragma once
#include <stdint.h>
#include "libstl/math.h"

extern struct limine_framebuffer *fb;

void graphics_init();

void putpixel(int x, int y, uint32_t color);
uint32_t getpixel(int x, int y);

void drawbitmap(uint8_t *bitmap, point position, point imageres, uint32_t color, uint32_t *buffer, uint32_t *bufferswap);
void clearbitmap(uint8_t *bitmap, point position, point imageres, uint32_t *buffer, uint32_t *bufferswap);