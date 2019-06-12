#pragma once

namespace utils
{


template<typename T>
std::string JoinStrList(const T& list, const std::string& sep) noexcept
{
	std::string s{};

	for (auto i{ std::begin(list) }; i != std::end(list); ++i) {
		if constexpr (std::is_integral<typename T::value_type>::value) {
			s += std::to_string(*i) + (std::distance(i, std::end(list)) == 1 ? "" : sep);
		} else {
			s += *i + (std::distance(i, std::end(list)) == 1 ? "" : sep);
		}
	}

	return s;
}


template<typename T>
std::string JoinStrList(const std::initializer_list<T>& list, const std::string& sep) noexcept
{
	std::string s{};

	for (auto i{ std::begin(list) }; i != std::end(list); ++i) {
		if constexpr (std::is_integral<T>::value) {
			s += std::to_string(*i) + (std::distance(i, std::end(list)) == 1 ? "" : sep);
		} else {
			s += *i + (std::distance(i, std::end(list)) == 1 ? "" : sep);
		}
	}

	return s;
}


} // namespace utils