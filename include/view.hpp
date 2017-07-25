#ifndef VIEW_HPP
#define VIEW_HPP

// Standard Library
#include <algorithm>
#include <functional>
#include <iosfwd>
#include <type_traits>
#include <utility>

// Third-party
#include "SDL2/SDL.h"

// Internal
#include "runnable.hpp"
#include "driver.hpp"

namespace View {
	using Runnable::e_task;
	using Runnable::TaskBase;
	using Runnable::Driver;

	/** @brief Shorthand for SDL Event type member */
	typedef decltype(SDL_Event::type) EVID;
	/** @brief Runnable SDL Window container */
	struct Frame;
	/** @brief Runnable canvas partition */
	struct Panel;
}

#include "frame.hpp"
#include "panel.hpp"
#include "handler.hpp"

#endif
