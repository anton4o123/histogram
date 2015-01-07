#ifndef EQUALIZE_HH_
#define EQUALIZE_HH_

#include "basic_sdl.hh"

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void null_the_arrays(int red[256], int green[256], int blue[256]);
void fill_rgb_histogram(SDL_Surface *image, int red[256], int green[256], int blue[256]);
void calculate_probability(double alpha, int t_red[256], int t_green[256], int t_blue[256], int red[256], int green[256], int blue[256]);
SDL_Surface *equalize_histogram(SDL_Surface *surface);

#endif
