#include "view_frame.hpp"
#include <algorithm>
#include <utility>
#include <functional>

#include "templates.hpp"

namespace View {

	Frame::Frame(SDL_Window *win): win(win) {}
	Frame::~Frame(void) { if(win) SDL_DestroyWindow(win); }

	// Base case event handler as specialized handler dispatch
	template<typename S, typename... T> bool
	Frame::handle(EVID && evid, S && ev, T &&... t)
	{
		// return false;
		switch(ev.type) {
			case SDL_WINDOWEVENT_CLOSE:
			case SDL_WINDOWEVENT_RESIZED:
				return handle(ev.type, ev.window);
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				return handle(ev.type, ev.key);
			case SDL_QUIT:
				return false;
			default:
				return handle(ev.type, ev, "Unhandled event");
		}
	}

	// Window event handler
	template<> bool
	Frame::handle(EVID && evid, SDL_WindowEvent && ev)
		{ return evid != SDL_WINDOWEVENT_CLOSE; }

	// Keyboard event handler
	template<> bool
	Frame::handle(EVID && evid, SDL_KeyboardEvent && ev)
		{ return ev.keysym.sym != SDLK_ESCAPE; }

	template<> bool
	// Quit event handler
	Frame::handle(EVID && evid, SDL_QuitEvent && ev)
		{ return false; }

	template<> bool
	// Unhandled event trap
	Frame::handle(EVID && evid, SDL_Event && ev, std::string && msg)
	{
		return true;
	}

	bool Frame::poll(void) {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
			// if(!handle(ev)) return false;
			// if(!handle<ev.type>(ev)) return false;
		}
		return true;
	}
	bool Frame::run(void)
	{
		while(poll()) {
			SDL_FillRect(SDL_GetWindowSurface(win), nullptr, 0x000000);
			SDL_UpdateWindowSurface(win);
			SDL_Delay(200);
		}
		return false;
	}
}
