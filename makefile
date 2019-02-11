CC = gcc
FLAGS = -g -MMD -Wall `sdl2-config --cflags` -I. -I..
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lm -pthread

MAINC = $(wildcard *.c)
MAINO = $(MAINC:.c=.o)
MAINH = $(MAINC:.c=.h)

OBJF = obj
SORTF = sort

SORTC = $(subst $(SORTF)/,,$(wildcard $(SORTF)/*.c))
OBJS = $(SORTC:.c=.o)
EXE =  $(SORTC:.c=)


all: $(EXE)

$(EXE): $(OBJS) $(MAINO)
	$(CC) $(OBJF)/$(@F).o $(MAINO) -o $@ $(LDFLAGS)

$(OBJS): $(MAINC)
	$(CC) $(FLAGS) -c $(SORTF)/$*.c -o $(OBJF)/$@

$(MAINO): $(MAINC) $(MAINH)
	$(CC) $(FLAGS) -c $*.c -o $(@F)

.PHONY: clean
clean:
	del *.d
	del *.o
	del obj/*.o
	del $(patsubst $(SORTF)/%, %, $(EXE))


-include $(SORTC:.c=d)
-include $(MAINC:.c=.d);
