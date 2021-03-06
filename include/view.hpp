#ifndef VIEW_HPP
#define VIEW_HPP

// Third-party
#include "SDL2/SDL.h" // -> SDL2/SDL_*.hpp
// Internal
#include "runnable.hpp" // -> driver.hpp, handler.hpp

namespace View {
	using Runnable::Signal;
	using Runnable::TaskBase;
	using Runnable::Driver;

	/** @brief Shorthand for SDL Event type member */
	typedef decltype(SDL_Event::type) EVID;
	/** @brief Runnable SDL Window container */
	struct Frame;
	/** @brief Runnable canvas partition */
	struct Panel;
}
namespace Runnable {
	template<> Signal TaskBase<View::Frame>::call(Signal sig)
		{ return Signal::Quit; }
}

#include "frame.hpp"
#include "panel.hpp"

#endif
