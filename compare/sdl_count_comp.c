#include <SDL2/SDL_image.h>

#include "shuffle.h"
#include "sdl_count_comp.h"

extern int compare_count;

int sdl_count_comp(void *a, void *b) {
	++compare_count;
	return ((struct rect_cont *)a)->val - ((struct rect_cont *)b)->val;
}
