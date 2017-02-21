#include "frame.hpp"


namespace View {
	Frame::Frame(SDL_Window *win): win(win) {}
	Frame::~Frame(void)
	{
		if(win) SDL_DestroyWindow(win);
	}
	bool Frame::poll(void) {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
				case SDL_WINDOWEVENT_CLOSE: {
						return false;
					}
				case SDL_QUIT:
					return false;
				case SDL_WINDOWEVENT: {
					if(ev.window.windowID == SDL_GetWindowID(win)) {
						switch(ev.window.type) {
							case SDL_WINDOWEVENT_CLOSE:
								return false;
							case SDL_WINDOWEVENT_RESIZED:
								// TODO
								break;
							case SDL_KEYDOWN:
								return false;
							default:
								break;
						}
					}
				} break;
				case SDL_KEYDOWN: {
					auto &key = ev.key;
					switch(key.keysym.sym) {
						case SDLK_ESCAPE:
							return false;
					}
				} break;
				default: break;
			}
		}
		return true;
	}
	bool Frame::run(void)
	{
		while(poll()) {
			SDL_FillRect(SDL_GetWindowSurface(win), nullptr, 0xFFFFFF);
			SDL_UpdateWindowSurface(win);
			SDL_Delay(200);
		}
		return false;
	}
}
