#include <SDL_image.h>

#include "shuffle.h"
#include "swap.h"

extern int *globalArray;
extern int globalSize;
extern int flag;
extern SDL_Texture **tex;
extern SDL_Rect *rect;

void swap(char *a, char *b, int size_e) {
	int word_loops = size_e / sizeof(int);
	int byte_loops = size_e % sizeof(int);

	for(int i = 0; i < word_loops; ++i) {
		int i_temp = *(int *)a;
		*(int *)a = *(int *)b;
		*(int *)b = i_temp;

		a += sizeof(int);
		b += sizeof(int);
	}

	for(int i = 0; i < byte_loops; ++i) {
		char c_temp = *a;
		*a = *b;
		*b = c_temp;

		++a;
		++b;
		
		/*
		char c_temp  = *(char *)a;
		*(char *)a = *(char *)b;
		*(char *)b = c_temp;

		a += sizeof(char);
		b += sizeof(char);
		*/
	}

	if(flag & 8)
		printArray(globalArray, globalSize);

	if(flag & 16)
		disp_array(tex, rect, globalSize);
}
