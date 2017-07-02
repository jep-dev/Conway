#ifndef VIEW_PANEL_HPP
#define VIEW_PANEL_HPP

#include "runnable.hpp"

namespace View {
	/** @brief A partition of a canvas */
	struct Panel : public Runnable {
		virtual bool poll(void);
		virtual bool run(void);
		/** @brief Constructor */
		Panel(void);
		/** @brief Descructor */
		virtual ~Panel(void);
	};
}

#endif
