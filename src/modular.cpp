#include <iostream>
#include "view.hpp"

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
	Driver<> driver([&frames]() -> bool {
		if(frames++ >= max_frames)
			return false;
		cout << "Frame: " << frames << endl;
		SDL_Delay(ms_delay);
		return true;
	});

	e_task dtask, ftask = e_task::start;
	while(ftask != e_task::quit)
		ftask = call(dtask = frame.call(ftask), driver);
}
