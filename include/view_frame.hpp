#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "SDL2/SDL.h"
#include "runnable.hpp"
#include "templates.hpp"

namespace View {

	/** @brief Shorthand for SDL_Event::type */
	typedef decltype(SDL_Event::type) EVID;

	/** @brief A container for SDL_Window with event logic */
	struct Frame : public Runnable {

		/** @brief Polls and processes one event.
 		 * @return true unless the frame should close. */
		virtual bool poll(void);

		/** @brief Polls until it returns false.
 		 * @return true unless the frame should close. */
		virtual bool run(void);

		/** @brief Template for event handlers; signature will change soon.
		 * @tparam S type of non-optional first argument, soon SDL_Event.
		 * @tparam T type(s) of optional argument(s).
		 * @param evid event id from SDL_Event::type.
		 * @param s non-optional first argument, soon an SDL_Event.
		 * @param t optional argument(s), currently used for message passing.
		 * @return true unless the frame should close. */
		template<typename S, typename... T>
		bool handle(EVID && evid, S && s, T &&... t);

		/** @brief Constructor; creates and stores an SDL_Window.
 		 * @param win The window managed by the Frame */
		Frame(SDL_Window *win = SDL_CreateWindow("", 0, 0, 640, 480, 0));

		/** @brief Destructor; frees the window managed by the Frame. */
		virtual ~Frame(void);
	private:
		/** @brief Internal window object, freed by the destructor. */
		SDL_Window *win;
	};

}

#endif
