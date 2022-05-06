#include <limine.h>
#include "acpi.h"

static volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};

uint8_t rsdp_sig[8];

void pci_init()
{
    rsdp_sig[0] = *(uint8_t*)rsdp_request.response->address;
    for (int i = 0; i < 8; i++)
    {
        rsdp_sig[i] = *((uint8_t*)rsdp_request.response->address + i);
    }
}