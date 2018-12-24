#pragma once

namespace utils
{


template<
	typename T,
	std::enable_if_t<std::is_integral<typename T::value_type>::value>* = nullptr
>
std::string JoinStrList(const T& list, const std::string& sep)
{
	std::string s{};
	
	for (auto i{ std::begin(list) }; i != std::end(list); ++i) {
		s += std::to_string(*i) + (i + 1 != std::end(list) ? sep : std::string());
	}

	return s;
}


template<
	typename T,
	std::enable_if_t<!std::is_integral<typename T::value_type>::value>* = nullptr
>
std::string JoinStrList(const T& list, const std::string& sep)
{
	std::string s{};
	
	for (auto i{ std::begin(list) }; i != std::end(list); ++i) {
		s += *i + (i + 1 != std::end(list) ? sep : std::string());
	}

	return s;
}


} // namespace std