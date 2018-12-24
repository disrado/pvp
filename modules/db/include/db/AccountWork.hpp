#pragma once


namespace db
{


class AccountWork : public flm::db::Worker
{
public:
	size_t Count();
	
};


} // namespace db;