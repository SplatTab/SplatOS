#include "stdio.h"
#include <limine.h>
#include <stddef.h>

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static const char CONVERSION_TABLE[] = "0123456789abcdef";

void putc(char c) {
    if (terminal_request.response == NULL || terminal_request.response->terminal_count < 1) return;
    char buffer[2] = {c, '\0'};
    terminal_request.response->write(terminal_request.response->terminals[0], buffer, 1);
}

void print(const char *msg) {
    for (size_t i = 0; msg[i]; i++) putc(msg[i]);
}

void puts(const char *msg) {
    print(msg);
    putc('\n');
}

static void printhex(size_t num) {
    int i;
    char buf[17];

    if (!num)
    {
        print("0x0");
        return;
    }

    buf[16] = 0;

    for (i = 15; num; i--)
    {
        buf[i] = CONVERSION_TABLE[num % 16];
        num /= 16;
    }

    i++;
    print("0x");
    print(&buf[i]);
}

static void printdec(size_t num) {
    int i;
    char buf[21] = {0};

    if (!num) {
        putc('0');
        return;
    }

    for (i = 19; num; i--) {
        buf[i] = (num % 10) + 0x30;
        num = num / 10;
    }

    i++;
    print(buf + i);
}

void printf(const char *format, ...) {
    va_list argp;
    va_start(argp, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == 'x') {
                printhex(va_arg(argp, size_t));
            } else if (*format == 'd') {
                printdec(va_arg(argp, size_t));
            } else if (*format == 's') {
                print(va_arg(argp, char*));
            }
        } else {
            putc(*format);
        }
        format++;
    }

    putc('\n');
    va_end(argp);
}

void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile("outb %1, %0" :: "dN"(port), "a"(val));
}

uint8_t inb(uint16_t port)
{
    uint8_t data;
    __asm__ volatile("inb %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

uint16_t ins(uint16_t port)
{
    uint16_t rv;
    __asm__ volatile ("inw %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

void outs(uint16_t port, uint16_t data)
{
    __asm__ volatile ("outw %1, %0" : : "dN" (port), "a" (data));
}

uint32_t inl(uint16_t port)
{
    uint32_t rv;
    __asm__ volatile ("inl %%dx, %%eax" : "=a" (rv) : "dN" (port));
    return rv;
}

void out(uint16_t port, uint32_t data)
{
    __asm__ volatile ("outl %%eax, %%dx" : : "dN" (port), "a" (data));
}