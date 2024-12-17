.section ".text"
.balign	0x100

.globl do_sysdog
do_sysdog:
   svc 0

.globl switch_context
switch_context:

    stm r0!, {r0-r14}

    mrs r0, spsr

    /* Set SPSR and LR for return */
    ldr r0, [r1, #60]
    msr spsr_fsxc, r0

    /* Restore user-mode registers from dogproc struct */
    ldm r1, {r0-r14}

    movs pc, lr

