#ifndef VIEW_FRAME_HPP
#define VIEW_FRAME_HPP

#include "view.hpp"
using namespace View;
using namespace Runnable;

namespace Runnable {
	struct OnFrameQuitEvent;
	struct OnFrameWindowQuitEvent;
	struct OnFrameKeyQuitEvent;
	struct OnFrameMouseQuitEvent;
	struct OnFrameUserQuitEvent;

	struct OnFrameQuitEvent:
	QuitEventHandler<1, View::Frame, OnFrameQuitEvent> {
		e_task handle(e_task, View::Frame &, SDL_Event const&);
	};
	struct OnFrameWindowEvent:
	WindowEventHandler<0, View::Frame, OnFrameWindowEvent> {
		e_task handle(e_task, View::Frame &, SDL_Event const&);
	};
	struct OnFrameKeyEvent:
	KeyEventHandler<0, View::Frame, OnFrameKeyEvent> {
		e_task handle(e_task, View::Frame &, SDL_Event const&);
	};
	struct OnFrameMouseEvent:
	MouseEventHandler<0, View::Frame, OnFrameMouseEvent> {
		e_task handle(e_task, View::Frame &, SDL_Event const&);
	};
	struct OnFrameUserEvent:
	UserEventHandler<0, View::Frame, OnFrameUserEvent> {
		e_task handle(e_task, View::Frame &, SDL_Event const&);
	};
}

namespace View {
	// struct Frame: Runnable::TaskBase<Frame>
	struct Frame: Runnable::TaskBase<Frame, Runnable::OnFrameQuitEvent,
		Runnable::OnFrameWindowEvent, Runnable::OnFrameKeyEvent,
		Runnable::OnFrameMouseEvent, Runnable::OnFrameWindowEvent> {
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
