#include <limine.h>
#include <stddef.h>
#include <libstl/strings.h>

static void OSInfoMain(void);
static void exit(void);

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static volatile struct limine_boot_time_request boot_time = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0
};

void _start(void)
{
    OSInfoMain();
    exit();
}

static void OSInfoMain(void)
{
    if (terminal_request.response == NULL || terminal_request.response->terminal_count < 1) exit();
    struct limine_terminal *terminal = terminal_request.response->terminals[0];

    terminal_request.response->write(terminal, "Copyright (C) 2022 (SplatTab)\n", 31);
    terminal_request.response->write(terminal, "Welcome to SplatOS v0.01 Kernel\n", 33);

    char bootTimeStr[11];
    ltos(bootTimeStr, boot_time.response->boot_time, 10);

    terminal_request.response->write(terminal, "Boot Time: ", 11);
    terminal_request.response->write(terminal, bootTimeStr, 10);
    terminal_request.response->write(terminal, "\n", 1);
}

static void exit(void)
{
    for (;;) __asm__("hlt");
}