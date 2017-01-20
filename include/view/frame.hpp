#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "SDL2/SDL.h"

namespace View {

	struct Frame {
		/** Runs one full update-and-render cycle.
 		 * @return true if the cycle was successful. */
		bool run_once(void);
		/** Repeats run_once until it returns false.
 		 * @return true if the cycles were successful. */
		bool run(void);

		/** Constructor; forwards the arguments to SDL_CreateWindow. */
		template<typename... TN> Frame(TN...);
		/** Destructor; frees the child window. */
		virtual ~Frame(void);
	private:
		SDL_Window *win;
	};

}

#include "frame.tpp"

#endif
