#include <SDL2/SDL_image.h>

#include "sdl_compare.h"

int sdl_compare(void *a, void *b) {
	return ((SDL_Rect *)a)->h > ((SDL_Rect *)b)->h;
}
