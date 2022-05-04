#include <limine.h>
#include "libstl/stdio.h"
#include "sys/idt.h"
#include "drivers/keyboard.h"

static volatile struct limine_boot_time_request boot_time = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0
};

void _start(void)
{
    idt_init();
    ps2_init();

    printf("Copyright (C) 2022 (SplatTab)\n");
    printf("Welcome to SplatOS v0.05 Kernel\n");
    printf("Boot time: %d\n", boot_time.response->boot_time);

    for(;;) getchar();
}