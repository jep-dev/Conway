#ifndef VIEW_PANEL_HPP
#define VIEW_PANEL_HPP

#include "view.hpp"

namespace View {
	struct Panel: Runnable::TaskBase<Panel> {
		template<typename... DN>
		Signal call(Signal e, DN &... dn);
		Panel(void);
		virtual ~Panel(void) = default;
	};
}

#endif
