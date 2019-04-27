#pragma once

#include "db/Pager.hpp"
#include "db/models/Account.hpp"

namespace db
{


class AccountWorker : public flm::db::Worker
{
public:
	AccountWorker(const bool autocommit = true);
	AccountWorker(ShPtr<flm::db::ConnUnit> connection, const bool autocommit = true);
	AccountWorker(UnPtr<flm::db::ConnUnit> connection, const bool autocommit = true);

public:
	UnPtr<Account> Insert(const Account& acc) const;
	Accounts Select(const Account::Filter& filter, const Pager& pager = Pager{}) const;
	UnPtr<Account> Update(const ID id, const ShPtr<Account> acc) const;
	bool Delete(const ID id) const;
	size_t Count(const Account::Filter& filter) const;

private:
	Accounts ExtractModels(const flm::db::DbResult& result) const;
};


} // namespace db