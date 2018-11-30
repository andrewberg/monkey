monkey_test.x: test.cpp ../build
	g++ -std=c++11 test.cpp -MMD -I ../include/ -L ../build -o monkey_test.x -lleveldb -lpthread

clean:
	rm *.o *.x