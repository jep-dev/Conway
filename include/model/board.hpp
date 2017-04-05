#ifndef BOARD_HPP
#define BOARD_HPP

namespace Model {
	// TODO choose data structure for cell storage
	struct Board {
		/** Toggle the state of a single cell.
		  @param x X coordinate
		  @param y Y coordinate */
		void toggle(int x, int y);
		/** Check the state of a single cell.
		  @param x X coordinate
		  @param y Y coordinate
		  @return True if and only if the cell is alive */
		bool query(int x, int y);
		/** Constructor */
		Board(void);
		/** Destructor */
		virtual ~Board(void);
	};
}

#endif
