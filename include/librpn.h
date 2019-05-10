#define RPNOK (1)
#define RPNNOK (0)

#ifndef RPN_STACK_SIZE
#define RPN_STACK_SIZE 100
#endif

int insertStack(double *d);
int getStack(int pos, double *d);
int swap(void);
int drop(void);
int cleanStack(void);
