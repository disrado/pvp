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

private:
	T m_value;
	bool m_isInverted = false;
};


template<typename T = std::string>
class ItemRange final
{
public:
	ItemRange(const T&& from, const T&& to);

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

private:
	Item<T> m_from;
	Item<T> m_to;
};


template<typename T = std::string>
using ItemList = std::list<Item<T>>;


template<typename T>
std::string ToSql(const Item<T>& item, std::string_view col)
{
	return fmt::format("{} {} {}",
		col,
		item.IsInverted() ? "!=" : "==",
		utils::ToStr(item.Value())
	);
}


std::string ToSql(const Item<std::string>& item, std::string_view col, const Escape& escape)
{
	return fmt::format("{} {} {}",
		col,
		item.IsInverted() ? "!=" : "==",
		escape(item.Value())
	);
}


template<typename T>
std::string ToSql(const ItemRange<T>& range, std::string_view col, const Escape& escape)
{
	return fmt::format("{} {} {} AND {} {} {}",
		col,
		range.From().IsInverted() ? "<=" : ">=",
		utils::ToStr(range.From().Value()),
		col,
		range.To().IsInverted() ? ">=" : "<=",
		utils::ToStr(range.To().Value())
	);
}


std::string ToSql(const ItemRange<std::string>& range, std::string_view col, const Escape& escape)
{
	return fmt::format("{} {} {} AND {} {} {}",
		col,
		range.From().IsInverted() ? "<=" : ">=",
		escape(range.From().Value()),
		col,
		range.To().IsInverted() ? ">=" : "<=",
		escape(range.To().Value())
	);
}


template<template<typename ContainerT> typename Container>
std::string ToSql(const Container<Item<std::string>>&& list, std::string_view col)
{
	if (list.empty()) {
		return "";
	}

	std::vector<std::string> sql(list.size());

	for (const auto& item : list) {
		sql.push_back(ToSql(item, col));
	}

	return utils::JoinStrList(sql, " AND ");
}


template<
	template<typename ContainerT> typename Container,
	typename ItemType
>
std::string ToSql(
	const Container<Item<ItemType>>&& list,
	std::string_view col,
	const Escape& escape)
{
	if (list.empty()) {
		return "";
	}

	std::vector<std::string> sql(list.size());

	for (const auto& item : list) {
		sql.push_back(ToSql(item, col, escape));
	}

	return utils::JoinStrList(sql, " AND ");
}


} // namespace db