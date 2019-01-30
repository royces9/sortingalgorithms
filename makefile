CC = gcc
FLAGS = -g -Wall -I. -O2
LDFLAGS = -lm -pthread

SORTC = $(wildcard sort/*.c)
OBJS = $(SORTC:.c=.o)
EXE =  $(SORTC:.c=)

OBJF = obj
SORTF = sort

all: $(EXE)

$(EXE) : $(OBJS) main.o shuffle.o
	$(CC) $(OBJF)/$(@F).o main.o shuffle.o -o ../$@ $(LDFLAGS)

shuffle.o: shuffle.c shuffle.h
	$(CC) $(FLAGS) -c shuffle.c -o shuffle.o

main.o: main.c shuffle.h
	$(CC) $(FLAGS) -c main.c -o main.o

$(SORTF)/%.o: $(SORTF)/%.c shuffle.c
	$(CC) $(FLAGS) -c $< -o $(OBJF)/$*.o


.PHONY: clean
clean:
	del *.o
	del obj/*.o
	del $(patsubst $(SORTF)/%, %, $(EXE))
