#include "pch.hpp"

#include "db/models/Filter.hpp"

namespace db
{


template<typename T>
Value<T>::Value(const T&& value, const bool isInverted)
	: m_value{ value }
	, m_isInverted{ isInverted }
{}


template<typename T>
const T& Value<T>::Get() const
{
	return m_value;
}


template<typename T>
void Value<T>::Set(const T&& value)
{
	m_value = value;
}


template<typename T>
void Value<T>::Invert(const bool isInverted)
{
	m_isInverted = isInverted;
}


template<typename T>
bool Value<T>::IsInverted() const
{
	return m_isInverted;
}


template<typename T>
Item<T>::Item()
	: m_list{ std::list<T>{} }
{}


template<typename T>
Item<T>::Item(const std::initializer_list<T>&& list)
	: m_list{ std::list<T>{ begin(list), std::end(list) } }
{}


template<typename T>
const std::list<Value<T>>& Item<T>::Get() const
{
	return m_list;
}


template<typename T>
void Item<T>::Add(const Value<T>&& value)
{
	m_list.push_back(value);
}


template<typename T>
void Item<T>::Remove(const Value<T>&& value)
{
	if (auto res{ m_list.find(value) }; res != std::end(m_list)) {
		m_list.erase(res);
	}
}


template<typename T>
void Item<T>::Clear()
{
	m_list.clear();
}


template<typename T>
bool Item<T>::IsEmpty() const
{
	return m_list.empty();
}


template<typename T>
size_t Item<T>::Size() const
{
	return m_list.size();
}


template<typename T>
std::string Item<T>::ToSql(const std::string& column, const Escape& escape) const
{
	if (IsEmpty()) {
		return "";
	}

	std::vector<std::string> sql(m_list.size());

	for (const auto& item : m_list)
	{
		constexpr bool isIntegral{ std::is_integral<typename T::value_type>::value };

		sql.push_back(fmt::format("{} {} {}",
			column,
			item.IsInverted() ? "!=" : "==",
			isIntegral ? ToStr(item.value) : escape(item.value)
		));
	}

	return utils::JoinStrList(sql, " AND ");
}


template<typename T>
Range<T>::Range(const T&& from, const T&& to)
	: m_from{ std::forward<T>(from) }
	, m_to{ std::forward<T>(to) }
{}


template<typename T>
const T& Range<T>::From() const
{
	return m_from;
}


template<typename T>
const T& Range<T>::To() const
{
	return m_from;
}


template<typename T>
void Range<T>::From(const T&& from)
{
	m_from = from;
}


template<typename T>
void Range<T>::To(const T&& to)
{
	m_to = to;
}


template<typename T>
std::string Range<T>::ToSql(const std::string& column, const Escape& escape) const
{
	constexpr bool isIntegral{ std::is_integral<typename T::value_type>::value };

	return fmt::format("{} {} {} AND {} {} {}",
		column,
		m_from.IsInverted() ? "<=" : ">=",
		isIntegral ? ToStr(m_from.value) : escape(m_from.value),
		column,
		m_to.IsInverted() ? ">=" : "<=",
		isIntegral ? ToStr(m_to.value) : escape(m_to.value)
	);
}


} // namespace db