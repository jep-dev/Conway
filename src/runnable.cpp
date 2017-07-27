#include "runnable.hpp"

namespace Runnable {
	std::ostream& operator<<(std::ostream & os, Signal const& s) {
		auto matches = 0;
		for(auto it : {Signal::Quit, Signal::Fail, Signal::Pass,
				Signal::Yield, Signal::Start}) {
			if(s & it) {
				matches++;
				if(matches > 1) os << ',';
				switch(s) {
					case Quit: os << "Quit";
					case Fail: os << "Fail";
					case Pass: os << "Pass";
					case Yield: os << "Yield";
					case Start: os << "Start";
				}
			}
		}
		/* switch(e) {
			case e_task::start: return os << "start";
			case e_task::pause: return os << "pause";
			case e_task::run:   return os << "run";
			case e_task::error: return os << "error";
			case e_task::quit:  return os << "quit";
			case e_task::pass:  return os << "pass";
			default:            return os << "unknown";
		} */
	}
}
