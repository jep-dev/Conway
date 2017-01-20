#include "view/frame.hpp"

int main(int argc, const char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO)) return 1;
	View::Frame f("Title", 0, 0, 512, 512, 0);
	SDL_Quit();
}
