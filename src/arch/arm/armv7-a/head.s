//
// interrupt service routines
//
.syntax unified
.data

.equ MODE_USR, 0x10
.equ MODE_IRQ, 0x12
.equ MODE_SVC, 0x13
.equ MODE_SYS, 0x1F

.section ".text.head"

.balign	0x100

.globl _start
_head:

   /* IRQ stack */
    msr cpsr_c, MODE_IRQ
    ldr sp, =_irq_stack_end


    msr cpsr_c, MODE_SVC
    ldr sp, =_kenr_stack_end

    bl dogmain
hang: b hang

.globl write_vbar
write_vbar:
    mcr p15, 0x0, r0, c12, c0, 0x0
    bx lr

.globl dummy
dummy:
    bx lr
