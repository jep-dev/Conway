#include "runnable.hpp"

namespace Runnable {
	std::ostream& operator<<(std::ostream & os, e_task const& e) {
		switch(e) {
			case e_task::start: return os << "start";
			case e_task::pause: return os << "pause";
			case e_task::run:   return os << "run";
			case e_task::error: return os << "error";
			case e_task::quit:  return os << "quit";
			case e_task::pass:  return os << "pass";
			default:            return os << "unknown";
		}
	}
}
