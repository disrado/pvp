#include "pch.hpp"

#include "db/models/TypeConversion.hpp"

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


std::string ToStr(const bool status)
{
	return status ? "1" : "0";
}


bool BoolFromStr(const std::string& str)
{
	if (str == "1") {
		return true;
	} else {
		return false;
	}
}


} // namespace db