#include "pch.hpp"

#include "db/models/Filter.hpp"

namespace db
{


template<typename T>
Value<T>::Value(T&& value, bool isInverted)
	: value{ value }
	, isInverted{ isInverted }
{}


template<typename T>
T Value<T>::Get() const
{
	return value;
}


template<typename T>
bool Value<T>::IsInverted() const
{
	return isInverted;
}


template<typename T>
Item<T>::Item()
	: list{ std::list<T>{} }
{}


template<typename T>
Item<T>::Item(const Value<T> value)
	: list{ std::list<T>{ value } }
{}


template<typename T>
Item<T>::Item(std::initializer_list<T> list)
	: list{ std::list<T>{ list.begin(), list.end() } }
{}


template<typename T>
std::list<Value<T>> Item<T>::Get() const
{
	return list;
}


template<typename T>
std::string Item<T>::ToSql(const std::string& column, Escape escape) const
{
	if (list.empty()) {
		return "";
	}

	std::vector<std::string> sql(list.size());

	for (const auto& item : list)
	{
		const bool isIntegral{ std::is_integral<typename T::value_type>::value };

		sql.push_back(fmt::format("{} {} {}",
			column,
			item.IsInverted() ? "!=" : "==",
			isIntegral ? ToStr(item.value) : escape(item.value)
		));
	}

	return utils::JoinStrList(sql, " AND ");
}


template<typename T>
Range<T>::Range(T&& from, T&& to)
	: m_from{ std::forward<T>(from) }
	, m_to{ std::forward<T>(to) }
{}


template<typename T>
T Range<T>::From() const
{
	return m_from;
}


template<typename T>
T Range<T>::To() const
{
	return m_from;
}


template<typename T>
std::string Range<T>::ToSql(const std::string& column, Escape escape) const
{
	const bool isIntegral{ std::is_integral<typename T::value_type>::value };

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