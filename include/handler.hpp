#ifndef RUNNABLE_EVENTS_HPP
#define RUNNABLE_EVENTS_HPP

#include <tuple>

#include "runnable.hpp"
#include "SDL2/SDL_events.h"

namespace Runnable {
	/* Handler template with compile-time emulated virtual methods.
		TODO: HandlerCRTP can be used for much more than EventHandlers!
		* Driver type, replace callback with ref pass and callable interface
		* Log type, swap implementations to toggle or vary debugging info
		* Any use case for the PIMPL idiom; little/no associated overhead
	*/
	template<typename D, typename SUBJ, typename... OBJS>
	struct HandlerCRTP {
		Signal handle(Signal task, SUBJ & subj, OBJS &... objs);
	};

	template<bool EXACT, uint32_t ID, typename D,
		typename SUBJ, typename... OBJS>
	struct EventHandlerCRTP: HandlerCRTP<EventHandlerCRTP<EXACT, ID, D,
			SUBJ, OBJS...>, const SDL_Event, SUBJ, OBJS...> {
		Signal handle(Signal task, SUBJ &subj,
				SDL_Event const& ev, OBJS &... objs) {
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
			Signal handle(Signal task,
				SUBJ &subj, OBJS &... objs, SDL_Event const& ev);
		};
	private:
		EventHandlers(void);
	};

	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using QuitEventHandler =
		typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
			::template EventHandler<EXACT, SDL_QUIT, D>;

	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using WindowEventHandler =
		typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
			::template EventHandler<EXACT, SDL_WINDOWEVENT, D>;

	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using KeyEventHandler =
		typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
			::template EventHandler<EXACT, SDL_KEYDOWN, D>;

	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using MouseEventHandler =
		typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
			::template EventHandler<EXACT, SDL_MOUSEMOTION, D>;

	template<bool EXACT, typename D, typename SUBJ, typename... OBJS>
	using UserEventHandler =
		typename EventHandlers<SUBJ, const SDL_Event, OBJS...>
			::template EventHandler<EXACT, SDL_USEREVENT, D>;
}

#endif
