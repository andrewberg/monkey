#include "system.h"

/* 
 * Defines Algorithm 5 to autotune the merge and size ratio from a given set of 
 * using modeling throughput average with theta = r*R + v*V + q*Q + w*W where
 * this is used as the cornerstone of Algorithm 5 
*/

class AutoTuneMergeRatio {
public:
	class DataInfo data;
	class SystemInfo system;

	/* function to compute theta model: theta = r*R + v*V + q*Q + w*W*/
	int
	theta_computation(int, bool);

	/* function to compute R (model for zero-result lookup cost) */
	int
	R_computation();

	/* function to compute V (model for worst-case non-zero-result lookup cost) */
	int
	V_computation();

	/* function to compute W (model for worst-case update cost) */
	int
	W_computation();

	/**/



};
