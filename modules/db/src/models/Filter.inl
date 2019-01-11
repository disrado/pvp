#pragma once

#include "db/TypeConversion.hpp"

namespace db
{


template<typename T>
Item<T>::Item(const T& value, const bool isInverted)
	: m_value{ value }
	, m_isInverted{ isInverted }
	, m_isInitialized{ true }
{}


template<typename T>
Item<T>::Item(const T&& value, const bool isInverted)
	: m_value{ std::move(value) }
	, m_isInverted{ isInverted }
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
bool Item<T>::IsInited() const
{
	return m_isInitialized;
}


template<typename T>
std::string Item<T>::ToSql(std::string_view column) const
{
	if (!m_isInitialized) {
		return "";
	}

	return fmt::format("{} {} '{}'",
		column,
		m_isInverted ? "!=" : "=",
		ToStr(m_value)
	);
}


template<typename T>
ItemRange<T>::ItemRange(const T& from, const T& to)
	: m_from{ from }
	, m_to{ to }
{}


template<typename T>
ItemRange<T>::ItemRange(const T&& from, const T&& to)
	: m_from{ std::move(from) }
	, m_to{ std::move(to) }
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
	const std::string from{ [this, &column] {
		if (!m_from.IsInited()) {
			return "";
		}

		return fmt::format("{} {} '{}'",
			column,
			m_from.IsInverted() ? "<=" : ">=",
			ToStr(m_from.Value())
		);
	}() };

	const std::string to{ [this, &column] {
		if (!m_from.IsInited()) {
			return "";
		}

		return fmt::format("{} {} '{}'",
			column,
			m_to.IsInverted() ? ">=" : "<=",
			ToStr(m_from.Value())
		);
	}() };

	return fmt::format("{}{}{}",
		from,
		(!from.empty() && !to.empty()) ? " AND " : "",
		to
	);
}

template<typename T>
bool ItemRange<T>::IsInited() const
{
	return m_from.IsInited() || m_to.IsInited();
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