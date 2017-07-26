SOLN=STLa # change "a" to one of [a-f] depending upon directory
CXX=g++-5
CXXFLAGS= -O -Wall -std=c++14  -MMD -D${SOLN}
SOURCES = $(wildcard Menu*.cc Iterator*.cc *Iterator.cc)   # list of all .cc files in the current directory
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=${SOLN}

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f *.o $(EXEC) $(OBJECTS) $(DEPENDS)

-include ${DEPENDS}

