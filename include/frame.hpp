#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "view.hpp"

namespace View {
	struct Frame: Runnable::TaskBase<Frame> {
		static constexpr Uint32 s_center = SDL_WINDOWPOS_CENTERED;
		SDL_Window *win;
		Frame(const char *title = "", Uint32 f = 0,
			Uint32 w = 512, Uint32 h = 512,
			Uint32 x = s_center, Uint32 y = s_center);
		template<typename... DN>
		e_task call(e_task e, DN &... dn);
		virtual ~Frame(void);
	};
}

#endif
