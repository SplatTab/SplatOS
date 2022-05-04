#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct idt_entry
{
    uint16_t Offset1;
    uint16_t Selector;
    uint8_t IST;
    uint8_t TypeAttr;
    uint16_t Offset2;
    uint32_t Offset3;
    uint32_t Zero;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr
{
    uint16_t Limit;
    uint64_t Base;
} __attribute__((packed)) idt_ptr_t;

typedef struct registers_t
{
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
    uint64_t int_no, error_code, rip, cs, rflags, rsp, ss;
} __attribute__((packed)) registers_t;

typedef void (*isr_t)(struct registers_t*);

void register_interrupt_handler(uint8_t vector, isr_t handler);
void irq_handler(struct registers_t *regs);
void idt_init();