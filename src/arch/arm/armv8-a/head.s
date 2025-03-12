
.section ".text.head"

.globl _start
_start:
    mrs x0, mpidr_el1
    and x0, x0, #3
    ldr x30, =stack_top	// setup stack
    mov sp, x30

    cbz x0, dogmain
    b hang

hang: b hang

.globl dummy
dummy:
    ret
