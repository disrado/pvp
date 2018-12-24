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
Item<T>::Item(const Value<T> value)
	: list{ std::list<T>{ value } }
{}


template<typename T>
Item<T>::Item(std::initializer_list<T> list)
	: list{ std::list<T>{ list.begin(), list.end() } }
{}


template<typename T>
Item<T>::Item()
	: list{ std::list<T>{} }
{}


template<typename T>
ItemRange<T>::ItemRange(T&& from, T&& to)
	: m_from{ std::forward<T>(from) }
	, m_to{ std::forward<T>(to) }
{}


template<typename T>
T ItemRange<T>::From() const
{
	return m_from;
}


template<typename T>
T ItemRange<T>::To() const
{
	return m_from;
}


template<typename T>
std::string Item<T>::ToSql(const std::string& key, Escape escape) const
{
	if (list.empty()) {
		return "";
	}

	std::vector<std::string> sql(list.size());

	for (const auto& item : list)
	{
		const auto operation{ item.isInverted ? "!=" : "==" };

		if (std::is_integral<typename T::value_type>::value) {
			fmt::format("{} {} {}", key, operation, ToStr(item.value));
		} else {
			fmt::format("{} {} {}", key, operation, escape(item.value));
		}
	}

	return utils::JoinStrList(sql, " AND ");
}


} // namespace db