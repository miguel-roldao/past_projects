
CC := g++
CCFLAGS := -std=c++14
INCLUDE := ../src


ROOT_FLAGS := $(shell echo $$(root-config --cflags --libs) )
#ROOT_FLAGS := $(shell echo $(ROOT_FLAGS) | sed 's/-std=c++11//;s/-stdlib=libc++//g' )
#--- VPATH contains the search path for the src files !
VPATH = ../src: ../serie_problemas:

#INCLUDE := ../src:../serie_problemas
LD := $(CC)

#####################################################
# Include the source files
SOURCES := $(wildcard ../src/*.cpp ../serie_problemas/*.cpp)

## SOURCES := $(shell ls . | grep cpp)
OBJECTS := $(notdir $(SOURCES:.cpp=.o))

all: ../bin/main.exe

	#debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: ../bin/main.exe

../bin/main.exe: $(OBJECTS)
	@echo $(OBJECTS)
	$(LD) -o $@ $^ $(ROOT_FLAGS) -I $(INCLUDE)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $^ $(ROOT_FLAGS) -I $(INCLUDE)

run:
	./../bin/main.exe

clean:
	rm *.o ../bin/*.exe

valgrind:
	valgrind --leak-check=yes ../bin/main.exe
