CC = gcc
FLAGS = -g -Wall -I.
LDFLAGS = -lm -pthread

SORTC = $(wildcard sort/*.c)
OBJS = $(SORTC:.c=.o)
EXE =  $(SORTC:.c=)


all: $(EXE)

$(EXE) : $(OBJS) main.o shuffle.o
	$(CC) $@.o main.o shuffle.o -o ../$@ $(LDFLAGS)


shuffle.o: shuffle.c shuffle.h
	$(CC) $(FLAGS) -c shuffle.c -o shuffle.o

main.o: main.c shuffle.h
	$(CC) $(FLAGS) -c main.c -o main.o

sort/%.o: sort/%.c shuffle.c
	$(CC) $(FLAGS) -c $< -o $@


.PHONY: clean
clean:
	del *.o
	del sort/*.o
