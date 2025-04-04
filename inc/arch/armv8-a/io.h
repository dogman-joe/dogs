#ifndef IO_H_
#define IO_H_

#include "types.h"

#define GET8(a)     (*(volatile u8 *)(a))
#define PUT8(a, v)   (*(volatile u8 *)(a) = (v))
#define GET16(a)    (*(volatile u16 *)(a))
#define PUT16(a, v)  (*(volatile u16 *)(a) = (v))
#define GET32(a)    (*(volatile u32 *)(a))
#define PUT32(a, v)  (*(volatile u32 *)(a) = (v))

#endif /* IO_H_ */
