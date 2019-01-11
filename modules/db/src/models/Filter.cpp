#include "db/models/Filter.hpp"

namespace db
{


template<>
std::string Item<std::string>::ToSql(std::string_view column, const db::Escape escape) const
{
	return fmt::format("{} {} '{}'",
		column,
		m_isInverted ? "!=" : "=",
		escape(m_value)
	);
}


template<>
std::string ItemRange<std::string>::ToSql(std::string_view column, const db::Escape escape) const
{
	const std::string from{ [this, &column, escape] () -> std::string {
		if (!m_from.IsInited()) {
			return "";
		}

		return fmt::format("{} {} '{}'",
			column,
			m_from.IsInverted() ? "<=" : ">=",
			escape(m_from.Value())
		);
	}() };

	const std::string to{ [this, &column, escape] () -> std::string {
		if (!m_from.IsInited()) {
			return "";
		}

		return fmt::format("{} {} '{}'",
			column,
			m_to.IsInverted() ? ">=" : "<=",
			escape(m_from.Value())
		);
	}() };

	return fmt::format("{}{}{}",
		from,
		(!from.empty() && !to.empty()) ? " AND " : "",
		to
	);
}


} // namespace db