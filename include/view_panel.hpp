#ifndef VIEW_PANEL_HPP
#define VIEW_PANEL_HPP

#include "runnable.hpp"

namespace View {
	struct Panel : public Runnable {
		virtual bool poll(void);
		virtual bool run(void);
		Panel(void);
		virtual ~Panel(void);
	};
}

#endif
