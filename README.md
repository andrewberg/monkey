 # Monkey Key Value Store 


To compile Monkey you must have GCC, CMAKE, and G++.

Must be on Linux (tested on Ubuntu).

Clone github repo.

Navigate to the repo and run:

mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

Navigate to ./test_suite and run 'make'.

Run ./monkey_test.x to run it.
