#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "shuffle.h"

extern SDL_Window *win;
extern SDL_Renderer *ren;
extern SDL_Rect rect_bg;
extern SDL_Texture *bg;

void shuffle(int *array, int size) {
	//shuffle array
	for(int i = 0; i < (size - 1); i++) {
		int j = i + rand() / (RAND_MAX / (size - i) + 1);
		int temp = array[j];
		array[j] = array[i];
		array[i] = temp;
	}

}

int *shuffledArray(int size) {
	//seed rand();
	struct timeval t2;
	gettimeofday(&t2, NULL);
	srand((unsigned) t2.tv_usec);

	
	//make array and populate
	int *array = malloc(size * sizeof(*array));
	for(int i = 0; i < size; i++)
		array[i] = i;

	shuffle(array, size);

	return array;
}


void printArray(int *array, int size) {
	for(int i = 0; i < size; i++)
		printf("%d ", array[i]);

	printf("\n");
}


double timeDifference(struct timeval start, struct timeval end) {
	return ((double)end.tv_usec - (double)start.tv_usec)/1000000 + ((double)end.tv_sec - (double)start.tv_sec);
}


void check_array(int *array, int size) {
	for(int i = 1; i < size; ++i) {
		if(array[i] <  (array[i - 1])) {
			printf("Sorted incorrectly.\n");
			break;
		}
	}
}


void disp_cont(SDL_Texture **tex, struct rect_cont *cont, int size) {
	int width = cont->rect.w;
	SDL_RenderCopy(ren, bg, NULL, &rect_bg);

	for(int i = 0; i < size; ++i) {
		cont[i].rect.x = width * i;
		SDL_RenderCopy(ren, tex[i], NULL, &cont[i].rect);
	}

	SDL_RenderPresent(ren);
	SDL_RenderClear(ren);
	
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			exit(1);
		}
	}
}

void disp_cont2(SDL_Texture **tex, struct rect_cont *cont, int ai, int bi, int size) {
	int width = cont->rect.w;
	SDL_RenderCopy(ren, bg, NULL, &rect_bg);

	SDL_SetTextureColorMod(tex[ai], 0, 255, 0);
	SDL_SetTextureColorMod(tex[bi], 0, 255, 0);

	for(int i = 0; i < size; ++i) {
		cont[i].rect.x = width * i;
		SDL_RenderCopy(ren, tex[i], NULL, &cont[i].rect);
	}

	SDL_RenderPresent(ren);
	SDL_RenderClear(ren);

	SDL_SetTextureColorMod(tex[ai], 255, 255, 255);
	SDL_SetTextureColorMod(tex[bi], 255, 255, 255);

	
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			exit(1);
		}
	}
}

void change_colour(SDL_Texture **tex, struct rect_cont *cont, int ai, int bi, int size) {
	int width = cont->rect.w;
	SDL_RenderCopy(ren, bg, NULL, &rect_bg);

	SDL_SetTextureColorMod(tex[ai], 255, 0, 0);
	SDL_SetTextureColorMod(tex[bi], 255, 0, 0);

	for(int i = 0; i < size; ++i) {
		cont[i].rect.x = width * i;
		SDL_RenderCopy(ren, tex[i], NULL, &cont[i].rect);
	}

	SDL_RenderPresent(ren);
	SDL_RenderClear(ren);

	SDL_SetTextureColorMod(tex[ai], 255, 255, 255);
	SDL_SetTextureColorMod(tex[bi], 255, 255, 255);

	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			exit(1);
		}
	}
}
