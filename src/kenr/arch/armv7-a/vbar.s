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
.global svc_entry
svc_entry:
    mov r0, #3
    b light_led

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

.global invalid_exc
invalid_exc:
    b .
