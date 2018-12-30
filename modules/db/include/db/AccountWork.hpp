#pragma once

#include "db/Pager.hpp"
#include "db/models/Account.hpp"

namespace db
{


class AccountWork : public flm::db::Worker
{
public:
	UnPtr<Account> Insert(const Account& acc) const;
	Accounts Select(const Account::Filter& filter, const Pager pager) const;
	UnPtr<Account> Update(const db::ID id, const ShPtr<Account> acc) const;
	bool Delete(const db::ID id) const;
	size_t Count(const Account::Filter& filter) const;

private:
	Accounts ExtractModels(const flm::db::DbResult& result) const;
};


} // namespace db