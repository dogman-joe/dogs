#ifndef PLAT_PROTO_H_
#define PLAT_PROTO_H_

#include "types.h"
#include "arch/armv7-a/io.h"


#define DOGTB_ADDRESS 0x40000000
#define GET_DTB_PTR() ((dtb_header *)(DOGTB_ADDRESS))

#endif   /* PLAT_PROTO_H_ */
