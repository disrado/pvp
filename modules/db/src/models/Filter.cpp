#include "db/models/Filter.hpp"

namespace db
{


template<>
std::string Item<std::string>::ToSql(
	std::string_view column, const db::Escape escape, const std::string& op) const
{
	if (!m_isInitialized) {
		return "";
	}

	return fmt::format("{} {} '{}'", column, op, escape(m_value));
}


template<>
std::string ItemRange<std::string>::ToSql(std::string_view column, const db::Escape escape) const
{
	if (!m_isInitialized) {
		return "";
	}

	return fmt::format("{} {}BETWEEN '{}' AND '{}'",
		column,
		m_isInverted ? "NOT " : "",
		escape(m_from),
		escape(m_to)
	);
}


} // namespace db