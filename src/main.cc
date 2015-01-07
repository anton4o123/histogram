#include <iostream>
#include <cmath>
#include "../lib/basic_sdl.hh"
#include "../lib/button.hh"
using namespace std;

SDL_Surface *screen;
SDL_Surface *original;
SDL_Surface *for_rendering;
SDL_Surface *text;
TTF_Font *font;
SDL_Color text_color = {0, 0, 0};
bool surf_change = true;

int main() {
	if(!start_SDL() || !load_files()) {
		return 1;
	}

	Button open(470, 20, 150, 38, "files/open");
        Button equalize(470, 80, 150, 38, "files/equalize");
        Button save(470, 140, 150, 38, "files/save");

	while(true) {
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				break;
			}

			open.handle_events();
			equalize.handle_events();
			save.handle_events();

			if(surf_change) {
				surf_change = false;
				SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
				apply_surface(10, 10, for_rendering, screen, NULL);
				open.show(false);
				equalize.show(false);
				save.show(false);
				SDL_Flip(screen);
			}
		}
		SDL_Delay(2);
	}

	clean_up();
	return 0;
}
