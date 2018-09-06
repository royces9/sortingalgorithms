CC = gcc
FLAGS = -Wall -I.


bubblesort: sort/bubblesort.o main.o shuffle.o
	$(CC) $^ -o bubblesort

shuffle.o: shuffle.c shuffle.h
	$(CC) $(FLAGS) -c shuffle.c -o shuffle.o

main.o: main.c shuffle.c
	$(CC) $(FLAGS) -c main.c -o main.o

sort/%.o: sort/%.c shuffle.c
	$(CC) $(FLAGS) -c $< -o $@


.PHONY: clean
clean:
	del *.o
	del sort/*.o
