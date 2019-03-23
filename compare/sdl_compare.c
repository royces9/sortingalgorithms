#include <SDL2/SDL_image.h>
#include "shuffle.h"
#include "sdl_compare.h"

int sdl_compare(void *a, void *b) {
	return ((struct rect_cont *)a)->rect.val > ((struct rect_cont *)b)->rect.val;
}
