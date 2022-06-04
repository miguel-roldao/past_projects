DB_FLAGS	= -Wall -g -ggdb 
#DB_FLAGS	= -O3

GTK_CMP		= `pkg-config --cflags --libs gtk+-3.0`
GTK_LIB		= `pkg-config --libs gtk+-3.0`

INCLUDE		= 

LIBS		=  $(GTK_LIB) -lm #-lgtkhtml-4.0

LOPTS		=

CFLAGS		= $(DB_FLAGS) $(GTK_CMP) #-I/usr/include/libgtkhtml-4.0
LFLAGS		= $(DB_FLAGS)

CC		= gcc
CP		= cp
RM		= rm
LS		= ls

OBJS		= Gtk3_CssAux.o

EXEC		= 

FAUX		= Gtk3_CssAux

PROGS		= icomp28


all: comp link

comp: 
	for fname in $(FAUX); do $(CC) $(CFLAGS) -c $$fname.c ; done
	for fname in $(PROGS); do $(CC) $(CFLAGS) -c $$fname.c ; done

link: 
	for fname in $(PROGS); do $(CC) $(LFLAGS) -o $$fname $$fname.o Gtk3_CssAux.o $(LIBS) ; done

clean:
	$(RM) -f *~ *.o $(PROGS)
