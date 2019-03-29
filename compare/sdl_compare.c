#include <SDL2/SDL_image.h>
#include "shuffle.h"
#include "sdl_compare.h"

extern SDL_Renderer *ren;
extern SDL_Texture **tex;
extern struct rect_cont *cont;
extern int globalSize;

int sdl_compare(void *a, void *b) {
	struct rect_cont *ar = (struct rect_cont *) a;
	struct rect_cont *br = (struct rect_cont *) b;

	int ai = (ar - cont);
	int bi = (br - cont);
	change_colour(tex, cont, ai, bi, globalSize);
	return ar->val > br->val;
}
