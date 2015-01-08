#include "basic_sdl.hh"

bool start_SDL() {
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1 || TTF_Init() == -1) {
		return false;
	}

	SDL_EnableUNICODE(SDL_ENABLE);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen == NULL) {
		return false;
	}
	SDL_WM_SetCaption("Histogram equalizer", NULL);

	return true;
}

bool load_files() {
	font = TTF_OpenFont("files/cour.ttf", 30);
	if(font == NULL) {
		return false;
	}

	return true;
}

SDL_Surface *load_image(string filename) {
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage != NULL) {
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clip, destination, &offset);
}

string take_path() {
	bool change = true;
	string text_string;

	while(true) {
		if(change) {
			change = false;
			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x88, 0x88, 0x88));
			text = TTF_RenderText_Solid(font, "Enter path: ", text_color);
			apply_surface(0, 0, text, screen, NULL);
			text = TTF_RenderText_Solid(font, text_string.c_str(), text_color);
			apply_surface(0, 20, text, screen, NULL);
			SDL_Flip(screen);
		}

		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_KEYDOWN) {
				if(event.key.keysym.sym == SDLK_BACKSPACE) {
					if(text_string.size() > 0) {
						text_string.erase(text_string.size() - 1);
						change = true;
					}
				}

				if(event.key.keysym.sym == SDLK_RETURN) {
					return text_string;
				}

				if(event.key.keysym.sym == SDLK_ESCAPE) {
					return string("");
				}

				if((event.key.keysym.unicode >= (Uint16)'0' && event.key.keysym.unicode <= (Uint16)'9') || (event.key.keysym.unicode >= (Uint16)'a' && event.key.keysym.unicode <= (Uint16)'z') || (event.key.keysym.unicode >= (Uint16)'A' && event.key.keysym.unicode <= (Uint16)'Z') || (event.key.keysym.unicode == (Uint16)'.') || (event.key.keysym.unicode == (Uint16)'/')) {
					text_string += event.key.keysym.unicode;
					change = true;
				}
			}
		}
	}
}

void clean_up() {
	SDL_EnableUNICODE(SDL_DISABLE);
	SDL_Quit();
}
