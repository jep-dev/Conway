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
#include "templates.hpp"

#include "runnable.hpp"
#include "driver.hpp"

namespace View {
	typedef decltype(SDL_Event::type) EVID;
}

#include "frame.hpp"

#endif
