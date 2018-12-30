#pragma once

#include "db/Aliases.hpp"

namespace db
{


template<typename T = std::string>
class Value final
{
public:
	Value(const T&& value, const bool m_isInverted = false);

	Value(const Value&) = default;
	Value& operator=(const Value&) = default;

	Value(Value&&) = default;
	Value& operator=(Value&&) = default;

public:
	const T& Get() const;
	void Set(const T&& value);
	void Invert(const bool isInverted);
	bool IsInverted() const;

private:
	T m_value;
	bool m_isInverted = false;
};


template<typename T = std::string>
class Item final
{
public:
	using Escape = func<std::string(const std::string&)>;

public:
	Item();
	Item(const std::initializer_list<T>&& list);

	Item(const Item&) = default;
	Item& operator=(const Item&) = default;

	Item(Item&&) = default;
	Item& operator=(Item&&) = default;

public:
	const std::list<Value<T>>& Get() const;
	void Add(const Value<T>&& value);
	void Remove(const Value<T>&& value);
	void Clear();
	bool IsEmpty() const;
	size_t Size() const;
	
	std::string ToSql(const std::string& column, const Escape& escape) const;

private:
	std::list<Value<T>> m_list;
};


template<typename T = std::string>
class Range final
{
public:
	using Escape = func<std::string(const std::string&)>;
	
public:
	Range(const T&& from, const T&& to);

	Range(const Range&) = default;
	Range& operator=(const Range&) = default;

	Range(Range&&) = default;
	Range& operator=(Range&&) = default;

public:
	const T& From() const;
	const T& To() const;
	void From(const T&& from);
	void To(const T&& to);

	std::string ToSql(const std::string& column, const Escape& escape) const;

private:
	Value<T> m_from;
	Value<T> m_to;
};


} // namespace db