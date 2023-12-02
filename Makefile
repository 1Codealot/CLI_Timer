CPPC = g++

Main_Path  = ./src/main.cpp
Build_Dir  = ./Final_Build/
Build_Path = $(Build_Dir)CLI_Timer
STD        ?= 23

CPPFLAGS = -O3 -Wall -Wextra -Wpedantic

ifdef STD
    CPPFLAGS += -std=c++$(STD)
endif

CPPFLAGS += -std=c++$(STD)

all:
	mkdir -p $(Build_Dir)
		$(TARGET): $(TARGET).cpp 
			$(CPPC) $(CPPFLAGS) -o $(Build_Path) $(Main_Path)

cross:
	mkdir -p $(Build_Dir)
		$(TARGET): $(TARGET).cpp 
			$(CPPC) $(CPPFLAGS) -o $(Build_Path) $(Main_Path)
				x86_64-w64-mingw32-g++ $(CPPFLAGS) -o $(Build_Path)_Windows.exe $(Main_Path) -static-libgcc -static-libstdc++ 
				

