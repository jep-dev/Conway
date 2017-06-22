#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "SDL2/SDL.h"

namespace View {

	struct Frame {
		/** Polls and processes one event.
 		 * @return true unless the frame should close. */
		bool poll(void);
		//bool poll(void) { return false; }

		/** Polls until it returns false.
 		 * @return true unless the frame should close. */
		bool run(void);
		//bool run(void) { return false; }

		/** Constructor; forwards the arguments to SDL_CreateWindow.
 		 * @param tn Arguments to forward to SDL_CreateWindow. */
		Frame(SDL_Window *win = SDL_CreateWindow("", 0, 0, 640, 480, 0));
			/*win(win) {} */

		/** Destructor; frees the child window. */
		virtual ~Frame(void);
	private:
		SDL_Window *win;
	};

}

#endif
