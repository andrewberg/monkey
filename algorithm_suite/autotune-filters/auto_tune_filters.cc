#include "auto_tune_filters.h"

/*
 * main function for this function to test functionality before moving
 * to implementation to LevelDB
 */


/*int
main()
{
	//run_tests();

	std::vector<Run> runs;

	int num_entries = 500000;
	int bits_per_entry = 5;
	int size_per_entry = 1024;
	int size_ratio = 2;

	int memory_budget = num_entries * bits_per_entry;

	create_runs(size_ratio, size_per_entry, num_entries, bits_per_entry, runs);

	run_tests(memory_budget, runs);

	std::cout << get_bits_level(4, runs) << std::endl;

	return 0;
}*/

/*
 * Algorithm 1: Allocate memory_budget to minizime the sum of False Positive Rates
 * memory_budget is allocated throughout the different levels to minizime
 * the sums of the FPR
 */

std::vector<Run>
auto_tune_filters(int memory_budget, std::vector<Run> & runs)
{
	int delta = memory_budget; // given memory budget from input
	runs[1].setBits(memory_budget); // allocate all memory to run 0 to start

	double R = runs.size() - 1 + eval(runs[0].getBits(), runs[0].getEntries());
	while (delta >= 1) {
		double R_new = R;

		for (int i = 1; i < runs.size() - 1; ++i) {
			for (int j = i + 1; j < runs.size(); ++j) {
				R_new = try_switch(runs[i], runs[j], delta, R);
				R_new = try_switch(runs[j], runs[i], delta, R);
			}
		}

		if (R_new == R) {
			delta = delta/2;
		}

		R = R_new;
	}

	return runs;
}

/*
 * Algorithm 2: Allows for testing of the evaluation of the test runs memory
 * allocation to see if the runs would be able to minimize the amount of 
 * False Positives for a given memory budget
 */

double
try_switch(Run &run1, Run &run2, int delta, double R)
{
	double R_new = R - eval(run1.getBits(), run1.getEntries())
					 - eval(run2.getBits(), run2.getEntries())
					 + eval(run1.getBits() + delta, run1.getEntries())
					 + eval(run2.getBits() - delta, run2.getEntries());

	if (R_new < R && ((run2.getBits() - delta) > 0)) {
		R = R_new;

		run1.setBits(run1.getBits() + delta);
		run2.setBits(run2.getBits() - delta);
	}

	return R;
}

/*  
 * algorithm 3: returns the false positive rate of a Bloom Filter
 * allows for calculation of FPR based on the given bits and entries
 * helper function for Algorithm 1
*/

double
eval(double bits, double entries)
{
	return exp(-(bits/entries)*pow(log(2),2));
}

/*
 * function to take test entries data from stdin
 * takes entries and assigns the number of entries at each level
 * for use in Algorithm 1
 */

std::vector<Run>
take_entries()
{
	std::vector<Run> runs;

	int num_entries;

	/* take from input and establish the different run objects in vector form */
	while (std::cin >> num_entries) {
		Run current_run (num_entries, 0);

		runs.push_back(current_run);
	}

	return runs;
}

/*
 * takes as input the memory budget for the bloom filters for Algorithm 1
 * calculation mem budget is the given number of entries * average bits
 * per entry
 */

int
take_mem_budget()
{
	int num_bits;
	std::cin >> num_bits;

	return num_bits;
}

/*
 * function to print out the vector of runs after computation
 */

void
print_run_results(std::vector<Run> runs)
{
	double total_fpr;

	for (int i = 0; i < runs.size(); ++i) {
		Run current_run = runs[i];

		std::cout << "Level " << i << ", " << std::endl;
		std::cout << "Number of entries: " << current_run.getEntries() 
			<< std::endl;
		std::cout << "Number of bits: " << current_run.getBits() << std::endl;
		
		double fpr = current_run.calc_fpr();

		total_fpr += fpr;

		std::cout << "False Positive Rate (FPR): " << fpr << std::endl;

		std::cout << "Bits per entry: " 
			<< current_run.getBits()/current_run.getEntries() << std::endl;

		std::cout << std::endl;
	}

	std::cout << "Worst Case Total False Positive Rate (FPR): " <<  total_fpr
		<< std::endl;


	std::cout << std::endl;
}

/*
 * function to run the test data in comparision to State of the Art
 * to Monkey algorithm to be able to show differences
 */

void
run_tests(int memory_budget, std::vector<Run> & runs)
{

	std::vector<Run> monkey_filters = 
		auto_tune_filters(memory_budget, runs);

	//std::vector<Run> leveldb_filters = 
	//	state_of_art_computation(memory_budget, runs);

	//std::cout << "--- MONKEY LEVELS ---" << std::endl;
	//print_run_results(monkey_filters);

	//std::cout << "--- LEVELDB LEVELS ---" << std::endl;
	//print_run_results(leveldb_filters);
}

/*
 * Computes the LevelDB constant False Positive Rate accross all of the bloom
 * filters
 */

std::vector<Run>
state_of_art_computation(int memory_budget, std::vector<Run> & runs)
{

	/* 
	 * sum up the number of elements to calculate the number of bits per
	 * entry to be able to calculate leveldb FPR's
	*/

	int total_entries = 0;

	for (int i = 0; i < runs.size(); ++i) {
		total_entries += runs[i].getEntries();
	}

	/* calculation of bits per entry */

	double bits_per_entry = memory_budget/total_entries;

	/* set a constant number of bits per run for the given runs */

	for (int i = 1; i < runs.size(); ++i) {
		runs[i].setBits(runs[i].getEntries() * bits_per_entry);
	}

	return runs;
}

int
take_size_ratio()
{
	int size_ratio;

	std::cin >> size_ratio;

	return size_ratio;
}

int
take_num_entries()
{
	int total_entries;

	std::cin >> total_entries;

	return total_entries;
}

int
take_buffer()
{
	int buffer;

	std::cin >> buffer;

	return buffer;
}

int
take_bits_per_entry()
{
	int bits_per_entry;

	std::cin >> bits_per_entry;

	return bits_per_entry;
}

void
create_runs(int size_ratio, int buffer, int entries, int bits_per_entry, std::vector<Run> & runs)
{

	int level = buffer;

	int mem_budget = bits_per_entry * entries;

	int entries_left = entries;

	int cur_entries = 0;

	int total = 0;

	// go until total entries left will not fill up next level

	while (entries_left >= level) {
		total += level;
		entries_left -= level;
		
		runs.push_back(Run(level, 0));

		level *= size_ratio;
	}

	runs.push_back(Run(entries_left, 0));

}

int
calculate_bits(int num_entry, std::vector<Run> runs)
{
	int total = 0;

	std::reverse(runs.begin(), runs.end());

	for (int i = 0; i < runs.size(); ++i) {
		total += runs[i].getEntries();
		if (num_entry < total) {
			return runs[i].getBits()/runs[i].getEntries();
		}
	}

	return 5;
}

int
get_bits_level(int level, std::vector<Run> runs)
{
	return runs[level].getBits()/runs[level].getEntries();
}


