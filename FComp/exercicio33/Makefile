# Simple Makefile to link the ROOT libraries to
# our C++ code...
#
# Author: R. Coelho

CC := g++
CCFLAGS := -std=c++14

ROOT_FLAGS := $(shell echo $$(root-config --cflags --libs) )
ROOT_FLAGS := $(shell echo $(ROOT_FLAGS) | sed 's/-std=c++11//;s/-stdlib=libc++//g' )

INCLUDE := ./
LD := $(CC)

#####################################################

SOURCES := $(shell ls . | grep cpp)
OBJECTS := $(SOURCES:.cpp=.o)

all: main

main: $(OBJECTS)
	$(LD) -o $@ $(OBJECTS) $(ROOT_FLAGS) -I $(INCLUDE)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $^ $(ROOT_FLAGS) -I $(INCLUDE)

clean:
	rm *.o *.exe

