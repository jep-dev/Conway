#include "frame.hpp"


namespace View {

	SDL_Surface *Frame::get_surface(void)
	{
		return SDL_GetWindowSurface(win);
	}
	SDL_Renderer *Frame::get_renderer(void)
	{
		return SDL_GetRenderer(win);
	}
	SDL_Window *Frame::get_window(void) 
	{
		return win;
	}

}
