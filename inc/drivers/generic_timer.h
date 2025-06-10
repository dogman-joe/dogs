#ifndef GENERIC_TIMER_H_
#define GENERIC_TIMER_H_

#define GENERIC_TIMER_INT_NO 27

u32 cntfrq; /* generic timer frequency */

void generic_timer_init();
void generic_timer_handle();

#endif   /* GENERIC_TIMER_H_ */
