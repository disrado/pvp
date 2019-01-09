#pragma once

namespace db
{


template<typename T>
using ShPtr = std::shared_ptr<T>;

template<typename T>
using UnPtr = std::unique_ptr<T>;

template<typename T>
using WkPtr = std::weak_ptr<T>;

template<typename T>
using func = std::function<T>;


using ID = uint64_t;
using Timestamp = std::string;
using Escape = func<std::string(const std::string&)>;


} // namespace db