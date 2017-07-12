#include "modular_main.hpp"

int main(int argc, const char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO)) return 1;
	View::Frame f;
	f.run();
	SDL_Quit();
}
