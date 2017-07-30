#include "panel.hpp"

namespace View {
	Panel::Panel(void): TaskBase() {}
	template<>
	Signal Panel::call(Signal sig) {
		// TODO stub
		return sig;
	}
}
