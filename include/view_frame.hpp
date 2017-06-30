#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "SDL2/SDL.h"
#include "runnable.hpp"
#include "templates.hpp"

namespace View {

	typedef decltype(SDL_Event::type) EVID;
	struct Frame : public Runnable {

		/** Polls and processes one event.
 		 * @return true unless the frame should close. */
		virtual bool poll(void);

		/** Polls until it returns false.
 		 * @return true unless the frame should close. */
		virtual bool run(void);

		/** Template for event handlers; signature will change soon.
		 * @tparam S type of non-optional first argument, soon SDL_Event.
		 * @tparam T type(s) of optional argument(s).
		 * @param evid event id from SDL_Event::type.
		 * @param s non-optional first argument, soon an SDL_Event.
		 * @param t optional argument(s), currently used for message passing.
		 * @return true unless the frame should close. */
		template<typename S, typename... T>
		bool handle(EVID && evid, S && s, T &&... t);

		/** Constructor; forwards the arguments to SDL_CreateWindow.
 		 * @param win The window managed by the Frame */
		Frame(SDL_Window *win = SDL_CreateWindow("", 0, 0, 640, 480, 0));

		/** Destructor; frees the child window. */
		virtual ~Frame(void);
	private:
		SDL_Window *win;
	};

}

#endif
