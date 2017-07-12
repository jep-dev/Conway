#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "SDL2/SDL.h"
#include "runnable.hpp"
#include "templates.hpp"

namespace View {
	struct Frame;
	typedef decltype(SDL_Event::type) EVID;
}

#include "view_handler.tpp"

namespace View {

	/* struct Frame;

	template<EVID... IDS> struct handler {
		virtual bool operator()(Frame &, SDL_Event &&);
	}; */

	/** @brief A container for SDL_Window with event logic */
	struct Frame : public Runnable {

		/** @brief Updates and repeats as long as poll returns true.
		 * @return False if and only if poll returns false. */
		virtual bool run(void);

		/** @brief Polls for events and calls a handler on each.
		 * @return The return value of the associated handler. */
		virtual bool poll(void);

		template<EVID... IDS>
		bool handle(SDL_Event && ev);

		/** @brief Constructor; creates and stores an SDL_Window.
		 * @param win The window managed by the Frame. */
		Frame(SDL_Window *win = SDL_CreateWindow("", 0, 0, 640, 480, 0));

		/** @brief Destructor; frees the window managed by the Frame. */
		virtual ~Frame(void);
	private:
		/** @brief Internal window object, freed by the destructor. */
		SDL_Window *win;
	};
}

#endif
