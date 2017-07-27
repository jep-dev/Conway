#include "modular.hpp"
#include <iostream>

using std::cout;
using std::endl;


// Unconditional quit response
e_task OnFrameQuitEvent::handle(e_task task, Frame &frame, SDL_Event const& ev) {
	return e_task::quit;
}
// Conditional quit response or passthrough
e_task OnFrameWindowEvent::handle(e_task task, Frame &frame, SDL_Event const& ev) {
	// TODO match window ID
	switch(ev.window.event) {
		case SDL_WINDOWEVENT_CLOSE: return e_task::quit;
		// TODO window event stub
		default: return task;
	}
	// return e_task::quit;
}
// Conditional quit response or passthrough
e_task OnFrameKeyEvent::handle(e_task task, Frame &frame, SDL_Event const& ev) {
	// TODO match window ID
	switch(ev.key.keysym.sym) {
		case SDLK_ESCAPE: return e_task::quit;
		// TODO key event stub
		default: return task;
	}
}
// Passthrough unless delegate handlers intervene
e_task OnFrameMouseEvent::handle(e_task task, Frame &frame, SDL_Event const& ev) {
	// TODO mouse event stub
	return task;
}
// Passthrough unless delegate handlers intervene
e_task OnFrameUserEvent::handle(e_task task, Frame &frame, SDL_Event const& ev) {
	// TODO user event stub
	return task;
}


void info(const char *arg0) {
	endl(cout << arg0 << " ('" BUILD "', v" << VERSION << ")");
}

int main(int argc, const char *argv[]) {
	info(argv[0]);

	Frame frame("Test Title");
	OnFrameQuitEvent on_quit;
	OnFrameWindowEvent on_window;
	OnFrameKeyEvent on_key;
	OnFrameMouseEvent on_mouse;
	OnFrameUserEvent on_user;

	uint32_t frames = 0, delay = 200;
	const uint32_t max_frames = ~uint32_t(0);
	Driver<> driver([&] () -> bool {
		if(frames++ < max_frames) {
			cout << "Frame: " << frames << endl;
			SDL_Delay(delay);
			return true;
		}
		return false;
	});

	e_task dtask, ftask = e_task::start;
	while(ftask != e_task::quit)
		ftask = call(dtask = frame.call(ftask, on_quit, on_window,
				on_key, on_mouse, on_user), driver);
}
