#pragma once
#include <limine.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void putc(char c);
void print(const char *msg);
void puts(const char *msg);
void printf(const char *format, ...);

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

void input(char str[], int nchars);

struct limine_terminal_response getconsole();