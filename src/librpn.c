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


	return(RPNOK);
}

int getStack(rpn_t *calc, int pos, long double *d)
{


	return(RPNNOK);
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
