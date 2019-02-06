#include <SDL2/SDL_image.h>
int compare(void *a, void *b) {
	return ((SDL_Rect *)a)->h > ((SDL_Rect *)b)->h;
	//return *(int *) a > *(int *) b;
}
