#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <type_traits>
#include <functional>

template<typename S, typename... T>
struct none_true_t:
	std::true_type {};
template<typename... T>
struct none_true_t<std::true_type, T...>:
	std::false_type {};
template<typename... T>
struct none_true_t<std::false_type, T...>:
	none_true_t<T...> {};

template<typename T, typename S = std::false_type, T... TN>
struct none_true:
	none_true_t<S, std::integral_constant<bool, static_cast<bool>(TN)>...> {};

template<typename S = std::false_type, typename... T>
struct any_true_t:
	none_true_t<none_true_t<S, T...>> {};
template<typename T, typename S = std::false_type, T... TN>
struct any_true:
	none_true_t<none_true<T,S,TN...>> {};


#endif
