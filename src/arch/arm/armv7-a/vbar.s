.balign	0x100
.global exc_vector_table
exc_vector_table:
    ldr pc, =invalid_exc           /* Reset */
    ldr pc, =invalid_exc           /* Reset */
    ldr pc, =svc_entry           /* Fast Interrupt */
    ldr pc, =invalid_exc           /* Fast Interrupt */
    ldr pc, =invalid_exc           /* Fast Interrupt */
    ldr pc, =invalid_exc           /* Fast Interrupt */
    ldr pc, =irq_entry             /* Interrupt */
    ldr pc, =invalid_exc           /* Fast Interrupt */

.balign	0x100
svc_entry:
    mov r0, #3
    b hello

.globl irq_entry
irq_entry:
  stmfd sp!, {r0-r12, lr}

  mrs r11, spsr
  push {r11}

  blx plat_irq_handle

  pop {r11}
  msr spsr, r11

  ldmfd sp!, {r0-r12, lr}

  subs pc, lr, #4

.globl enable_irq
enable_irq:
    cpsie i
    bx lr

.globl disable_irq
disable_irq:
    cpsid i
    bx lr

.global invalid_exc
invalid_exc:
    b .
