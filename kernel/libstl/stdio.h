#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void putc(char c);
void print(const char *msg);
void puts(const char *msg);
void printf(const char *format, ...);

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

uint16_t ins(uint16_t port);
void outs(uint16_t port, uint16_t data);

uint32_t inl(uint16_t port);
void out(uint16_t port, uint32_t data);