CC = gcc
FLAGS = -g -MMD -Wall `sdl2-config --cflags` -I. -I..
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lm -pthread

MAINC = $(wildcard *.c)
MAINO = $(MAINC:.c=.o)
MAINH = $(MAINC:.c=.h)

OBJF = obj
SORTF = sort

SORTC = $(subst $(SORTF)/,,$(wildcard $(SORTF)/*.c))
OBJS = $(OBJF)/$(SORTC:.c=.o)
EXE =  $(SORTC:.c=)

$(EXE): $(MAINO) $(OBJS)
	$(CC) $(MAINO) $(OBJF)/$(@F).o -o $@ $(LDFLAGS)

$(OBJS): $(MAINC)
	$(CC) $(FLAGS) -c $< -o $(SORTF)/$@

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
