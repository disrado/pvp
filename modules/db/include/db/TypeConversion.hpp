#pragma once

#include "db/models/Account.hpp"

namespace db
{


std::string ToStr(const AccountStatus& status);
AccountStatus AccountStatusFromStr(const std::string& str);

std::string ToStr(const bool value);
bool BoolFromStr(const std::string& str);

std::string ToStr(const size_t value);
size_t SizetFromStr(const std::string& str);


} // namespace db