#include "button.hh"

SDL_Event event;

Button::Button(int x, int y, int w, int h, string name) {
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	name_ = name;
	button = load_image(name_ + ".bmp");
	button_hover = load_image(name_ + "_hover.bmp");
	hover_ = true;
}

Button::~Button() {
	SDL_FreeSurface(button);
	SDL_FreeSurface(button_hover);
}

void Button::handle_events() {
	int x = 0, y = 0;

	if(event.type == SDL_MOUSEMOTION) {
		x = event.motion.x;
		y = event.motion.y;

		if((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h)) {
			if(!hover_) {
				hover_ = true;
				show(hover_);
			}
		} else if(hover_) {
			hover_ = false;
			show(hover_);
		}
	}

	if(event.type == SDL_MOUSEBUTTONDOWN) {
		x = event.motion.x;
		y = event.motion.y;

		if((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h)) {
			if(name_ == "files/open") {
				original = IMG_Load(take_path().c_str());
				for_rendering = SDL_DisplayFormat(original);
				for_rendering = rotozoomSurfaceXY(for_rendering, 0, 0.3, 0.3, 1);
				surf_change = true;
			}

			if(name_ == "files/equalize") {
				original = equalize_histogram(original);
				SDL_FreeSurface(for_rendering);
				for_rendering = SDL_DisplayFormat(original);
				surf_change = true;
			}

			if(name_ == "files/save") {
				SDL_SaveBMP(original, take_path().c_str());
				surf_change = true;
			}
		}
	}
}

void Button::show(bool hover_type) {
	if(!hover_type) {
		apply_surface(box.x, box.y, button, screen, NULL);
	} else {
		apply_surface(box.x, box.y, button_hover, screen, NULL);
	}
	SDL_Flip(screen);
}
