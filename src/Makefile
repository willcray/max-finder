CXX = g++ -std=c++11
CXXFLAGS  = -Wall -g -pthread
HEADERS = max_finder.h barrier.h
OFILES = barrier.o max_finder.o main.o
CXXFILES = main.cpp barrier.cpp max_finder.cpp

program: $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) -o max_finder

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

barrier.o: barrier.cpp barrier.h
	$(CXX) $(CXXFLAGS) -c barrier.cpp

max_finder.o: max_finder.cpp max_finder.h
	$(CXX) $(CXXFLAGS) -c max_finder.cpp
