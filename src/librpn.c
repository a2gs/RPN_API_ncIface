#include <string.h>
#include <math.h>

#include "librpn.h"

int startRPNCalculator(rpn_t *calc)
{

/*
 https://en.cppreference.com/w/c/numeric/math/nan
 https://stackoverflow.com/questions/14174991/how-to-define-nan-value-in-ansi-c
NaN isn't an "abstract type". It's a value of a floating-point datum.

If by "ANSI C" you mean standard C (which is the actual meaning of the term, in as much as it has one), include <math.h> and use the NAN macro to produce a nan, and isnan(x) to detect one.

If by "ANSI C" you actually mean the long-replaced C89 standard (which some people intend, even if it isn't formally correct), you can produce a NaN value with 0./0., and check for one with x != x.

*/
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

int getStack(rpn_t *calc, int pos, long double *d)
{
	if(pos >= RPN_STACK_SIZE || calc->top == 0)
		return(RPNNOK);

	*d = calc->stack[pos];

	return(RPNOK);
}

int swap(rpn_t *calc)
{


	return(RPNOK);
}

int drop(rpn_t *calc)
{


	return(RPNOK);
}

int cleanStack(rpn_t *calc)
{


	return(RPNOK);
}
