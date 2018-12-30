#pragma once

#include "db/Aliases.hpp"

namespace db
{


template<typename T = std::string>
class Value
{
public:
	Value(T&& value, bool m_isInverted = false);

	Value(const Value&) = default;
	Value& operator=(const Value&) = default;

	Value(Value&&) = default;
	Value& operator=(Value&&) = default;

public:
	T Get() const;
	bool IsInverted() const;

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
	explicit Item(const Value<T> value);
	Item(std::initializer_list<T> list);

	Item(const Item&) = default;
	Item& operator=(const Item&) = default;

	Item(Item&&) = default;
	Item& operator=(Item&&) = default;

public:
	std::list<Value<T>> Get() const;
	std::string ToSql(const std::string& column, Escape escape) const;

private:
	std::list<Value<T>> list;
};


template<typename T = std::string>
class Range
{
public:
	using Escape = func<std::string(const std::string&)>;
	
public:
	Range(T&& from, T&& to);

	Range(const Range&) = default;
	Range& operator=(const Range&) = default;

	Range(Range&&) = default;
	Range& operator=(Range&&) = default;

public:
	T From() const;
	T To() const;
	std::string ToSql(const std::string& column, Escape escape) const;

private:
	Value<T> m_from;
	Value<T> m_to;
};


} // namespace db