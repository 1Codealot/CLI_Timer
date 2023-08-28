CXX = g++
CXXFLAGS = -std=c++17

SRCS = main.cpp scrambles.hpp NxNMoveGen.hpp fileIO.hpp
OBJS = $(SRCS:.cpp=.o)
TARGET = .\Final_Build\CLI_Timer.exe

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o
