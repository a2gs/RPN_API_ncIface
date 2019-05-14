#include <stdio.h>
#include <string.h>
#include <math.h>
/* #include <tgmath.h> */

#include "librpn.h"

int calculationType(char *operation, char *opType)
{
	/* https://en.cppreference.com/w/c/numeric/math */
	if     (strcasecmp(operation, "+")     == 0) *opType = 2;
	else if(strcasecmp(operation, "-")     == 0) *opType = 2;
	else if(strcasecmp(operation, "*")     == 0) *opType = 2;
	else if(strcasecmp(operation, "/")     == 0) *opType = 2;
	else if(strcasecmp(operation, "powxy") == 0) *opType = 2;
	else if(strcasecmp(operation, "logxy") == 0) *opType = 2;
	else if(strcasecmp(operation, "!")     == 0) *opType = 1;
	else if(strcasecmp(operation, "sin")   == 0) *opType = 1;
	else if(strcasecmp(operation, "cos")   == 0) *opType = 1;
	else if(strcasecmp(operation, "tg")    == 0) *opType = 1;
	else if(strcasecmp(operation, "loge")  == 0) *opType = 1;
	else if(strcasecmp(operation, "lg10")  == 0) *opType = 1;
	else if(strcasecmp(operation, "inv")   == 0) *opType = 1;
	else if(strcasecmp(operation, "pow2x") == 0) *opType = 1;
	else if(strcasecmp(operation, "R")     == 0) *opType = 1;
	/*
	}else if(strcasecmp(operation, "") == 0){
	}else if(strcasecmp(operation, "") == 0){
	}else if(strcasecmp(operation, "") == 0){
	*/
	else{
		*opType = 0;
		return(RPNNOK);
	}

	return(RPNOK);
}

int doCalculation(long double d1, char *operation, long double d2, long double *answer, char *opType)
{
	/* https://en.cppreference.com/w/c/numeric/math */
	if(strcasecmp(operation, "+") == 0){
		*answer = d1 + d2;
		*opType = 2;
	}else if(strcasecmp(operation, "-") == 0){
		*answer = d1 - d2;
		*opType = 2;
	}else if(strcasecmp(operation, "*") == 0){
		*answer = d1 * d2;
		*opType = 2;
	}else if(strcasecmp(operation, "/") == 0){
		*answer = d1 / d2;
		*opType = 2;
	}else if(strcasecmp(operation, "powxy") == 0){
		*answer = powl(d1, d2);
		*opType = 2;
	}else if(strcasecmp(operation, "logxy") == 0){
		*answer = logl(d2)/logl(d1);
		*opType = 2;
	}else if(strcasecmp(operation, "!") == 0){
		for(; d1 > 1; d1--){
			*answer *= d1;
		}
		*opType = 1;
	}else if(strcasecmp(operation, "sin") == 0){
		*answer = sinl(d1);
		*opType = 1;
	}else if(strcasecmp(operation, "cos") == 0){
		*answer = cosl(d1);
		*opType = 1;
	}else if(strcasecmp(operation, "tg") == 0){
		*answer = tanl(d1);
		*opType = 1;
	}else if(strcasecmp(operation, "loge") == 0){
		*answer = logl(d1);
		*opType = 1;
	}else if(strcasecmp(operation, "lg10") == 0){
		*answer = log10l(d1);
		*opType = 1;
	}else if(strcasecmp(operation, "inv") == 0){
		*answer = 1/d1;
		*opType = 1;
	}else if(strcasecmp(operation, "pow2x") == 0){
		*answer = exp2l(d1);
		*opType = 1;
	}else if(strcasecmp(operation, "R") == 0){
		*answer = sqrtl(d1);
		*opType = 1;
	/*
	}else if(strcasecmp(operation, "") == 0){
	}else if(strcasecmp(operation, "") == 0){
	}else if(strcasecmp(operation, "") == 0){
	*/
	}else{
		*opType = 0;
		return(RPNNOK);
	}

	fprintf(stderr, "[%Lg] %s [%Lg] = [%Lg] (%u)\n", d1, operation, d2, *answer, *opType);

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
	long double answer = 0.0;
	char opType = 0;

	if(calc->top == 0)
		return(RPNNOK);

	fprintf(stderr, "calc->top [%d]    ", calc->top);

	if(calc->top == 1){
		if(doCalculation(0.0, op, calc->stack[calc->top-1], &answer, &opType) == RPNNOK)
			return(RPNNOK);
	}else{
		if(doCalculation(calc->stack[calc->top-2], op, calc->stack[calc->top-1], &answer, &opType) == RPNNOK)
			return(RPNNOK);
	}

	drop(calc);

	if(opType == 2)
		drop(calc);

	insertStackValue(calc, &answer);

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
