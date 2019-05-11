#define RPNOK (1)
#define RPNNOK (0)

#ifndef RPN_STACK_SIZE
#define RPN_STACK_SIZE 100
#endif

int insertStackValue(long double *d);
int insertStackOperator(char op);
int getStack(int pos, long double *d);
int swap(void);
int drop(void);
int cleanStack(void);
