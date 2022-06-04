CC := g++
CCFLAGS := -std=c++14
INCLUDE := ./


ROOT_FLAGS := $(shell echo $$(root-config --cflags --libs) )
#ROOT_FLAGS := $(shell echo $(ROOT_FLAGS) | sed 's/-std=c++11//;s/-stdlib=libc++//g' )
#--- VPATH contains the search path for the src files !
VPATH = ./

#INCLUDE := ../src:../serie_problemas

#INCLUDE := ../src:../serie_problemas
LD := $(CC)

#####################################################
# Include the source files
SOURCES := $(wildcard ./*.cpp)

## SOURCES := $(shell ls . | grep cpp)
OBJECTS := $(notdir $(SOURCES:.cpp=.o))

all: ./main.exe

	#debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: ./main.exe

./main.exe: $(OBJECTS)
	@echo $(OBJECTS)
	$(LD) -o $@ $^ $(ROOT_FLAGS) -I $(INCLUDE)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $^ $(ROOT_FLAGS) -I $(INCLUDE)

run:
	./main.exe

clean:
	rm *.o ../*.exe *.eps

valgrind:
	valgrind --leak-check=yes ../bin/main.exe
