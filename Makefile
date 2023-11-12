CPPC = g++

CPPFLAGS = -O3 -Wall -Wextra -Wpedantic -std=c++23

Main_Path  = ./src/main.cpp
Build_Dir  = ./Final_Build/
Build_Path = $(Build_Dir)CLI_Timer

all:
	mkdir -p $(Build_Dir)
		$(TARGET): $(TARGET).cpp 
			$(CPPC) $(CPPFLAGS) -o $(Build_Path) $(Main_Path)

