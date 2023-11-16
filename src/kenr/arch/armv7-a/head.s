//
// interrupt service routines
//
.syntax unified
.data

.equ MODE_IRQ, 0x12
.equ MODE_SVC, 0x13

.section ".text.head"

.balign	4

.globl _start
_head:

   /* IRQ stack */
    msr cpsr_c, MODE_IRQ
    ldr sp, =_irq_stack_end

    /* Supervisor mode */
    msr cpsr_c, MODE_SVC

    ldr sp, =_init_stack_end
    bl notmain
hang: b hang

.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.globl write_vbar
write_vbar:
    mcr p15, 0x0, r0, c12, c0, 0x0
    bx lr

.globl dummy
dummy:
    bx lr
