#include <limine.h>
#include "libstl/stdio.h"
#include "libstl/strings.h"

#include "sys/idt.h"
#include "drivers/input/keyboard.h"
#include "drivers/input/mouse.h"
#include "drivers/graphics.h"
#include "drivers/acpi.h"

#include "apps/ticto.h"

static volatile struct limine_boot_time_request boot_time = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0
};

void printbootinfo()
{
    point resolution = getresolution();

    puts("\nCopyright (C) 2022 (SplatTab)");
    puts("Welcome to SplatOS v0.07 Kernel\n\n");

    printf("Boot time In Unix: %d", boot_time.response->boot_time);
    printf("RSDP Signature: %s", rsdp_sig);
    printf("Screen Resolution: %dx%d", resolution.x, resolution.y);
}

void _start(void)
{
    ps2md_init();
    idt_init();
    kbd_init();
    pci_init();
    graphics_init();

    printbootinfo();

    char cmd[256];
    for (;;)
    {
        input(cmd, 256);

        if (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p')
        {
            printf("\n Commands: \n help - Usage: help <command> \n info - Usage: info \n echo - Usage: echo <string> \n clear - Usage: clear Aliases: cls \n ./ - Usage: ./<program> <arguments> \n");
        }
        else if (cmd[0] == 'e' && cmd[1] == 'c' && cmd[2] == 'h' && cmd[3] == 'o')
        {
            for (size_t i = 5; i < strnlen(cmd, 256); i++)
            {
                if (cmd[i] != '\0') putc(cmd[i]);
            }

            putc('\n');
        }
        else if ((cmd[0] == 'c' && cmd[1] == 'l') && (cmd[2] == 's' || (cmd[2] == 'e' && cmd[3] == 'a' && cmd[4] == 'r')))
        {
            print("\033[H\033[2J");
        }
        else if (cmd[0] == 'i' && cmd[1] == 'n' && cmd[2] == 'f' && cmd[3] == 'o')
        {
            printbootinfo();
        }
        else if (cmd[0] == '.' && cmd[1] == '/')
        {
            putc('\n');
            if (cmd[2] == 't' && cmd[3] == 'i' && cmd[4] == 'c' && cmd[5] == 't' && cmd[6] == 'o')
            {
                for (;;)
                {
                    if (ticto_update()) break;
                }
            }
        }
        else
        {
            puts("Error: Invalid Command");
        }
    }
}