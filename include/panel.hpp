#ifndef VIEW_PANEL_HPP
#define VIEW_PANEL_HPP

#include "view.hpp"

namespace View {
	struct Panel: Runnable::TaskBase<Panel> {
		template<typename... DN>
		e_task call(e_task e, DN &... dn);
		Panel(void);
		virtual ~Panel(void) = default;
	};
}

#endif
