#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "int_compare.h"
#include "radix_compare.h"
#include "sdl_compare.h"
#include "sdl_radix_compare.h"
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

SDL_Rect rect_bg = {0, 0, 1920, 1080};
SDL_Texture *bg;
char *img;

void *comp_array[] = {&int_compare, &radix_compare,
		      &sdl_compare, &sdl_radix_compare};
void print_flags();

int main(int argc, char **argv) {

	if(argc == 1)
		print_flags();

	int size = 10;
	int *extra = NULL;
	struct timeval start;
	struct timeval end;

	int repeat = 1;

	int radix_flag = 0;

	if(strstr(argv[0], "radix"))
		radix_flag = 1;

	int width = rect_bg.w;
	int height = rect_bg.h;


 start:;
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
				array = shuffledArray(size);
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

	void *comp = comp_array[radix_flag];

	void *sort_obj = array;
	int size_obj = sizeof(int);

	if(flag & 16) {
		float rect_width = ((float)width / size);
		if(repeat) {
			int w_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
			int r_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
			SDL_Init(SDL_INIT_VIDEO);
			win = SDL_CreateWindow("Sorting", 0, 0, width, height, w_flags);
			ren = SDL_CreateRenderer(win, -1, r_flags);
			tex = malloc(size * sizeof(*tex));
			rect = malloc(size * sizeof(*rect));

			SDL_RenderSetLogicalSize(ren, width, height);
			//bg = IMG_LoadTexture(ren, img);
			repeat = 0;
		}

		for(int i = 0; i < size; ++i) {
			tex[i] = IMG_LoadTexture(ren, "pink.png");

			rect[i].w = rect_width;
			rect[i].x = rect_width * i;

			rect[i].h = (height * (array[i] + 1)) / size;
			rect[i].y = height - rect[i].h;
		}

		disp_array(tex, rect, size);

		comp = comp_array[radix_flag + 2];

		sort_obj = rect;
		size_obj = sizeof(*rect);
	}

	if(flag & 1)
		printArray(array, size);

	gettimeofday(&start, NULL);
	sort(sort_obj, size, size_obj, comp, extra);
	gettimeofday(&end, NULL);

	if(flag & 1)
		printArray(array, size);

	if(flag & 2)
		printf("Time elapsed: %lf s\n", timeDifference(start, end));

	if(flag & 4)
		check_array(array, size);

	free(array);
	free(extra);

	if(flag & 16) {
		SDL_Delay(500);
		goto start;
	}

	return 0;
}


void print_flags(void) {
	puts("./<alg name> -f <#> -s <#> -e <#> -[rad]");
	puts("");
		
	puts("-f: flags");
	puts("Add values together to use multiple");
	puts("1: print array to stdout");
	puts("2: Time sort");
	puts("4: Verify correctly sorted");
	puts("8: Print to stdout when swap/copy is called");
	puts("16: Use SDL to visualize");
	puts("");

	puts("-s: size of array");
	puts("");
		
	puts("-e: extra flags");
	puts("number of threads for threaded sorts");
	puts("");

	puts("-r: reverse sorted array as input");
	puts("");

	puts("-a: sorted array as input");
	puts("");

	puts("-d: all elements of array are 1");
	puts("");
}
