#include <SDL_image.h>

#include "copy.h"
#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;
extern SDL_Texture **tex;
extern SDL_Rect *rect;
extern struct rect_cont *cont;

void copy(char *src, char *dest, int size_e) {
	int word_loops = size_e / sizeof(int);
	int byte_loops =  size_e % sizeof(int);
 
	for(int i = 0; i < word_loops; ++i) {
		*(int *)dest = *(int *)src;

		dest += sizeof(int);
		src += sizeof(int);
	}

	for(int i = 0; i < byte_loops; ++i) {
		*dest = *src;

		++dest;
		++src;
	}

#ifdef DISP
        if(flag & 16)
		disp_cont(tex, cont, globalSize);
#endif //DISP
}
