#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>

#include "run.h"

double 
eval(double bits, double entries);

std::vector<Run>
take_entries();

std::vector<Run>
compute_levels();

int
take_size_ratio();

int
take_num_entries();

int
take_mem_budget();

void
create_runs(int ratio, int buffer, int entries, int bits_per_entry, std::vector<Run> & runs);

void
print_run_results(std::vector<Run>);

std::vector<Run>
auto_tune_filters(int, std::vector<Run> &);

double
try_switch(Run &, Run &, int, double);

void
run_tests(int memory_budget, std::vector<Run> & runs);

std::vector<Run>
state_of_art_computation(int, std::vector<Run> &);

int
calculate_bits(int num_entry, std::vector<Run> runs);

int
get_bits_level(int level, std::vector<Run> runs);