#pragma once

#include "db/Aliases.hpp"

namespace db
{


template<typename T = std::string>
class Value
{
public:
	Value() = default;
	Value(T&& value, bool m_isInverted = false);

private:
	T value;
	bool isInverted = false;
};


template<typename T = std::string>
class Item
{
public:
	using Escape = func<std::string(const std::string&)>;

public:
	Item();
	explicit Item(const Value<T> list);
	Item(std::initializer_list<T> list);

public:
	std::string ToSql(const std::string& key, Escape escape) const;

public:
	std::list<Value<T>> list;
};


template<typename T = std::string>
class ItemRange
{
public:
	ItemRange(T&& from, T&& to);

public:
	T From() const;
	T To() const;

private:
	Value<T> m_from;
	Value<T> m_to;
};


} // namespace db