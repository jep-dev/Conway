#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "SDL2/SDL.h"

namespace View {

	struct Frame {
		/** Polls and processes one event.
 		 * @return true unless the frame should close. */
		bool poll(void);

		/** Polls until it returns false.
 		 * @return true unless the frame should close. */
		bool run(void);

		/** Constructor; forwards the arguments to SDL_CreateWindow.
 		 * @param tn Arguments to forward to SDL_CreateWindow. */
		Frame(SDL_Window * = SDL_CreateWindow("", 0, 0, 640, 480, 0));

		/** Destructor; frees the child window. */
		virtual ~Frame(void);
	private:
		SDL_Window *win;
	};

}

#endif
