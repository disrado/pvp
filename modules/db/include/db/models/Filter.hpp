#pragma once

#include "db/Aliases.hpp"

namespace db
{


template<typename T = std::string>
class Item final
{
public:
	Item(const T& value, const bool m_isInverted = false);
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

	std::string ToSql(std::string_view column) const;
	std::string ToSql(std::string_view column, const Escape escape) const;

private:
	T m_value;
	bool m_isInverted = false;
};


template<typename T = std::string>
class ItemRange final
{
public:
	ItemRange(T&& from, T&& to);

	ItemRange(const ItemRange&) = default;
	ItemRange& operator=(const ItemRange&) = default;

	ItemRange(ItemRange&&) = default;
	ItemRange& operator=(ItemRange&&) = default;

public:
	void From(const T& from);
	void To(const T& to);

	void From(const T&& from);
	void To(const T&& to);

	Item<T>& From() &;
	Item<T>&& From() &&;
	const Item<T>& From() const &;
	const Item<T>&& From() const &&;

	Item<T>& To() &;
	Item<T>&& To() &&;
	const Item<T>& To() const &;
	const Item<T>&& To() const &&;

public:
	std::string ToSql(std::string_view column) const;
	std::string ToSql(std::string_view, const Escape escape) const;

private:
	Item<T> m_from;
	Item<T> m_to;
};


template<typename T = std::string>
using ItemList = std::list<Item<T>>;


template<typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::string ToSql(const ItemList<T>& list, const std::string& column);

template<typename T, std::enable_if_t<!std::is_integral<T>::value>* = nullptr>
std::string ToSql(const ItemList<T>& list, const std::string& column, db::Escape escape);


} // namespace db


#include "../../../src/models/Filter.inl"