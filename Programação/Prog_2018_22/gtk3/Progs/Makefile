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

OBJS		= 

EXEC		= 

FAUX		= Gtk3_CssAux

PROGS		= Gtk3_01_01 Gtk3_01_02 Gtk3_01_03 Gtk3_01_04\
			Gtk3_02_01 Gtk3_02_02 Gtk3_02_03 Gtk3_02_04 Gtk3_02_05\
			Gtk3_03_01 Gtk3_03_02 Gtk3_03_03 Gtk3_03_04 Gtk3_03_05 Gtk3_03_06\
			Gtk3_04_01 Gtk3_04_02\
			Gtk3_05_01 Gtk3_05_02 Gtk3_05_03 Gtk3_05_04 Gtk3_05_05\
			Gtk3_06_01 Gtk3_06_02 Gtk3_06_03 Gtk3_06_04\
			Gtk3_07_01 Gtk3_07_02 Gtk3_07_03 Gtk3_07_04\
			Gtk3_08_01 Gtk3_08_02 Gtk3_08_03\
			Gtk3_09_01 Gtk3_09_02 Gtk3_09_03 Gtk3_09_04 Gtk3_09_05 Gtk3_09_06 Gtk3_09_07 Gtk3_09_08\
			Gtk3_09_09 Gtk3_09_10 Gtk3_09_11 Gtk3_09_12 Gtk3_09_13 Gtk3_09_14 Gtk3_09_15

all: comp link

comp: 
	for fname in $(FAUX); do $(CC) $(CFLAGS) -c $$fname.c ; done
	for fname in $(PROGS); do $(CC) $(CFLAGS) -c $$fname.c ; done

link: 
	for fname in $(PROGS); do $(CC) $(LFLAGS) -o $$fname $$fname.o Gtk3_CssAux.o $(LIBS) ; done

clean:
	$(RM) -f *~ *.o $(PROGS)
