CC = gcc

bubblesort: bubblesort.c bubblesort.h shuffle.o
	$(CC) bubblesort.c shuffle.o -o bubblesort

quicksort: quicksort.c quicksort.h shuffle.o
	$(CC) quicksort.c shuffle.o -o quicksort -lm

quicksort2: quicksort2.c quicksort2.h shuffle.o
	$(CC) quicksort2.c shuffle.o -o quicksort2 -lm

mergesort: mergesort.c mergesort.h shuffle.o
	$(CC) mergesort.c shuffle.o -o mergesort -lm

LSDradix: LSDradix.c LSDradix.h shuffle.o
	$(CC) LSDradix.c shuffle.o -o LSDradix -lm

MSDradix: MSDradix.c MSDradix.h shuffle.o
	$(CC) MSDradix.c shuffle.o -o MSDradix -lm

selectionsort: selectionsort.c selectionsort.h shuffle.o
	$(CC) selectionsort.c shuffle.o -o selectionsort

insertionsort: insertionsort.c insertionsort.h shuffle.o
	$(CC) insertionsort.c shuffle.o -o insertionsort

shuffle.o: shuffle.c shuffle.h
	$(CC) -c shuffle.c
