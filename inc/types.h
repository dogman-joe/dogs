#ifndef TYPES_H_
#define TYPES_H_

typedef enum {
  DOGSTATUS_SUCCESS,
  DOGSTATUS_ERROR,
  DOGSTATUS_INVALID_PARAM
} dog_status_t;

/* Time stuff */
typedef long int __time_t;
typedef __time_t time_t;

/* Size stuff */
typedef long int __size_t;
typedef __size_t size_t;

typedef unsigned char        u8;
typedef unsigned short       u16;
typedef unsigned int         u32;
typedef unsigned long long   u64;

#define BIT(bit) ((u32)(1U << (bit)))

#endif   /* TYPES_H_ */
