#ifndef	_DOG_PROC_H
#define	_DOG_PROC_H

#include "dogtypes.h"

#define DOG_PROC_MAGIC 0xBADB
#define NUM_DOGS       0x03

/* Proc Table */
#define BEG_PROC_ADDR (&dogs[0])

struct dogproc dogs[NUM_DOGS];	/* process table */

#endif  /*_DOG_PROC_H */
