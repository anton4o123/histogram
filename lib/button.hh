#ifndef BUTTON_HH_
#define BUTTON_HH_

#include "SDL_rotozoom.h"
#include "basic_sdl.hh"
#include "equalize.hh"

class Button {
	SDL_Rect box;
	SDL_Surface *button;
	SDL_Surface *button_hover;
	string name_;
	bool hover_;
public:
	Button(int x, int y, int w, int h, string name);
	~Button();
	void handle_events();
	void show(bool hover_type);
};

#endif
