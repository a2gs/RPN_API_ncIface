#include <string.h>
#include <math.h>

#include "librpn.h"

int startRPNCalculator(rpn_t *calc)
{
	memset(calc, 0, sizeof(rpn_t));

	return(RPNOK);
}

int insertStackOperator(rpn_t *calc, char op)
{


	return(RPNOK);
}

int insertStackValue(rpn_t *calc, long double *d)
{
	if(calc->top == RPN_STACK_SIZE)
		return(RPNNOK);

	calc->stack[calc->top] = *d;
	calc->top++;

	return(RPNOK);
}

int getStackLIFO(rpn_t *calc, unsigned int pos, long double *d)
{
	if(pos >= RPN_STACK_SIZE || calc->top == 0 || pos >= calc->top)
		return(RPNNOK);

	*d = calc->stack[calc->top - 1 - pos];

	return(RPNOK);
}

int getStack(rpn_t *calc, unsigned int pos, long double *d)
{
	if(pos >= RPN_STACK_SIZE || calc->top == 0 || pos >= calc->top)
		return(RPNNOK);

	*d = calc->stack[pos];

	return(RPNOK);
}

int swap(rpn_t *calc)
{
	long double sw = 0.0;

	if(calc->top <= 1)
		return(RPNNOK);

	sw = calc->stack[calc->top - 1];
	calc->stack[calc->top - 1] = calc->stack[calc->top - 2];
	calc->stack[calc->top - 2] = sw;

	return(RPNOK);
}

int drop(rpn_t *calc)
{
	if(calc->top == 0)
		return(RPNNOK);

	calc->stack[calc->top] = 0.0;
	calc->top--;

	return(RPNOK);
}

int cleanStack(rpn_t *calc)
{
	startRPNCalculator(calc);
	return(RPNOK);
}
