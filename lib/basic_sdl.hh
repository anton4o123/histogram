#ifndef BASIC_SDL_
#define BASIC_SDL_

#include <iostream>
#include <string>
#include <cmath>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

extern bool surf_change;

extern SDL_Surface *screen;
extern SDL_Surface *original;
extern SDL_Surface *equalized;
extern SDL_Surface *for_rendering;
extern SDL_Surface *text;
extern TTF_Font *font;
extern SDL_Event event;
extern SDL_Color text_color;

bool start_SDL();
bool load_files();
SDL_Surface *load_image(string filename);
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
string take_path();
void clean_up();

#endif
