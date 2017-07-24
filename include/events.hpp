#ifndef VIEW_EVENTS_HPP
#define VIEW_EVENTS_HPP

#include "view.hpp"

namespace View {
	struct Handler: Runnable::TaskBase<Handler, SDL_Event> {
		Runnable::e_task call(Runnable::e_task e, SDL_Event &ev);
		/* Runnable::e_task call(Runnable::e_task e, SDL_Event &ev) {
			return e_task::quit;
		} */
		Handler(void);
		// Handler(void): TaskBase() {}
		virtual ~Handler(void) = default;
	};
}

#endif
