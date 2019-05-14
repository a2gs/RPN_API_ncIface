#define RPNOK (1)
#define RPNNOK (0)

#ifndef RPN_STACK_SIZE
#define RPN_STACK_SIZE 100
#endif

typedef struct _rpn_t{
	long double stack[RPN_STACK_SIZE];
	unsigned int top;
}rpn_t;

int startRPNCalculator(rpn_t *calc);
int insertStackValue(rpn_t *calc, long double d);
int insertStackOperator(rpn_t *calc, char *op);
int getStack(rpn_t *calc, unsigned int pos, long double *d);
int getStackLIFO(rpn_t *calc, unsigned int pos, long double *d);
int swap(rpn_t *calc);
int drop(rpn_t *calc);
int cleanStack(rpn_t *calc);
