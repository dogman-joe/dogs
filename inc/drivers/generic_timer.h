#ifndef GENERIC_TIMER_H_
#define GENERIC_TIMER_H_

#define GENERIC_TIMER_IRQ_NO 27U

dog_status_t generic_timer_init(void);
void generic_timer_handle(void);

#endif   /* GENERIC_TIMER_H_ */
