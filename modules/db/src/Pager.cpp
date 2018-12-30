#include "pch.hpp"

#include "db/Pager.hpp"
#include "db/TypeConversion.hpp"

namespace db
{


Pager::Pager(size_t limit, size_t offset, size_t count)
	: m_limit{ limit }
	, m_offset{ offset }
	, m_count{ count }
{}


void Pager::Limit(size_t limit)
{
	m_limit = limit;
}


void Pager::Offset(size_t offset)
{
	m_offset = offset;
}


void Pager::Count(size_t count)
{
	m_count = count;
}


size_t Pager::Limit()
{
	return m_limit;
}


size_t Pager::Offset()
{
	return m_offset;
}


size_t Pager::Count()
{
	return m_count;
}


std::string Pager::ToSql() const
{
	std::string sql;

	if (m_offset) {
		sql += "OFFSET " + ToStr(m_offset);
	}

	if (m_limit) {
		sql += sql.empty() ? "" : " ";
		sql += "LIMIT " + ToStr(m_limit);
	}

	return sql;
}


} // db
