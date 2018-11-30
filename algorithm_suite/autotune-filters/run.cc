#include "run.h"

double
Run::calc_fpr()
{
	if (getBits() == 0) {
		return 0;
	}
	
	return exp(-(getBits()/getEntries())*pow(log(2),2));
}