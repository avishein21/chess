CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -O2

main: main.o util.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o main main.o util.o

test_unit: test_unit.o util.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test_unit test_unit.o util.o

util.o: util.h util.cpp
	$(CXX) $(CXXFLAGS) -c util.cpp

clean: 
	rm -f $(EXECS)  *.o main
