#
# Makefile for wxWidgets version of Hexdump.
#

# General Flags
###############
CXX=clang++
CXXFLAGS=-std=c++11 -c -O -emit-llvm -I$(BOOST_HOME) `wx-config --cppflags` -D__WXDEBUG__
LLVMLINK=llvm-link
LLVMLINKFLAGS=
LINKFLAGS=-L/usr/lib/i386-linux-gnu -L$(BOOST_HOME)/stage/lib -lpthread `wx-config --libs`

# Program Sources
#################
SOURCES=wxHexdumpMain.cpp wxHexdumpApp.cpp
OBJECTS=$(SOURCES:.cpp=.bc)
PROG=wxHexdump

# Implicit Rules
################
%.bc:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

%.o:	%.bc2
	llc -filetype=obj $< -o $@

%.bc2:	%.bc1
	opt -o $@ -globaldce $<

# Main Target
#############
all:	$(PROG)

# Global Link
#############

$(PROG):	$(PROG).o
	$(CXX) $< $(LINKFLAGS) -o $@

$(PROG).o:	$(PROG).bc2

$(PROG).bc2:	$(PROG).bc1

$(PROG).bc1:	$(OBJECTS)
	$(LLVMLINK) $(LLVMLINKFLAGS) -o $@ $(OBJECTS)

# File Dependencies
###################

wxHexdumpMain.bc:	wxHexdumpMain.cpp

wxHexdumpApp.bc:	wxHexdumpApp.cpp

# Additional Rules
##################
clean:
	rm -f *.bc *.bc1 *.bc2 *.o $(PROG) *.s *.ll *~
