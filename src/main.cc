#include <iostream>
#include <cmath>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
using namespace std;

Uint32 getpixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;

	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1: return *p;
		case 2: return *(Uint16 *)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				return p[0] << 16 | p[1] << 8 | p[2];
			} else {
				return p[0] | p[1] << 8 | p[2] << 16;
			}
		case 4: return *(Uint32 *)p;
	}
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
	int bpp = surface->format->BytesPerPixel;

	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			*p = pixel;
			break;
		case 2:
			*(Uint16 *)p = pixel;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}

void null_the_arrays(int red[256], int green[256], int blue[256]) {
	for(int i = 0; i < 256; ++i) {
		red[i] = 0;
		green[i] = 0;
		blue[i] = 0;
	}
}

void fill_rgb_histograms(SDL_Surface *image, int red[256], int green[256], int blue[256]) {
	Uint8 red_c, green_c, blue_c;

	null_the_arrays(red, green, blue);

	SDL_LockSurface(image);
	for(int x = 0; x < image->w; ++x) {
		for(int y = 0; y < image->h; ++y) {
			SDL_GetRGB(getpixel(image, x, y), image->format, &red_c, &green_c, &blue_c);
			++red[red_c];
			++green[green_c];
			++blue[blue_c];
		}
	}
	SDL_LockSurface(image);
}

void fill_rgb_cumulative_histograms(int red[256], int green[256], int blue[256], int cum_red[256], int cum_green[256], int cum_blue[256]) {
	null_the_arrays(cum_red, cum_green, cum_blue);

	cum_red[0] = red[0];
	cum_green[0] = green[0];
	cum_blue[0] = blue[0];

	for(int i = 1; i < 256; ++i) {
		cum_red[i] = red[i] + cum_red[i - 1];
		cum_green[i] = green[i] + cum_green[i - 1];
		cum_blue[i] = blue[i] + cum_blue[i - 1];
	}
}

void calculate_probability(double alpha, int t_red[256], int t_green[256], int t_blue[256], int red[256], int green[256], int blue[256]) {
	null_the_arrays(t_red, t_green, t_blue);

	for(int i = 0; i < 256; ++i) {
		t_red[i] = (int)round(red[i] * alpha);
		t_green[i] = (int)round(green[i] * alpha);
		t_blue[i] = (int)round(blue[i] * alpha);
	}
}

SDL_Surface *equalize_histogram(SDL_Surface *surface, int mask = 7) {
	int red[256], green[256], blue[256];
	int cum_red[256], cum_green[256], cum_blue[256];
	int t_red[256], t_green[256], t_blue[256];
	Uint8 r, g, b;
	double alpha = 255.0 / (surface->w * surface->h);
	SDL_Surface *equalized_surface = NULL;

	fill_rgb_histograms(surface, red, green, blue);
	fill_rgb_cumulative_histograms(red, green, blue, cum_red, cum_green, cum_blue);
	calculate_probability(alpha, t_red, t_green, t_blue, red, green, blue);

	equalized_surface = surface;
	SDL_LockSurface(surface);
	SDL_LockSurface(equalized_surface);
	for(int x = 0; x < surface->w; ++x) {
		for(int y = 0; y < surface->h; ++y) {
			SDL_GetRGB(getpixel(surface, x, y), surface->format, &r, &g, &b);
			putpixel(equalized_surface, x, y, SDL_MapRGB(equalized_surface->format, t_red[r], t_green[g], t_blue[b]));
		}
	}
	SDL_UnlockSurface(equalized_surface);
	SDL_UnlockSurface(surface);

	return equalized_surface;
}

int main() {
	SDL_Surface *image = NULL;
	int red[256], green[256], blue[256];
	int cum_red[256], cum_green[256], cum_blue[256];
	int t_red[256], t_green[256], t_blue[256];
	double alpha, size;

	SDL_Init(SDL_INIT_EVERYTHING);

	image = IMG_Load("haha.png");
	SDL_SaveBMP(equalize_histogram(image), "hoho.bmp");

	SDL_Quit();
	return 0;
}
