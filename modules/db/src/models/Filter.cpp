#include "pch.hpp"

#include "db/models/Filter.hpp"

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
std::string Item<T>::ToSql(std::string_view column, const Escape& escape) const
{
	constexpr bool isIntegral{ std::is_integral<typename T::value_type>::value };

	return fmt::format("{} {} {}",
		column,
		m_isInverted ? "!=" : "==",
		isIntegral ? ToStr(m_value) : (escape ? escape(m_value) : m_value)
	);
}


template<typename T>
ItemRange<T>::ItemRange(const T&& from, const T&& to)
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
std::string ItemRange<T>::ToSql(std::string_view column, const Escape& escape) const
{
	constexpr bool isIntegral{ std::is_integral<typename T::value_type>::value };

	return fmt::format("{} {} {} AND {} {} {}",
		column,
		m_from.IsInverted() ? "<=" : ">=",
		isIntegral ? ToStr(m_from.Value()) : (escape ? escape(m_from.Value()) : m_from.Value()),
		column,
		m_to.IsInverted() ? ">=" : "<=",
		isIntegral ? ToStr(m_to.Value()) : (escape ? escape(m_to.Value()) : m_to.Value())
	);
}


} // namespace db