CC = gcc
CFLAGS = -MMD -g -O3 -Wall -I. -I.. -Icompare/ -Idata_structures/
FLAGS = -MMD -Wall `sdl2-config --cflags` -I. -I.. -Icompare/
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lm -pthread

MAINC = $(wildcard *.c)
MAINO = $(MAINC:.c=.o)
MAINH = $(MAINC:.c=.h)

OBJF = obj
SORTF = sort
DATAF = data_structures

SORTC = $(subst $(SORTF)/,,$(wildcard $(SORTF)/*.c))
OBJS = $(SORTC:.c=.o)
EXE =  $(SORTC:.c=)

COMPC = $(wildcard compare/*.c)
COMPH = $(COMPC:.c=.h)
COMPO = $(COMPC:.c=.o)

DATAC = $(wildcard $(DATAF)/*.c)
DATAH = $(DATAC:.c=.h)
DATAO = $(DATAC:.c=.o)

all: $(EXE)

$(EXE): $(OBJS) $(MAINO) $(COMPO) $(DATAO)
	$(CC) $(OBJF)/$(@F).o $(DATAO) $(COMPO) $(MAINO) -o $@ $(LDFLAGS)

$(OBJS): $(MAINC) $(MAINH)
	$(CC) $(CFLAGS) -c $(SORTF)/$*.c -o $(OBJF)/$@

$(DATAO): $(DATAC) $(DATAH)
	$(CC) $(CFLAGS) -c $*.c -o $@

$(COMPO): $(COMPC) $(COMPH)
	$(CC) $(FLAGS) -c $*.c -o $@

$(MAINO): $(MAINC) $(MAINH)
	$(CC) $(FLAGS) -c $ $*.c -o $(@F)

.PHONY: clean
clean:
	del *.d
	del *.o
	del */*.o
	del */*.d
	del *~
	del */*~
	del vgcore.*
	del $(patsubst $(SORTF)/%, %, $(EXE))

-include $($(OBJF)/*:.o=.d)
-include $(DATAC:.c=.d)
-include $(SORTC:.c=.d)
-include $(MAINC:.c=.d)
