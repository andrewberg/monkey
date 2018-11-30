auto_filters.x: run.o run.h auto_tune_filters.o auto_tune_filters.h
	g++ -std=c++11 run.o auto_tune_filters.o -o auto_filters.x

auto_tune_filters.o: auto_tune_filters.cc auto_tune_filters.h
	g++ -std=c++11 -c auto_tune_filters.cc

run.o: run.cc run.h
	g++ -std=c++11 -c run.cc

clean:
	rm *.o *.x