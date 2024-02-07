.data

.equ SCTLR_VALUE, 0x30d00800
.equ HCR_VALUE,   0x80000000
.equ SCR_VALUE,   0x00000431
.equ SPSR_VALUE,  0x000001C5

.section ".text"
.balign	0x100

.globl get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret
.globl master
master:
    ldr	x0, =SCTLR_VALUE
    msr	sctlr_el1, x0
    ldr	x0, =HCR_VALUE
    msr	hcr_el2, x0

    ldr	x0, =SCR_VALUE
    msr	scr_el3, x0

    ldr	x0, =SPSR_VALUE
    msr	spsr_el3, x0

    adr	x0, el1_entry
    msr	elr_el3, x0

    eret

skip:
    mov x0,x30
    bl notmain

el1_entry:

    mov sp,#0x400000
    bl      notmain
.globl dog_spawn
dog_spawn:
   mov x0, x20
   blr x19

.globl switch_context
switch_context:
    mov x9, sp
    stp	x19, x20, [x0], #16  // store callee-saved registers
    stp	x21, x22, [x0], #16
    stp	x23, x24, [x0], #16
    stp	x25, x26, [x0], #16
    stp	x27, x28, [x0], #16
    stp	x29, x9, [x0], #16
    str	x30, [x0]
    ldp	x19, x20, [x1], #16  // restore callee-saved registers
    ldp	x21, x22, [x1], #16
    ldp	x23, x24, [x1], #16
    ldp	x25, x26, [x1], #16
    ldp	x27, x28, [x1], #16
    ldp	x29, x9,  [x1], #16
    ldp	x30, xzr, [x1]
    mov sp, x9
    ret
