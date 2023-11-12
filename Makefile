CPPC = g++

CPPFLAGS = -O3 -Wall -Wextra -Wpedantic

Main_Path  = ./src/main.cpp
Build_Dir  = ./Final_Build/
Build_Path = $(Build_Dir)main

all:
	mkdir -p $(Build_Dir)
		$(TARGET): $(TARGET).cpp 
			$(CPPC) $(CPPFLAGS) -o $(Build_Path) $(Main_Path)

