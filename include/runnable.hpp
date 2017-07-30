#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

// Standard library
#include <cstdint>
#include <iostream> // TODO Use iosfwd

namespace Runnable {
	/** @brief Signals used by Runnable types, generally named relative to the
	  life cycle of the type receiving them. */
	enum Signal : uint8_t {
		Quit     =    0b00000001,
		Fail     =    0b00000010,
		Pass     =    0b00000100,
		Yield    =    0b00001000,
		Start    =    0b00010000,
		Abort    =  Quit |  Fail,
		Done     =  Quit |  Pass,
		Throw    =  Fail | Yield,
		Catch    =  Fail | Start,
		Restart  =  Done | Start,
		Continue = Yield | Start,
		Retry    = Throw | Start
	};
	std::ostream& operator<<(std::ostream &os, Signal const& s);

	/** @brief Maps signals to form loops and other structures; uses the
	 given function on its arguments when mapping the 'start' signal.
	 Soon to be deprecated.
	 @tparam D The arguments into the Driver; other operands may be bound
	 to the function instead. */
	template<typename... D> struct Driver;

	/** @brief Template 'task' interface/trait; derived behavior is resolved.
	  through CRTP instead of virtual methods.
	  @tparma D The derived type providing implementation.
	  @tparam DN The arguments into the interface method. */
	template<typename D, typename... DN> struct TaskBase;

	// Specialization of HandlerCRTP that prepends const SDL_Event to OBJS
	/** @brief A handler of a given subject (event, etc.) as a task.
	  @tparam D The derived type providing implementation.
	  @tparam SUBJ The subject type, context for the handler logic.
	  @tparam OBJS The object types, potentially argands of the operation or
	  delegate handlers based on the given subject. */
	template<typename D, typename SUBJ, typename... OBJS> struct HandlerCRTP;

	/** @brief A specialization prepending an event to the argands of
	  HandlerCRTP.
	  @tparam EXACT Implies that context matching is strict instead of 'fuzzy'.
	  @tparam ID The ID of the context to match. If EXACT is false, then both
	  the ID and the subject type may be masked before comparison.
	  @tparam D The derived type providing implementatino.
	  @tparam SUBJ The subject type of the operation.
	  @tparam OBJS The object types of the operation. */
	template<bool EXACT, uint32_t ID, typename D,
		typename SUBJ, typename... OBJS> struct EventHandlerCRTP;

	/** @brief Collection of EventHandler types invariant over their arguments.
	  @tparam SUBJ The subject type of the operation.
	  @tparam OBJS The object types of the operation. */
	template<typename SUBJ, typename... OBJS> struct EventHandlers;
}

#include "task.hpp"
#include "driver.hpp"
#include "handler.hpp"

#endif
