#ifndef VIEW_HANDLER_HPP
#define VIEW_HANDLER_HPP

#include <algorithm>
#include <utility>
#include <functional>
#include "SDL2/SDL.h"


namespace View {
	struct Frame;

	/** @brief Shorthand for SDL_Event::type */
	typedef decltype(SDL_Event::type) EVID;

	/** @brief Event handler implementation
	  @tparam IDS The sequence of events to handle. */
	template<EVID... IDS> struct handler {
		/** @brief Implementation of the handler logic.
		  @param f The frame reference used when the implementation
		  includes operations on the caller.
		  @param ev The event to handle.
		  @return True if the event does not match the IDS sequence,
		  and none of the implementations for matched IDS return false. */
		virtual bool operator()(Frame & f, SDL_Event && ev);
	};
}
#include "view_frame.hpp"

#endif
