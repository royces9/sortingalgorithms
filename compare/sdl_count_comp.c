#include <SDL2/SDL_image.h>

#include "sdl_count_comp.h"

extern int compare_count;

int sdl_count_comp(void *a, void *b) {
	++compare_count;
	return ((SDL_Rect *)a)->h > ((SDL_Rect *)b)->h;
}
