CXX = g++ -std=c++11
CXXFLAGS  = -Wall -g -pthread
OFILES = main.o
CXXFILES = main.cpp

program: $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) -o max_finder

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp