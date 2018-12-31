#pragma once

#include "db/Aliases.hpp"

namespace db
{


template<typename T = std::string>
class Item final
{
public:
	Item(const T&& value, const bool m_isInverted = false);

	Item(const Item&) = default;
	Item& operator=(const Item&) = default;

	Item(Item&&) = default;
	Item& operator=(Item&&) = default;

public:
	T& Value() &;
	T&& Value() &&;
	const T& Value() const &;
	const T&& Value() const &&;
	
	void Invert(const bool isInverted);
	bool IsInverted() const;

private:
	T m_value;
	bool m_isInverted = false;
};


template<typename T = std::string>
class ItemList final
{
public:
	using Escape = func<std::string(const std::string&)>;

public:
	ItemList();
	ItemList(const std::initializer_list<T>&& list);

	ItemList(const ItemList&) = default;
	ItemList& operator=(const ItemList&) = default;

	ItemList(ItemList&&) = default;
	ItemList& operator=(ItemList&&) = default;

public:
	T& Value() &;
	T&& Value() &&;
	const T& Value() const &;
	const T&& Value() const &&;

	void Add(const T& value);
	void Add(const T&& value);

	void Remove(const T& value);
	void Remove(const T&& value);

	void Clear();
	
	bool IsEmpty() const;
	size_t Size() const;
	
	std::string ToSql(const std::string& column, const Escape& escape) const;

private:
	std::list<Item<T>> m_list;
};


template<typename T = std::string>
class ItemRange final
{
public:
	using Escape = func<std::string(const std::string&)>;
	
public:
	ItemRange(const T&& from, const T&& to);

	ItemRange(const ItemRange&) = default;
	ItemRange& operator=(const ItemRange&) = default;

	ItemRange(ItemRange&&) = default;
	ItemRange& operator=(ItemRange&&) = default;

public:
	const T& From() const;
	const T& To() const;

	void From(const T&& from);
	void To(const T&& to);

	std::string ToSql(const std::string& column, const Escape& escape) const;

private:
	Item<T> m_from;
	Item<T> m_to;
};


} // namespace db