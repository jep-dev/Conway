#include "view_handler.hpp"
#include "view_frame.hpp"
#include "templates.hpp"
// #include <iostream>

namespace View {
	Frame::Frame(SDL_Window *win): win(win) {}
	Frame::~Frame(void) { if(win) SDL_DestroyWindow(win); }

	bool Frame::poll(void) {
		SDL_Event ev;
		bool cont = true;
		while(cont && SDL_PollEvent(&ev)) {
			cont = handler<SDL_QUIT, SDL_WINDOWEVENT, SDL_KEYDOWN,
				SDL_MOUSEMOTION>()(*this,std::forward<SDL_Event>(ev));
		}
		return cont;
	}
	bool Frame::run(void)
	{
		unsigned i = 0;
		while(poll()) {
			SDL_FillRect(SDL_GetWindowSurface(win), nullptr, 0x000000);
			SDL_UpdateWindowSurface(win);
			SDL_Delay(200);
		}
		return false;
	}
}
