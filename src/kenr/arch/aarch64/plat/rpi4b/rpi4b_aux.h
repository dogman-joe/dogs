#ifndef _RPI4B_AUX_H
#define _RPI4B_AUX_H

#include"types.h"

#define AUX_BASE     0xFE215000
#define MINI_BASE    0xFE215040

struct rpi4b_aux
{
  u32 AUX_IRQ;
  u32 AUX_ENABLES;
}__attribute__((packed, aligned(4)));

struct rpi4b_aux_mini
{
  u8  MU_IO[4];
  u32 MU_IER;
  u32 MU_IIR;
  u32 MU_LCR;
  u32 MU_MCR;
  u32 MU_LSR;
  u32 MU_SCRATCH[6];
  u32 MU_CNTL;
  u32 MU_BAUD;
}__attribute__((packed, aligned(4)));

#endif   /* _RPI4B_AUX_H */
