#include "idt.h"
#include "libstl/stdio.h"

static const char *exception_messages[32] = {
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Detected overflow",
    "Out-of-bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

void exception_handler(struct registers_t *regs)
{
    print("\nSystem Exception!\n");
    print(exception_messages[regs->int_no]);
    for (;;) __asm__ volatile ("cli; hlt");
}

void int_handler(struct registers_t *regs)
{
    if (regs->int_no < 32) exception_handler(regs);
    else if (regs->int_no >= 32 && regs->int_no < 256) irq_handler(regs);
}