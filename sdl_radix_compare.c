#include <SDL2/SDL_image.h>

#include "sdl_radix_compare.h"

int sdl_radix_compare(void *a, void *b) {
	return *(unsigned int *)a & ((SDL_Rect *)b)->h;
}
