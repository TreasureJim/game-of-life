IDIR=./include

CC=gcc
LIBS=-lm -lSDL2 -lSDL2_ttf
CFLAGS=-I$(IDIR) $(LIBS) -g

ODIR=obj
LDIR =../lib

_DEPS = window.h macros.h game.h input_handler.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = gol.o window.o game.o input_handler.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gol: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o gol *~ core $(INCDIR)/*~ 
