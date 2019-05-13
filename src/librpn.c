#include <string.h>
#include <math.h>
/* #include <tgmath.h> */

#include "librpn.h"

int doCalculation(long double d1, char *operation, long double d2, long double *answer)
{
	/* https://en.cppreference.com/w/c/numeric/math */
	if(strcasecmp(operation, "+") == 0){
		*answer = d1 + d2;
	}else if(strcasecmp(operation, "-") == 0){
		*answer = d1 - d2;
	}else if(strcasecmp(operation, "*") == 0){
		*answer = d1 * d2;
	}else if(strcasecmp(operation, "/") == 0){
		*answer = d1 / d2;
	}else if(strcasecmp(operation, "powxy") == 0){
		*answer = powl(d1, d2);
	}else if(strcasecmp(operation, "logxy") == 0){
		*answer = logl(d2)/logl(d1);
	}else if(strcasecmp(operation, "!") == 0){
		for(; d1 > 1; d1--){
			*answer *= d1;
		}
	}else if(strcasecmp(operation, "sin") == 0){
		*answer = sinl(d1);
	}else if(strcasecmp(operation, "cos") == 0){
		*answer = cosl(d1);
	}else if(strcasecmp(operation, "tg") == 0){
		*answer = tanl(d1);
	}else if(strcasecmp(operation, "loge") == 0){
		*answer = logl(d1);
	}else if(strcasecmp(operation, "lg10") == 0){
		*answer = log10l(d1);
	}else if(strcasecmp(operation, "inv") == 0){
		*answer = 1/d1;
	}else if(strcasecmp(operation, "pow2x") == 0){
		*answer = exp2l(d1);
	}else if(strcasecmp(operation, "R") == 0){
		*answer = sqrtl(d1);
	}else if(strcasecmp(operation, "") == 0){
	/*
	}else if(strcasecmp(operation, "") == 0){
	}else if(strcasecmp(operation, "") == 0){
	*/
	}else{
		return(RPNNOK);
	}

	return(RPNOK);
}

/* --------------- */

int startRPNCalculator(rpn_t *calc)
{
	memset(calc, 0, sizeof(rpn_t));

	return(RPNOK);
}

int insertStackOperator(rpn_t *calc, char *op)
{
	if(calc->top == 0)
		return(RPNNOK);



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
