#ifndef VIEW_EVENTS_HPP
#define VIEW_EVENTS_HPP

#include "view.hpp"

namespace View {
	/* template<unsigned MAJOR>
	struct Handler: Runnable::TaskBase<Handler<MAJOR>, const SDL_Event> { */
	template<SDL_EventType E>
	struct Handler: Runnable::TaskBase<Handler<E>, const SDL_Event> {
		Runnable::e_task call(Runnable::e_task t, SDL_Event const& ev);
		Handler(void);
		virtual ~Handler(void) = default;
	};
	struct HandlerBase: Runnable::TaskBase<HandlerBase, const SDL_Event> {
		Runnable::e_task call(Runnable::e_task e, SDL_Event const& ev);
		HandlerBase(void);
		virtual ~HandlerBase(void) = default;
	};
}

#endif
