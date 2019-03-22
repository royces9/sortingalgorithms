#include <SDL_image.h>

#include "copy.h"
#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;
extern SDL_Texture **tex;
extern SDL_Rect *rect;


void copy(void *src, void *dest, int size_e) {
	int word_loops = size_e / sizeof(int);
	int byte_loops =  size_e % sizeof(int);
 
	for(int i = 0; i < word_loops; ++i) {
		*(int *)dest = *(int *)src;

		dest += sizeof(int);
		src += sizeof(int);
	}

	for(int i = 0; i < byte_loops; ++i) {
		*(char *)dest = *(char *)src;

		dest += sizeof(char);
		src += sizeof(char);
	}

        if(flag & 16)
		disp_array(tex, rect, globalSize);
}
