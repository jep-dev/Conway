#include "frame.hpp"


namespace View {
	Frame::~Frame(void)
	{
		if(win) SDL_DestroyWindow(win);
	}
	bool Frame::run_once(void)
	{
		SDL_Event ev;
		if(SDL_PollEvent(&ev)) {
			switch(ev.type) {
				case SDL_WINDOWEVENT: {
					auto &window = ev.window;
					/*if(window = win) {
					}*/
				} break;
			}
		}
		return true;
	}
	bool Frame::run(void)
	{
		while(run_once()) {
		}
		return true;
	}
}
