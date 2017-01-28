#include "frame.hpp"


namespace View {
	Frame::~Frame(void)
	{
		if(win) SDL_DestroyWindow(win);
	}
	bool Frame::run_once(void)
	{
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
				case SDL_WINDOWEVENT_CLOSE: {
					return false;
				}
				case SDL_QUIT:
				case SDL_WINDOWEVENT: {
					//auto &window = ev.window;
				} break;
				case SDL_KEYDOWN: {
					auto &key = ev.key;
					switch(key.keysym.sym) {
						case SDLK_ESCAPE:
							return false; break;
					}
				} break;
				default: break;
			}
		}
		SDL_Delay(200);
		return true;
	}
	bool Frame::run(void)
	{
		while(run_once()) {
		}
		return true;
	}
}
