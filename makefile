CC = gcc

bubblesort: bubblesort.c bubblesort.h shuffle.o
	$(CC) bubblesort.c shuffle.o -o bubblesort

quicksort: quicksort.c quicksort.h shuffle.o
	$(CC) quicksort.c shuffle.o -o quicksort -lm

quicksort2: quicksort2.c quicksort2.h shuffle.o
	$(CC) quicksort2.c shuffle.o -o quicksort2 -lm

mergesort: mergesort.c mergesort.h shuffle.o file.h
	$(CC) mergesort.c shuffle.o -o mergesort -lm

mergesort2: mergesort2.c mergesort2.h shuffle.o file.h
	$(CC) mergesort2.c shuffle.o -o mergesort2 -lm

LSDradix: LSDradix.c LSDradix.h shuffle.o
	$(CC) LSDradix.c shuffle.o -o LSDradix -lm

MSDradix: MSDradix.c MSDradix.h shuffle.o
	$(CC) MSDradix.c shuffle.o -o MSDradix -lm

selectionsort: selectionsort.c selectionsort.h shuffle.o
	$(CC) selectionsort.c shuffle.o -o selectionsort

insertionsort: insertionsort.c insertionsort.h shuffle.o
	$(CC) insertionsort.c shuffle.o -o insertionsort

heapsort: heapsort.c heapsort.h shuffle.o
	$(CC) heapsort.c shuffle.o -o heapsort

threadqs: threadqs.c threadqs.h shuffle.o
	$(CC) threadqs.c shuffle.o -o threadqs -lm

shuffle.o: shuffle.c shuffle.h
	$(CC) -c shuffle.c
