#include "view.hpp"

namespace View {
	/* template<unsigned MAJOR> Runnable::e_task
	Handler<MAJOR>::call(Runnable::e_task e, SDL_Event const& ev) {
		switch(e) {
		}
	} */
	template<> e_task
	Handler<SDL_QUIT>::call(e_task t, SDL_Event const& ev) {
		return e_task::quit; // TODO
	}
	template<> e_task
	Handler<SDL_WINDOWEVENT>::call(e_task t, SDL_Event const& ev) {
		// TODO view -> handler
		return ev.window.type == SDL_WINDOWEVENT_CLOSE ?
			e_task::quit : t;
	}
	template<> e_task
	Handler<SDL_MOUSEMOTION>::call(e_task t, SDL_Event const& ev) {
		// TODO handler -> model
		return t;
	}
	template<> e_task
	Handler<SDL_KEYDOWN>::call(e_task t, SDL_Event const& ev) {
		return t;
	}
	template<SDL_EventType E>
	Handler<E>::Handler(void):
		Runnable::TaskBase<Handler<E>, const SDL_Event>() {}

	Runnable::e_task
	HandlerBase::call(Runnable::e_task t, SDL_Event const& ev) {
		switch(ev.type & 0xff00) {
			case SDL_WINDOWEVENT:
				return Handler<SDL_WINDOWEVENT>().call(t, ev);
			case SDL_QUIT:
				return Handler<SDL_QUIT>().call(t, ev);
			case SDL_MOUSEMOTION:
				return Handler<SDL_MOUSEMOTION>().call(t, ev);
			case SDL_KEYDOWN:
				return Handler<SDL_KEYDOWN>().call(t, ev);
			default: return t;
		}
	}
	HandlerBase::HandlerBase(void):
		Runnable::TaskBase<HandlerBase, const SDL_Event>() {}
}
