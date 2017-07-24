#include "panel.hpp"

namespace View {
	Panel::Panel(void): TaskBase() {}
	template<>
	e_task Panel::call(Runnable::e_task e) {
		// TODO stub
		return e;
	}
}
