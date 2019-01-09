#pragma once

#include "db/TypeConversion.hpp"

namespace db
{


template<typename T>
Item<T>::Item(const T& value, const bool isInverted)
	: m_value{ value }
	, m_isInverted{ isInverted }
{}


template<typename T>
Item<T>::Item(const T&& value, const bool isInverted)
	: m_value{ std::move(value) }
	, m_isInverted{ isInverted }
{}


template<typename T>
T& Item<T>::Value() &
{
	return m_value;
}


template<typename T>
T&& Item<T>::Value() &&
{
	return std::move(m_value);
}


template<typename T>
const T& Item<T>::Value() const &
{
	return m_value;
}


template<typename T>
const T&& Item<T>::Value() const &&
{
	return std::move(m_value);
}


template<typename T>
void Item<T>::Invert(const bool isInverted)
{
	m_isInverted = isInverted;
}


template<typename T>
bool Item<T>::IsInverted() const
{
	return m_isInverted;
}


template<typename T>
std::string Item<T>::ToSql(std::string_view column) const
{
	return fmt::format("{} {} {}",
		column,
		m_isInverted ? "!=" : "==",
		ToStr(m_value)
	);
}


template<typename T>
ItemRange<T>::ItemRange(T&& from, T&& to)
	: m_from{ std::forward<T>(from) }
	, m_to{ std::forward<T>(to) }
{}


template<typename T>
Item<T>& ItemRange<T>::From() &
{
	return m_to;
}


template<typename T>
Item<T>&& ItemRange<T>::From() &&
{
	return std::move(m_to);
}


template<typename T>
const Item<T>& ItemRange<T>::From() const &
{
	return m_to;
}


template<typename T>
const Item<T>&& ItemRange<T>::From() const &&
{
	return std::move(m_to);
}


template<typename T>
Item<T>& ItemRange<T>::To() &
{
	return m_to;
}


template<typename T>
Item<T>&& ItemRange<T>::To() &&
{
	return std::move(m_to);
}


template<typename T>
const Item<T>& ItemRange<T>::To() const &
{
	return m_to; 
}


template<typename T>
const Item<T>&& ItemRange<T>::To() const &&
{
	return std::move(m_to);
}


template<typename T>
void ItemRange<T>::From(const T& from)
{
	m_from = from;
}


template<typename T>
void ItemRange<T>::To(const T& to)
{
	m_to = to;
}


template<typename T>
void ItemRange<T>::From(const T&& from)
{
	m_from = from;
}


template<typename T>
void ItemRange<T>::To(const T&& to)
{
	m_to = to;
}


template<typename T>
std::string ItemRange<T>::ToSql(std::string_view column) const
{
	return fmt::format("{} {} {} AND {} {} {}",
		column,
		m_from.IsInverted() ? "<=" : ">=",
		ToStr(m_from.Value()),
		column,
		m_to.IsInverted() ? ">=" : "<=",
		ToStr(m_to.Value())
	);
}


template<typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::string ToSql(const ItemList<T>& list, const std::string& column)
{
	if (list.empty()) {
		return "";
	}

	std::vector<std::string> sql(list.size());

	for(auto&& item : list) {
		sql.push_back(item.ToSql(column));
	}

	return utils::JoinStrList(sql, " AND ");
}


template<typename T, std::enable_if_t<!std::is_integral<T>::value>* = nullptr>
std::string ToSql(const ItemList<T>& list, const std::string& column, db::Escape escape)
{
	if (list.empty()) {
		return "";
	}

	std::vector<std::string> sql(list.size());

	for(auto&& item : list) {
		sql.push_back(item.ToSql(column, escape));
	}

	return utils::JoinStrList(sql, " AND ");
}


} // namespace db