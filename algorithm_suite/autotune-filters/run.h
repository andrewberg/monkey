#include <math.h>

/*
 * Class file for definition of a run and its entries
 * Used by the auto_tune_filters
 */

class Run {

	public:
		/* constructor for the Run */


		/* getter and setters of bits */

		int getBits() { return bits; }
		void setBits(int val) { bits = val; }

		/* getter and setters of entries data */

		int getEntries() { return entries; }
		void setEntries(int val) { entries = val; }

		/* calculate false positive rate for this filter */

		double calc_fpr();

	private:

		/* variables for the run entries */

		int entries; // number of entries in the given level
		int bits;    // number of bits allocated to this levels bloom filter

};