#include "view.hpp"

namespace View {
	Runnable::e_task Handler::call(Runnable::e_task e, SDL_Event &ev) {
		return e_task::quit;
	}
	Handler::Handler(void): Runnable::TaskBase<Handler, SDL_Event>() {}
}
