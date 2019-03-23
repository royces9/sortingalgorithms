#include <stdint.h>
#include <SDL2/SDL_image.h>

#include "sdl_radix_compare.h"

int sdl_radix_compare(void *a, void *b) {
	return *(uint32_t *)a & (uint32_t)((SDL_Rect *)b)->h;
}
