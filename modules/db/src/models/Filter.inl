#pragma once

#include "db/TypeConversion.hpp"

namespace db
{


template<typename T>
Item<T>::Item(const T& value)
	: m_value{ value }
	, m_isInitialized{ true }
{}


template<typename T>
Item<T>::Item(const T&& value)
	: m_value{ std::move(value) }
	, m_isInitialized{ true }
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
bool Item<T>::IsInited() const
{
	return m_isInitialized;
}


template<typename T>
std::string Item<T>::ToSql(std::string_view column, const std::string& op) const
{
	if (!m_isInitialized) {
		return "";
	}

	return fmt::format("{} {} '{}'", column, op, ToStr(m_value));
}


template<typename T>
ItemRange<T>::ItemRange(const T& from, const T& to, const bool invert)
	: m_from{ from }
	, m_to{ to }
	, m_isInverted{ invert }
	, m_isInitialized { true }
{}


template<typename T>
ItemRange<T>::ItemRange(const T&& from, const T&& to, const bool invert)
	: m_from{ std::move(from) }
	, m_to{ std::move(to) }
	, m_isInverted{ invert }
	, m_isInitialized { true }
{}


template<typename T>
T& ItemRange<T>::From() &
{
	return m_from;
}


template<typename T>
T&& ItemRange<T>::From() &&
{
	return std::move(m_from);
}


template<typename T>
const T& ItemRange<T>::From() const &
{
	return m_from;
}


template<typename T>
const T&& ItemRange<T>::From() const &&
{
	return std::move(m_from);
}


template<typename T>
T& ItemRange<T>::To() &
{
	return m_to;
}


template<typename T>
T&& ItemRange<T>::To() &&
{
	return std::move(m_to);
}


template<typename T>
const T& ItemRange<T>::To() const &
{
	return m_to; 
}


template<typename T>
const T&& ItemRange<T>::To() const &&
{
	return std::move(m_to);
}


template<typename T>
std::string ItemRange<T>::ToSql(std::string_view column) const
{
	if (!m_isInitialized) {
		return "";
	}

	return fmt::format("{} {}BETWEEN '{}' AND '{}'",
		column,
		m_isInverted ? "NOT " : "",
		ToStr(m_from),
		ToStr(m_to)
	);
}


template<typename T>
void ItemRange<T>::Invert()
{
	m_isInverted = !m_isInverted;
}


template<typename T>
bool ItemRange<T>::IsInverted() const
{
	return m_isInverted;
}


template<typename T>
bool ItemRange<T>::IsInited() const
{
	return m_isInitialized;
}


template<typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::string ToSql(const ItemList<T>& list, const std::string& column)
{
	if (list.empty()) {
		return "";
	}

	std::vector<std::string> sql;
	sql.reserve(list.size());

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

	std::vector<std::string> sql;
	sql.reserve(list.size());

	for(auto&& item : list) {
		sql.push_back(item.ToSql(column, escape));
	}

	return utils::JoinStrList(sql, " AND ");
}


} // namespace db