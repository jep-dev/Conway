#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "SDL2/SDL.h"

namespace View {

	struct Frame {
		// Getters
		SDL_Surface *get_surface(void);
		SDL_Renderer *get_renderer(void);
		SDL_Window *get_window(void);

		// Setters
		bool run_once(void);
		bool run(void);

		// {C,D}'tors
		template<typename... TN> Frame(TN...);
		virtual ~Frame(void);
	private:
		SDL_Window *win;
	};

}

#include "frame.tpp"

#endif
