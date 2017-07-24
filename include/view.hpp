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

	typedef decltype(SDL_Event::type) EVID;
	struct Frame;
	struct Panel;
}

#include "frame.hpp"

#endif
