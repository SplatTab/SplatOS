#include <limine.h>
#include <stddef.h>
#include <libstl/stdio.h>

static void OSInfoMain(void);
static void exit(void);

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
    putst("Copyright (C) 2022 (SplatTab)\n");
    putst("Welcome to SplatOS v0.01 Kernel\n");
    printft("Boot time: %d\n", boot_time.response->boot_time);
}

static void exit(void)
{
    for (;;) __asm__("hlt");
}