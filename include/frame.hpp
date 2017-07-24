#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "view.hpp"

namespace View {
	struct Frame: Runnable::TaskBase<Frame> {
	protected:
		static constexpr Uint32 s_center = SDL_WINDOWPOS_CENTERED;
		SDL_Window *win;
	public:
		/** @brief Constructor; initializes SDL_Window member with the given
		  arguments as initial values for SDL_CreateWindow.
		  @param title The title of the window.
		  @param f The flags for the window, currently none
		  @param w The width of the window
		  @param h The height of the window
		  @param x The horizontal position of the window
		  @param y The vertical position of the window */
		Frame(const char *title = "", Uint32 f = 0,
			Uint32 w = 512, Uint32 h = 512,
			Uint32 x = s_center, Uint32 y = s_center);
		/** @brief Calls the Frame as a Runnable task.
		  @tparam DN The type of the remainder of the arguments to call.
		  @param e The input task to handle.
		  @param dn The remainder of the arguments to call.
		  @return The response task with respect to the timeline of one frame.
		  */
		template<typename... DN>
		e_task call(e_task e, DN &... dn);
		/** @brief Destructor; frees the managed SDL_Window. */
		virtual ~Frame(void);
	};
}

#endif
