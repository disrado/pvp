#pragma once 


namespace db
{


class Pager
{

public:
	Pager(size_t limit = 0, size_t offset = 0, size_t count = 0);


public:
	void Limit(size_t limit);
	void Offset(size_t offset);
	void Count(size_t count);

	size_t Limit();
	size_t Offset();
	size_t Count();

	std::string ToSql() const;

private:
	size_t m_limit;
	size_t m_offset;
	size_t m_count;
};


} // namespace db