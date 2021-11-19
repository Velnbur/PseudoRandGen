##
# Lab1
#
# @file
# @version 0.1
CXX=g++
DEBUG=0
CXXFLAGS=-Wall -g -O2 -I./lab/include -D DEBUG=$(DEBUG)
PROJECT_NAME=lab1
SRCMODULES=gist.cpp rand.cpp
OBJMODULES=$(SRCMODULES:.cpp=.o)

all: dirs build

dirs:
	mkdir -p lab/build lab/bin

%.o: lab/src/%.cpp lab/include/%.h
	$(CXX) $(CXXFLAGS) -c  $< -o ./lab/build/$@

build: $(OBJMODULES)
	$(CXX) $(CXXFLAGS) lab/main.cpp $(addprefix ./lab/build/, $^) -o ./lab/bin/$(PROJECT_NAME)

clean:
	rm -f *.o $(PROJECT_NAME)
