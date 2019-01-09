#pragma once

namespace db
{


std::string ToStr(const bool value);
bool BoolFromStr(const std::string& str);

std::string ToStr(const size_t value);
size_t SizetFromStr(const std::string& str);


} // namespace db