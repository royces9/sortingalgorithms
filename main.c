#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "shuffle.h"

/*
 * 1: print array
 * 2: print time
 * 4: check sorted
 * 8: print swap/copy
 * 16: disp swap/copy in SDL
 */

void sort(void *, int, int, int (*)(void *, void *), void *);

int *globalArray;
int globalSize;
int flag;

SDL_Window *win;
SDL_Renderer *ren;
SDL_Texture **tex;
SDL_Rect *rect;

int compare(void *a, void *b);

int main(int argc, char **argv) {
	int size = 10;
	int *extra = NULL;
	struct timeval start;
	struct timeval end;
  
	int *array = shuffledArray(size);

	if(argc > 1) {
		for(int i = 1; i < argc; i += 2) {
			switch(*(argv[i] + 1)) {
			case 'f':
				flag = atoi(argv[i + 1]);
				break;
				
			case 's':
				free(array);
				size = atoi(argv[i + 1]);
				array  = shuffledArray(size);
				break;

			case 'e':
				extra = malloc(sizeof(*extra));
				*extra = atoi(argv[i + 1]);
				break;

			case 'r':
				for(int k = size - 1, j = 0; k >= 0; --k, ++j)
					array[k] = j;
				
				--i;
				break;

			case 'a':
				for(int k = 0; k < size; ++k)
					array[k] = k;

				--i;
				break;

			case 'd':
				for(int k = 0; k < size; ++k)
					array[k] = 1;

				--i;
				break;

			default:
				break;
			}
		}
	} else {
		flag = 7;
	}

	globalArray = array;
	globalSize = size;


	if(flag & 16) {
		SDL_Init(SDL_INIT_VIDEO);
		int width = 1280;
		int height = 720;
		int w_flags = SDL_WINDOW_SHOWN;

		int r_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

		win = SDL_CreateWindow("Sorting", 0, 0, width, height, w_flags);
		ren = SDL_CreateRenderer(win, -1, r_flags);
		tex = malloc(size * sizeof(*tex));
		rect = malloc(size * sizeof(*rect));

		float rect_width = ((float)width / size);
		for(int i = 0; i < size; ++i) {
			tex[i] = IMG_LoadTexture(ren, "pink.png");

			rect[i].w = rect_width;

			rect[i].x = rect_width * i;

			rect[i].h = (height * (array[i] + 1)) / size;
			rect[i].y = height - rect[i].h;
		}
	}

	if(flag & 1)
		printArray(array, size);

	if(flag & 16)
		disp_array(tex, rect, size);

	gettimeofday(&start, NULL);
	sort(rect, size, sizeof(*rect), &compare, extra);
	//sort(array, size, sizeof(*array), &compare, extra);
	gettimeofday(&end, NULL);

	if(flag & 16)
		disp_array(tex, rect, size);

	if(flag & 1)
		printArray(array, size);

	if(flag & 2)
		printf("Time elapsed: %lf s\n", timeDifference(start, end));

	if(flag & 4)
		check_array(array, size);


	free(array);
	free(extra);
	return 0;
}
