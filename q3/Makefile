CXX=g++-5
CXXFLAGS= -O -Wall -std=c++14  -MMD
SOURCES = $(wildcard *.cc)   # list of all .cc files in the current directory
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
#EXEC=sampleHangman
EXEC=hangman

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)
	strip $(EXEC)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f *.o $(EXEC) $(OBJECTS) $(DEPENDS)

-include ${DEPENDS}

