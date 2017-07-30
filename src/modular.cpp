#include "modular.hpp"
#include <iostream>

using std::cout;
using std::endl;


// Unconditional quit response
Signal OnFrameQuitEvent::handle(Signal sig, Frame &frame, SDL_Event const& ev) {
	return Signal::Done;
}
// Conditional quit response or passthrough
Signal OnFrameWindowEvent::handle(Signal sig,
		Frame &frame, SDL_Event const& ev) {
	// TODO match window ID
	switch(ev.window.event) {
		case SDL_WINDOWEVENT_CLOSE: return Signal::Done;
		// TODO window event stub
		default: return sig;
	}
}
// Conditional quit response or passthrough
Signal OnFrameKeyEvent::handle(Signal sig, Frame &frame, SDL_Event const& ev) {
	// TODO match window ID
	switch(ev.key.keysym.sym) {
		case SDLK_ESCAPE: return Signal::Done;
		// TODO key event stub
		default: return sig;
	}
}
// Passthrough unless delegate handlers intervene
Signal OnFrameMouseEvent::handle(Signal sig,
		Frame &frame, SDL_Event const& ev) {
	// TODO mouse event stub
	return sig;
}
// Passthrough unless delegate handlers intervene
Signal OnFrameUserEvent::handle(Signal sig,
		Frame &frame, SDL_Event const& ev) {
	// TODO user event stub
	return sig;
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

	Signal dsig, fsig = Signal::Start;
	while(!(fsig & Signal::Abort))
		fsig = call(dsig = frame.call(fsig, on_quit, on_window,
				on_key, on_mouse, on_user), driver);
}
