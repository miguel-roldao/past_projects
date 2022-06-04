# Simple Makefile with variables (compiler+flags+include)
# and explicit paths on targets + dependencies
#
#
# Author: R. Coelho
# Modified: A. Barbosa & M. Roldão

CC := g++-7
CCFLAGS := -std=c++14
INCLUDE := ../src

#--- VPATH contains the search path for the src files !
VPATH = ../src:../serie_problemas

#--- Now find & list all cpp files on directories
SOURCES := $(wildcard ../src/*.cpp ../serie_problemas/*.cpp)

#--- But object files should not have the full path of
#--- the SOURCES when we replace the .cpp by .o !
OBJECTS := $(notdir $(SOURCES:.cpp=.o))


#####################################################

all: ../bin/turma_teste

../bin/turma_teste: $(OBJECTS)
	@echo $(OBJECTS)
	$(CC) -o $@ $^ -g -I $(INCLUDE)

#--- Now every .cpp file can easily be found from VPATH !
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $^ -I $(INCLUDE)

clean:
	rm *.o ../bin/turma_teste
