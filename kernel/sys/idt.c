#include "idt.h"
#include "libstl/stdio.h"

struct idt_entry idt[256];

struct idt_ptr idtr;

isr_t interrupt_handlers[256];
extern void *int_table[];

void idt_set_descriptor(uint8_t vector, void *isr)
{
    idt[vector].Offset1 = (uint64_t)isr;
    idt[vector].Selector = 0x28;
    idt[vector].IST = 0;
    idt[vector].TypeAttr = 0x8E;
    idt[vector].Offset2 = (uint64_t)isr >> 16;
    idt[vector].Offset3 = (uint64_t)isr >> 32;
    idt[vector].Zero = 0;
}

void register_interrupt_handler(uint8_t vector, isr_t handler)
{
    interrupt_handlers[vector] = handler;
}

void irq_handler(struct registers_t *regs)
{
    if (interrupt_handlers[regs->int_no]) interrupt_handlers[regs->int_no](regs);
    if (regs->int_no >= 40) outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void idt_init()
{
    idtr.Limit = sizeof(struct idt_entry) * 256 - 1;
    idtr.Base = (uintptr_t)&idt[0];
    for (size_t i = 0; i < 256; i++) idt_set_descriptor(i, int_table[i]);
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x00);
    outb(0xA1, 0x00);
    __asm__ volatile ("cli");
    __asm__ volatile ("lidt %0" : : "memory"(idtr));
    __asm__ volatile ("sti");
}