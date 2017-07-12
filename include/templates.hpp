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

/** @brief Defines value as true if the given type's value is equivalent to true.
  @tparam T The given type with value typedef convertible to boolean. */
template<typename T> struct is_true;

/** @brief True type unless one of the given values is equivalent to true.
  @tparam T The type of the given values to be inspected.
  @tparam TN the values to be inspected. */
template<typename T, T... TN> struct none_true;

/** @brief True type unless one of the given types is interpreted as true.
  @tparam TN the types to be interpreted as booleans. */
template<typename... TN> struct none_true_t;

/** @brief True type unless the match of any given type is interpreted as true.
  @tparam TT The match template applied to each given type for interpretation.
  @tparam T1 The first type to match.
  @tparam TN The remainder of the types to match. */
template<template<typename...> class TT,
	typename T1, typename... TN> struct none_match_tt;

/** @brief True type unless the given type is a member of the given type sequence.
  @tparam T1 The type to find in the type sequence.
  @tparam TN The sequence of types. */
template<typename T1, typename... TN> struct none_same_t;

/** @brief True type unless any member of the given sequence is derived from
  given type.
  @tparam T1 The type to find in the type sequence.
  @tparam TN The sequence of types. */
template<typename T1, typename... TN> struct none_base_t;

/** @brief True type unless the given value is a member of the value sequence.
  @tparam T The type of all subsequent values.
  @tparam T1 The value to find in the value sequence.
  @tparam TN The sequence of values. */
template<typename T, T T1, T... TN> struct none_match_t;

/** @copybrief is_true
  @see is_true */
template<typename T, T T1>
struct is_true<std::integral_constant<T,T1>>:
	std::integral_constant<bool, static_cast<bool>(T1)> {};
/** @copybrief is_true
  @see is_true */
template<bool T1>
struct is_true<std::integral_constant<bool, T1>>:
	std::integral_constant<bool, T1> {};

/** @copybrief none_true
  @see none_true */
template<bool... TN>
struct none_true<bool, TN...>:
	std::true_type {};
/** @copybrief none_true
  @see none_true */
template<bool... TN>
struct none_true<bool, true, TN...>:
	std::false_type {};
/** @copybrief none_true
  @see none_true */
template<bool... TN>
struct none_true<bool, false, TN...>:
	none_true<bool, TN...> {};
template<typename T, T... TN>
struct none_true:
	none_true<bool, static_cast<bool>(TN)...> {};

template<typename... TN>
struct none_true_t:
	none_true<bool, is_true<TN>::value...> {};

template<template<typename...> class TT,
	typename T1, typename... TN>
struct none_match_tt:
	none_true_t<typename TT<T1,TN>::type...> {};

template<typename T1, typename... TN>
struct none_same_t:
	none_match_tt<std::is_same, T1, TN...> {};

template<typename T1, typename... TN>
struct none_base_t:
	none_match_tt<std::is_base_of, T1, TN...> {};

template<typename T, T T1, T... TN>
struct none_match_t:
	none_match_tt<std::is_same,
		std::integral_constant<T, T1>,
		std::integral_constant<T, TN>...> {};

#endif
