#include <stdint.h>
#include <SDL2/SDL_image.h>

#include "sdl_radix_compare.h"

int sdl_radix_compare(void *a, void *b) {
	return *(uint64_t *)a & (uint64_t)((SDL_Rect *)b)->h;
}
