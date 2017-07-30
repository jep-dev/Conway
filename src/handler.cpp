#include "handler.hpp"

namespace Runnable {
	template<typename D, typename SUBJ, typename... OBJS>
	Signal HandlerCRTP<D,SUBJ,OBJS...>
	::handle(Signal sig, SUBJ & subj, OBJS &... objs) {
		return static_cast<D*>(this) -> handle(sig, subj, objs...);
	}
}
