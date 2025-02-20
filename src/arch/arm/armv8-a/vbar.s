.macro  kernel_entry
    add sp, sp, #-16
    stp x0, x1, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x20, x21, [sp, #-16]!
    stp x22, x23, [sp, #-16]!
    stp x24, x25, [sp, #-16]!
    stp x26, x29, [sp, #-16]!
    stp x28, x29, [sp, #-16]!
    stp x30, xzr, [sp, #-16]!

    mrs x2, elr_el2
    mrs x3, spsr_el2

    stp x2, x3, [sp, #-16]!
.endm

.macro	kernel_exit
    ldp x2, x3, [sp], #16

    msr spsr_el2, x3
    msr elr_el2, x2

    ldp x30, xzr, [sp], #16
    ldp x28, x29, [sp], #16
    ldp x26, x27, [sp], #16
    ldp x24, x25, [sp], #16
    ldp x22, x23, [sp], #16
    ldp x20, x21, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x2, x3, [sp], #16
    ldp x0, x1, [sp], #16
    add sp, sp, #16
    eret
.endm

.balign	0x100

.align	0x10
.globl vectors
vectors:
    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b same_el_irq
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

    b not_yet_implemented
    .balign 0x80

not_yet_implemented:
    b err_hang

same_el_irq:
    kernel_entry
    bl arch_handle_irq
    kernel_exit

.globl write_vbar
write_vbar:
    adr	x0, vectors
    msr	vbar_el2, x0
    ret

.globl enable_irq
enable_irq:
    msr daifclr, #2
    ret

.globl disable_irq
disable_irq:
    msr	daifset, #2
    ret

.globl err_hang
err_hang:
    b err_hang
