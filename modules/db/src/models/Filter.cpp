#include "db/models/Filter.hpp"

namespace db
{


template<>
std::string Item<std::string>::ToSql(std::string_view column, const db::Escape escape) const
{
	return fmt::format("{} {} {}",
		column,
		m_isInverted ? "!=" : "==",
		escape(m_value)
	);
}


template<>
std::string ItemRange<std::string>::ToSql(std::string_view column, const db::Escape escape) const
{
	return fmt::format("{} {} {} AND {} {} {}",
		column,
		m_from.IsInverted() ? "<=" : ">=",
		escape(m_from.Value()),
		column,
		m_to.IsInverted() ? ">=" : "<=",
		escape(m_to.Value())
	);
}


} // namespace db