#include "modular_main.hpp"

// #include <iostream>

int main(int argc, const char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO)) return 1;
	View::Frame f;
	f.run();
	SDL_Quit();

	typedef std::true_type TT;
	typedef std::false_type FT;

	static_assert(is_true<TT>::value, "identity of true");
	static_assert(!is_true<FT>::value, "identity of false");
	static_assert(none_true<bool,0,0>::value, "none of {0,0}");
	static_assert(!none_true<bool,0,1>::value, "any of {0,1}");
	static_assert(!none_true<bool,1,0>::value, "any of {1,0}");
	static_assert(!none_true<bool,1,1>::value, "any of {1,1}");
	static_assert(!none_true<bool,0,0,0,1>::value, "any of {0, 0..., 1}");

	static_assert(!none_same_t<int, bool, int>::value,
			"int one of {bool, int}");
	static_assert(none_same_t<int, bool, char>::value,
			"int none of {bool, char}");

	static_assert(none_match_t<View::EVID,
			SDL_WINDOWEVENT_CLOSE, SDL_QUIT, SDL_KEYDOWN>::value,
			"Close EVID none of {Quit, Keydown}");
	static_assert(!none_match_t<View::EVID, SDL_WINDOWEVENT_CLOSE,
			SDL_WINDOWEVENT_ENTER, SDL_WINDOWEVENT_CLOSE>::value,
			"Close EVID one of {Enter, Close}");

}
