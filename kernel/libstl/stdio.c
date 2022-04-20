#include <limine.h>
#include <stdio.h>
#include <stddef.h>

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static const char CONVERSION_TABLE[] = "0123456789abcdef";

void putct(char c) {
    if (terminal_request.response == NULL || terminal_request.response->terminal_count < 1) return;
    char buffer[2] = {c, '\0'};
    terminal_request.response->write(terminal_request.response->terminals[0], buffer, 1);
}

void printt(const char *msg) {
    for (size_t i = 0; msg[i]; i++) putct(msg[i]);
}

void putst(const char *msg) {
    printt(msg);
    putct('\n');
}

static void printhext(size_t num) {
    int i;
    char buf[17];

    if (!num)
    {
        printt("0x0");
        return;
    }

    buf[16] = 0;

    for (i = 15; num; i--)
    {
        buf[i] = CONVERSION_TABLE[num % 16];
        num /= 16;
    }

    i++;
    printt("0x");
    printt(&buf[i]);
}

static void printdect(size_t num) {
    int i;
    char buf[21] = {0};

    if (!num) {
        putct('0');
        return;
    }

    for (i = 19; num; i--) {
        buf[i] = (num % 10) + 0x30;
        num = num / 10;
    }

    i++;
    printt(buf + i);
}

void printft(const char *format, ...) {
    va_list argp;
    va_start(argp, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == 'x') {
                printhext(va_arg(argp, size_t));
            } else if (*format == 'd') {
                printdect(va_arg(argp, size_t));
            } else if (*format == 's') {
                printt(va_arg(argp, char*));
            }
        } else {
            putct(*format);
        }
        format++;
    }

    putct('\n');
    va_end(argp);
}