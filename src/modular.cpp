#include <iostream>

#include "view.hpp"
#include "driver.hpp"
#include "SDL2/SDL.h"

using namespace Runnable;
using namespace View;
using std::cout;
using std::endl;

#ifndef BUILD
#define BUILD "n/a"
#endif
#ifndef VERSION
#define VERSION 0
#endif

void info(const char *arg0) {
	endl(cout << arg0 <<
		" ('" BUILD "', v" << VERSION << ")");
}

static constexpr unsigned int ms_delay = 200, max_frames = ~0;

int main(int argc, const char *argv[]) {
	unsigned frames = 0;
	info(argv[0]);
	Frame frame("Test Title");
	Driver<> driver([&frames]() {
		cout << "Frame: " << frames++ << endl;
		SDL_Delay(ms_delay);
	});

	e_task dtask, ftask = e_task::start;
	while(true) {
		dtask = frame.call(ftask);
		ftask = call(dtask, driver);
		// if((unsigned(dtask)|unsigned(ftask)) & unsigned(e_task::error)) {
		if(dtask == e_task::quit || ftask == e_task::quit
			|| dtask == e_task::error || ftask == e_task::error) {
			cout << "Frame returned " << task_str(dtask)
				<< "; driver returned " << task_str(ftask) << endl;
			break;
		}
	}
}
