CPPC = g++

Main_Path    = ./src/main.cpp
Build_Dir    = ./Final_Build/
Final_Name   = CLI_Timer
Build_Path   = $(Build_Dir)$(Final_Name)
Install_Path = /bin/$(Final_Name)

STD         ?= 23

CPPFLAGS = -Wall -Wextra -Wpedantic -O3

all:
	mkdir -p $(Build_Dir)
		$(TARGET): $(TARGET).cpp 
			$(CPPC) $(CPPFLAGS) -std=c++$(STD) -o $(Build_Path) $(Main_Path)

# This was for cross compiling to windows however, the multi threading is impossible.

# cross:
# 	mkdir -p $(Build_Dir)
# 		$(TARGET): $(TARGET).cpp 
# 			$(CPPC) $(CPPFLAGS) -o $(Build_Path) $(Main_Path)
# 				x86_64-w64-mingw32-g++ $(CPPFLAGS) -o $(Build_Path)_Windows.exe $(Main_Path) -static-libgcc -static-libstdc++

debug:
	mkdir -p $(Build_Dir)
		$(TARGET): $(TARGET).cpp 
			$(CPPC) $(CPPFLAGS) -std=c++$(STD) -O0 -ggdb -o $(Build_Path) $(Main_Path)

install:
	cp $(Build_Path) $(Install_Path)

uninstall:
	rm $(Install_Path)
				

