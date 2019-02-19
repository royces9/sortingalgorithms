CC = gcc
SORTFLAGS = -g -MMD -O3 -Wall -I. -I.. -Icompare/
FLAGS = -g -MMD -O3 -Wall `sdl2-config --cflags` -I. -I.. -Icompare/
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lm -pthread

MAINC = $(wildcard *.c)
MAINO = $(MAINC:.c=.o)
MAINH = $(MAINC:.c=.h)

OBJF = obj
SORTF = sort

SORTC = $(subst $(SORTF)/,,$(wildcard $(SORTF)/*.c))
OBJS = $(SORTC:.c=.o)
EXE =  $(SORTC:.c=)

COMPC = $(wildcard compare/*.c)
COMPH = $(COMPC:.c=.h)
COMPO = $(COMPC:.c=.o)

all: $(EXE)

$(EXE): $(OBJS) $(MAINO) $(COMPO)
	$(CC) $(OBJF)/$(@F).o $(COMPO) $(MAINO) -o $@ $(LDFLAGS)

$(OBJS): $(MAINC)
	$(CC) $(SORTFLAGS) -c $(SORTF)/$*.c -o $(OBJF)/$@

$(COMPO): $(COMPC) $(COMPH)
	$(CC) $(FLAGS) -c $*.c -o $@

$(MAINO): $(MAINC) $(MAINH)
	$(CC) $(FLAGS) -c $ $*.c -o $(@F)

.PHONY: clean
clean:
	del *.d
	del *.o
	del obj/*.o
	del compare/*.o
	del vgcore.*
	del $(patsubst $(SORTF)/%, %, $(EXE))


-include $(SORTC:.c=d)
-include $(MAINC:.c=.d);
