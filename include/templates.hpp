#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <type_traits>
#include <typeinfo>
#include <string>

/* Type introspection for template troubleshooting */
#ifdef __GNUG__
#include <cstdlib>
#include <cxxabi.h>
#include <memory>

/* Use abi when available to get legible names. Consider wrapping these in
   functions or lambdas for portability, instead of multiple statements
   hidden behind a macro. */
#define DEMANGLE(X, Y) \
	int status = 0; \
	std::unique_ptr<char, void (*)(void*)> demangled \
	{ abi::__cxa_demangle(Y, NULL, NULL, &status), std::free }; \
		X << Y << " / " << (status ? Y : demangled.get())
#else
/*  Otherwise default to get mangled names (e.g. std::cout -> So).
	Try post hoc object file introspection using nm or equivalent if this
	implementation is chosen by your compiler. */
#define DEMANGLE(X, Y) X << Y
#endif

/** @brief Print (stream insert) the names of the given types.
  @tparam T The sequence of types to print.
  @tparam S The type of the destination stream.
  @param s The destination (potentially standard output or a log file).
  @return The destination stream after insertion. */
template<typename... T, typename S>
S& get_types (S &s) {
	for(auto && name : {typeid(T).name()...}) {
		DEMANGLE(s, name) << "; ";
	}
	return s;
}

struct reductor {
	template<typename T, T DEF, T... TN>
	struct reduce_or;
	template<typename T, T DEF, T... TN>
	struct reduce_or:
		std::integral_constant<T, DEF> {};
	template<typename T, T DEF, T T1, T... TN>
	struct reduce_or<T, DEF, T1, TN...>:
		std::integral_constant<T, T1
			| reduce_or<T, DEF, TN...>::value> {};
};

#endif
