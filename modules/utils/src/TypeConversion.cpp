#include "pch.hpp"

#include "utils/TypeConversion.hpp"


namespace utils
{


std::string ToStr(const bool value)
{
	return value ? "1" : "0";
}


bool BoolFromStr(const std::string& str)
{
	if (str == "1") {
		return true;
	} else {
		return false;
	}
}


std::string ToStr(const size_t value)
{
	return std::to_string(value);
}


size_t SizetFromStr(const std::string& str)
{
	size_t result;

	std::istringstream stream(str);
	stream >> result;

	return result;
}


} // namespace utils
