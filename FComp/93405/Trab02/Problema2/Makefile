CC := g++
CCFLAGS := -std=c++14
INCLUDE := src


ROOT_FLAGS := $(shell echo $$(root-config --cflags --libs) )
#ROOT_FLAGS := $(shell echo $(ROOT_FLAGS) | sed 's/-std=c++11//;s/-stdlib=libc++//g' )
#--- VPATH contains the search path for the src files !
VPATH = src: serie_problemas:

#INCLUDE := ../src:../serie_problemas

#INCLUDE := ../src:../serie_problemas
LD := $(CC)

#####################################################
# Include the source files
SOURCES := $(wildcard src/*.cpp serie_problemas/*.cpp )

## SOURCES := $(shell ls . | grep cpp)
OBJECTS := $(addprefix bin/, $(notdir $(SOURCES:.cpp=.o)))

all: bin/molecule_bond.exe

	#debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: bin/molecule_bond.exe

bin/molecule_bond.exe: $(OBJECTS)
	@echo $(OBJECTS)
	$(CC) -o $@ $^ -I $(INCLUDE) $(ROOT_FLAGS)

bin/%.o: %.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@ -I $(INCLUDE) $(ROOT_FLAGS)

run:
	./bin/molecule_bond.exe

clean:
	rm bin/*.o bin/*.exe *.o

valgrind:
	valgrind --leak-check=yes bin/molecule_bond.exe
