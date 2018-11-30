#include <math.h>
#include <vector>
#include <iostream>

#include "run.h"

double 
eval(double bits, double entries);

std::vector<Run>
take_entries();

int
take_mem_budget();

void
print_run_results(std::vector<Run>);

std::vector<Run>
auto_tune_filters(int, std::vector<Run>);

double
try_switch(Run &, Run &, int, double);

void
run_tests();

std::vector<Run>
state_of_art_computation(int, std::vector<Run> &);