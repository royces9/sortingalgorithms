CC = gcc

bubblesort: bubblesort.c bubblesort.h shuffle.o
	$(CC) bubblesort.c shuffle.o -o bubblesort

quicksort: quicksort.c quicksort.h shuffle.o
	$(CC) quicksort.c shuffle.o -o quicksort

mergesort: mergesort.c mergesort.h shuffle.o
	$(CC) mergesort.c shuffle.o -o mergesort -lm

LSDradix: LSDradix.c LSDradix.h shuffle.o
	$(CC) LSDradix.c shuffle.o -o LSDradix -lm

selectionsort: selectionsort.c selectionsort.h shuffle.o
	$(CC) selectionsort.c shuffle.o -o selectionsort

shuffle.o: shuffle.c shuffle.h
	$(CC) -c shuffle.c
