#ifndef VIEW_FRAME_TPP
#define VIEW_FRAME_TPP

namespace View {
	template<typename... TN>
	Frame::Frame(TN... tn):
		win(SDL_CreateWindow(tn...)) {}
}

#endif
