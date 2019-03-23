#ifndef SHUFFLE
#define SHUFFLE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <sys/time.h>

struct rect_cont {
	SDL_Rect rect;
	int val;
};

void shuffle(int *array, int size);
int *shuffledArray(int size);
void printArray(int *array, int size);
void copyArray(void *src, void *dest, int size_a, int size_e);
double timeDifference(struct timeval start, struct timeval end);
void check_array(int *array, int size);
void disp_array(SDL_Texture **tex, SDL_Rect *rect, int size);
void disp_cont(SDL_Texture **tex, struct rect_cont *cont, int size);

#endif //SHUFFLE
