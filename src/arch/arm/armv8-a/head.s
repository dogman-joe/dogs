
.section ".text.head"

.globl _start
_start:
    mrs x0, mpidr_el1
    and     x0, x0, #3
    cbz x0,master
    b hang

hang: b hang

.globl dummy
dummy:
    ret
