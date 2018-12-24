#pragma once

#include "db/models/Account.hpp"

namespace db
{


std::string ToStr(const AccountStatus& status);
AccountStatus AccountStatusFromStr(const std::string& str);


std::string ToStr(const bool status);
bool BoolFromStr(const std::string& str);


} // namespace db