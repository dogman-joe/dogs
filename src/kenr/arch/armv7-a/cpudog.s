.section ".text"
.balign	0x100

.globl do_sysdog
do_sysdog:
   svc 0

.globl switch_context
switch_context:
    mov sp, r0

    /* Set SPSR and LR for return */
    ldr r0, [sp, #64]
    msr spsr_fsxc, r0 		/* flags , status, extension control. */

    /* Restore user-mode registers from proc struct */
    ldm sp, {r0-r14}^

    movs pc, lr

