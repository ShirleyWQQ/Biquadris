CXX=g++
CXXFLAGS=-std=c++14 -Wall -O -g -MMD # use -MMD to generate dependencies // Nata: no -Werror=vla because we have new
SOURCES=$(wildcard *.cc)   # list of all .cc files in the current directory
OBJECTS=${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=biquadris

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC): $(OBJECTS)
        $(CXX) $(CXXFLAGS) $(OBJECTS) -lX11 -o $(EXEC)

%.o: %.cc
        $(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
        rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
