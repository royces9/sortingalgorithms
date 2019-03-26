#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "int_compare.h"
#include "radix_compare.h"
#include "sdl_compare.h"
#include "sdl_radix_compare.h"
#include "int_count_comp.h"
#include "sdl_count_comp.h"

#include "shuffle.h"

/*
 * 1: print array
 * 2: print time
 * 4: check sorted
 * 8: print swap/copy
 * 16: disp swap/copy in SDL
 * 32: print #of calls to swap and copy
 */

void sort(void *, int, int, int (*)(void *, void *), void *);

int *globalArray;
int globalSize;
int flag;

SDL_Window *win;
SDL_Renderer *ren;
SDL_Texture **tex;
SDL_Rect *rect;

SDL_Rect rect_bg;
SDL_Texture *bg;
char *img;

int (*comp_array[])(void *, void *) = {&int_compare, &radix_compare,
		      &sdl_compare, &sdl_radix_compare,
		      &int_count_comp, &radix_compare,
		      &sdl_count_comp, &sdl_radix_compare
};

struct rect_cont *cont;
	
void print_flags();
int *make_array(int argc, char **argv, int *size, int **extra, int *flag, unsigned int *type);
void assign_rect(SDL_Rect *rect, int *array, int size);
void assign_cont(struct rect_cont *cont, int *array, int size);

int compare_count;

int main(int argc, char **argv) {
	if(argc == 1)
		print_flags();

	unsigned int type = 0;

	int size = 10;
	int *extra = NULL;
	struct timeval start;
	struct timeval end;

	int compare_index = 0;

	if(strstr(argv[0], "radix"))
		compare_index += 1;

	rect_bg.w = 2560;
	rect_bg.h = 1440;

	int *array = make_array(argc, argv, &size, &extra, &flag, &type);

	globalArray = array;
	globalSize = size;

	if(flag & 32)
		compare_index += 4;

	int (*comp)(void *, void *) = comp_array[compare_index];

	void *sort_obj = array;
	int size_obj = sizeof(*array);

	if(flag & 16) {
		unsigned int w_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
		unsigned int r_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
		SDL_Init(SDL_INIT_VIDEO);
		win = SDL_CreateWindow("Sorting", 0, 0, rect_bg.w, rect_bg.h, w_flags);
		ren = SDL_CreateRenderer(win, -1, r_flags);
		tex = malloc(size * sizeof(*tex));
		//rect = malloc(size * sizeof(*rect));
		cont = malloc(size * sizeof(*cont));

		SDL_RenderSetLogicalSize(ren, rect_bg.w, rect_bg.h);

		if(img)
			bg = IMG_LoadTexture(ren, img);


		assign_cont(cont, array, size);
		//assign_rect(rect, array, size);

		for(int i = 0; i < size; ++i)
			tex[i] = IMG_LoadTexture(ren, "pink.png");

		//disp_array(tex, rect, size);
		disp_cont(tex, cont, size);

		comp = comp_array[compare_index + 2];

		/*
		sort_obj = rect;
		size_obj = sizeof(*rect);
		*/
		sort_obj = cont;
		size_obj = sizeof(*cont);
	}

	do {
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

		if(flag & 16) {
			SDL_Delay(500);
			free(array);
			array = make_array(argc, argv, &size, &extra, &flag, &type);
			assign_cont(cont, array, size);
			//assign_rect(rect, array, size);
		}

		if(flag & 32)
			printf("%d\n", compare_count);

	} while(flag & 16);

	free(array);
	free(extra);

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
	puts("32: Count number of comparisons");
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


int *make_array(int argc, char **argv, int *size, int **extra, int *flag, unsigned int *type) {
	if(argc > 1) {
		for(int i = 1; i < argc; i += 2) {
			switch(*(argv[i] + 1)) {
			case 'f':
				*flag = atoi(argv[i + 1]);
				break;
				
			case 's':
				*size = atoi(argv[i + 1]);
				break;

			case 'e':
				*extra = malloc(sizeof(*extra));
				**extra = atoi(argv[i + 1]);
				break;

			case 'r':
				*type = 1;
				--i;
				break;

			case 'a':
				*type = 2;
				--i;
				break;

			case 'd':;
				*type = 4;
				--i;
				break;
 
			default:
				break;
			}
		}
	} else {
		*flag = 7;
	}

	int *array = NULL;
	if(!*type) {
		array = shuffledArray(*size);

	} else if(*type == 1) {
		array = malloc(*size * sizeof(*array));

		for(int k = *size - 1, j = 0; k >= 0; --k, ++j)
			array[k] = j;

	} else if(*type == 2) {
		array = malloc(*size * sizeof(*array));

		for(int k = 0; k < *size; ++k)
			array[k] = k;

	} else if(*type == 4) {
		int max_val = 10;
		int step = *size / max_val;

		for(int ind = 0, value = 0; value < max_val; ++value) {
			for(int j = 0; j < step; ++j, ++ind) {
				array[ind] = value;
			}
		}

		int diff = *size - step * max_val;

		for(int l = 1; l <= diff; --l) {
			array[*size - l] = max_val;
		}

		shuffle(array, *size);

	}

	return array;
}


void assign_cont(struct rect_cont *cont, int *array, int size ) {
	for(int i = 0; i < size; ++i) {
		cont[i].rect.w = rect_bg.w / size;
		cont[i].rect.x = rect_bg.w * i;

		cont[i].rect.h = (rect_bg.h * (array[i] + 1)) / size;
		cont[i].rect.y = rect_bg.h - cont[i].rect.h;

		cont[i].val = array[i];
	}

}

void assign_rect(SDL_Rect *rect, int *array, int size) {
	for(int i = 0; i < size; ++i) {
		rect[i].w = rect_bg.w / size;
		rect[i].x = rect_bg.w * i;

		rect[i].h = (rect_bg.h * (array[i] + 1)) / size;
		rect[i].y = rect_bg.h - rect[i].h;
	}
}
