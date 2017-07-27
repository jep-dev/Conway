#ifndef RUNNABLE_EVENTS_HPP
#define RUNNABLE_EVENTS_HPP

#include <tuple>

#include "runnable.hpp"
#include "SDL2/SDL.h"

namespace Runnable {
	/* Handler with compile-time emulated virtual methods */
	template<typename D, typename SUBJ, typename... OBJS>
	struct HandlerCRTP;
	/* Specialization of HandlerCRTP that prepends const SDL_Event to OBJS */
	template<bool EXACT, uint32_t ID, typename D, typename SUBJ, typename... OBJS>
	struct EventHandlerCRTP;
	/* Collection of types by invariance over subject and objects */
	template<typename SUBJ, typename... OBJS>
	struct EventHandlers;

	template<typename D, typename SUBJ, typename... OBJS>
	struct HandlerCRTP {
		e_task handle(e_task task, SUBJ & subj, OBJS &... objs) {
			return static_cast<D*>(this) -> handle(task, subj, objs...);
		}
	};
	template<bool EXACT, uint32_t ID, typename D, typename SUBJ, typename... OBJS>
	struct EventHandlerCRTP: HandlerCRTP<EventHandlerCRTP<EXACT, ID, D, SUBJ, OBJS...>,
			const SDL_Event, SUBJ, OBJS...> {
		e_task handle(e_task task, SUBJ &subj, SDL_Event const& ev, OBJS &... objs) {
			return static_cast<D*>(this) -> handle(task, subj, ev, objs...);
		}
	};
	template<typename SUBJ, typename... OBJS>
	struct EventHandlers {
		template<bool EXACT, uint32_t ID, typename D>
		struct EventHandler;

		template<bool EXACT, uint32_t ID, typename D>
		struct EventHandler: EventHandlerCRTP<EXACT, ID, EventHandlers<SUBJ, OBJS...>
				::EventHandler<EXACT, ID, D>, SUBJ, OBJS...> {
			e_task handle(e_task task, SUBJ &subj, OBJS &... objs, SDL_Event const& ev);
		};
	private:
		EventHandlers(void);
	};

	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using QuitEventHandler = typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
		::template EventHandler<EXACT, SDL_QUIT, D>;
	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using WindowEventHandler = typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
		::template EventHandler<EXACT, SDL_WINDOWEVENT, D>;
	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using KeyEventHandler = typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
		::template EventHandler<EXACT, SDL_KEYDOWN, D>;
	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using MouseEventHandler = typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
		::template EventHandler<EXACT, SDL_MOUSEMOTION, D>;
	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using UserEventHandler = typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
		::template EventHandler<EXACT, SDL_USEREVENT, D>;
}

#endif
