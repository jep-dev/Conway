#include "view_handler.hpp"
// #include <iosfwd>

namespace View {
	struct Frame;

	template<EVID... IDS>
	bool handler<IDS...>::operator()(Frame & frame, SDL_Event && ev)
		{ return false; }

	template<> struct handler<SDL_QUIT> : handler<> {
		bool operator()(Frame & frame, SDL_Event && ev)
			{ return false; }
	};
	template<> struct handler<SDL_WINDOWEVENT> : handler<> {
		bool operator()(Frame & frame, SDL_Event && ev)
			{ return ev.type != SDL_WINDOWEVENT_CLOSE; }
	};
	template<> struct handler<SDL_KEYDOWN> : handler<> {
		bool operator()(Frame & frame, SDL_Event && ev)
			{ return ev.key.keysym.scancode != SDL_SCANCODE_ESCAPE; }
	};
	template<> struct handler<SDL_MOUSEMOTION> : handler<> {
		bool operator()(Frame & frame, SDL_Event && ev)
			{ return true; }
	};

	/** @brief Generic implementation of event-to-handler dispatch.
		@tparam ID The current major event type to match.
		@tparam IDS The remaining event types, if any. */
	template<EVID ID, EVID... IDS>
	struct handler<ID, IDS...> : handler<ID>, handler<IDS...> {
		/** @brief Delegates to the first handler if it matches the most major
		  event type and recurses on the remainder otherwise.
		  @param frame The source of the event or target of side effects.
		  @param ev The event to handle or delegate.
		  @return true if none of the matching handlers return false. */
		bool operator()(Frame & frame, SDL_Event && ev) {
			if((ev.type & 0xff00) == ID)
				return handler<ID>()(frame, std::forward<SDL_Event>(ev));
			return handler<IDS...>()(frame, std::forward<SDL_Event>(ev));
		}
	};
}
