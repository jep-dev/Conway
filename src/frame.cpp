#include "view.hpp"
#include <iostream>
#include <map>

namespace View {
	Frame::Frame(const char *title, Uint32 f,
		unsigned w, unsigned h, unsigned x, unsigned y):
		win(SDL_CreateWindow(title, x, y, w, h, f)),
		TaskBase() {}

	Frame::~Frame(void) { SDL_DestroyWindow(win); }
}
namespace Runnable {
	// TODO why is this necessary? Remove or provide impl here instead
	template<> e_task TaskBase<View::Frame>::call(e_task e)
		{ return e_task::quit; }
}
namespace View {
	/* template<>
	e_task Frame::call(Runnable::e_task t)*/
	template<>
	e_task Frame::call(Runnable::e_task task, OnFrameQuitEvent &on_quit,
		OnFrameWindowEvent &on_window, OnFrameKeyEvent &on_key,
		OnFrameMouseEvent &on_mouse, OnFrameUserEvent &on_user) {
		using Runnable::e_task;
		switch(task) {
			// Before 'start', driver may sleep
			case e_task::start:
				return e_task::run;
			case e_task::run:
				SDL_Event ev;
				if(SDL_PollEvent(&ev)) {
					switch(ev.type & 0xff00) {
						case SDL_QUIT: return on_quit.handle(task, *this, ev);
						case SDL_WINDOWEVENT: return on_window.handle(task, *this, ev);
						case SDL_KEYDOWN: return on_key.handle(task, *this, ev);
						case SDL_MOUSEMOTION: return on_mouse.handle(task, *this, ev);
						case SDL_USEREVENT: return on_user.handle(task, *this, ev);
						default: return e_task::run;
					}
						/* case SDL_QUIT:
							// return e_task::quit;
						case SDL_WINDOWEVENT:
							if(ev.window.event == SDL_WINDOWEVENT_CLOSE)
								return e_task::quit;
							break;
						// TODO delegate/dispatch from this point
						case SDL_KEYDOWN:
							if(ev.key.keysym.sym == SDLK_ESCAPE)
								return e_task::quit;
							break;
					return e_task::run; */
				}
				SDL_FillRect(SDL_GetWindowSurface(win),
					nullptr, 0x000000);
				SDL_UpdateWindowSurface(win);
				return e_task::start;
			case e_task::pass:
				return e_task::pass;
			case e_task::error:
				return e_task::quit;
			case e_task::quit:
				return e_task::quit;
				// Window failure := app failure
				// -- return pass or define new signal for close vs. quit
		}
	}
}
