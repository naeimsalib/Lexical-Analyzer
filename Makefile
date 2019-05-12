# C++ compiler
CXX = g++

# C++ compiler flags
CXXFLAGS = -g -Wall

# Creating a .o file
COMPILE = $(CXX) $(CXXFLAGS) -c

# Name of the executable; should match the contents of Runfile
EXE = main

# All object files
OBJS = main.o

$(EXE) : $(OBJS) # depends on all object files
	$(CXX) $^ -o $@

# An object file is dependent on the corresponding source file

%.o : %.cc
	$(COMPILE) -o $@ $<
