#include "pch.hpp"

#include "db/TypeConversion.hpp"

namespace db
{


std::string ToStr(const AccountStatus& status)
{
	switch(status)
	{
		case AccountStatus::ACTIVE: return "ACTIVE";
		case AccountStatus::DISABLED: return "DISABLED";
		default: throw std::runtime_error{ "Bad cast" };
	}
}


AccountStatus AccountStatusFromStr(const std::string& str)
{
	if (str == "ACTIVE") {
		return AccountStatus::ACTIVE;
	} else if (str == "DISABLED") {
		return AccountStatus::DISABLED;
	} else {
		throw std::runtime_error{ "Bad cast" };
	}
}


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


} // namespace db