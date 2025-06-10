#ifndef DOGPRINT_H_
#define DOGPRINT_H_

typedef u64 console;

void dogprint_init(console *console_base);

int dogprint(char *s);
int dogprintnum(u32 x);
int dogprintnum64(u64 x);

#endif  /*DOGPRINT_H_*/

