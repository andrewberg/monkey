/* 
 * Definition of system variables that go into modeling the design space for
 * merge policy and size ratio for LSM-trees based on given data such as
 * defined below
 */

/* defines the characeristics of the given dataset for optimization */

class DataInfo {
public:
	
	/* ratio of zero-result point looks ups */
	double r_ratio;

	/* ratio of non-zero-result point looks ups */
	double v_ratio;

	/* ratio of updates */
	double w_ratio;

	/* ratio of zero-result point looks ups */
	double q_ratio;
};

/* defines the system info for computation of theta in algorithm */

class SystemInfo{
public:
	/* budget for in memory bloom filters to be allocated to */
	int memory_budget;

	/* size ratio between different levels */
	int T;

	/* number of levels in the key-value store */
	int L;

	/* total number of entries in the key-value store */
	int N;

	/* size of antry in the key-value store (bits) */
	int E;

	/* number of entries that into a disk page */
	int B;
};
