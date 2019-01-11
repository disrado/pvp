#include "pch.hpp"

#include "db/AccountWork.hpp"
#include "db/TypeConversion.hpp"

#include "logger/Logger.hpp"

namespace
{
namespace col
{


static const std::string id{ "id" };
static const std::string email{ "email" };
static const std::string password{ "password" };
static const std::string question{ "question" };
static const std::string answer{ "answer" };
static const std::string name{ "name" };
static const std::string created_at{ "created_at" };
static const std::string login_at{ "login_at" };
static const std::string status_2fa{ "status_2fa" };
static const std::string status{ "status" };


} // namespace col


static const std::string table{ "account" };


} // namespace


namespace db
{


AccountWork::AccountWork(UnPtr<flm::db::ConnUnit> connection)
	: Worker{ std::move(connection) }
{}


UnPtr<Account> AccountWork::Insert(const Account& acc) const
{
	const auto query{ fmt::format(
		"INSERT INTO {} ({}) "
		"VALUES('{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}') "
		"RETURNING *",
		table,
		utils::JoinStrList({
			// col::id, serial in db
			col::email,
			col::password,
			col::question,
			col::answer,
			col::name,
			col::created_at,
			col::login_at,
			col::status_2fa,
			col::status
		}, ", "),
		// acc.Id(), serial in db
		acc.Email(),
		acc.Pwd(),
		acc.Question(),
		acc.Answer(),
		acc.Name(),
		"NOW()",// acc.CreatedAt(),
		"NOW()",// acc.LoginAt(),
		acc.Status2fa(),
		acc.Status()
	) };
	
	return std::move(ExtractModels(Execute(query)).at(0));
}


Accounts AccountWork::Select(const Account::Filter& filter, const Pager& pager) const
{
	const auto conditions{ filter.ToSql([this] (const std::string& rhs) {
		return this->Escape(rhs);
	}) };

	const auto query{ fmt::format( "SELECT * FROM {} {} ORDER BY {} DESC {}",
		table,
		conditions.empty() ? "" : ("WHERE " + conditions),
		col::id,
		pager.ToSql()
	) };

	return ExtractModels(Execute(query));
}


UnPtr<Account> AccountWork::Update(const db::ID id, const ShPtr<Account> acc) const
{
	std::list<std::string> assignments;

	const auto addAssignment{ [&assignments] (const std::string& lhs, const std::string& rhs) {
		return fmt::format("{} = '{}'", lhs, rhs);
	} };

	{
		addAssignment(col::id, ToStr(id));
		addAssignment(col::email, acc->Email());
		addAssignment(col::password, acc->Pwd());
		addAssignment(col::question, acc->Question());
		addAssignment(col::answer, acc->Answer());
		addAssignment(col::name, acc->Name());
		addAssignment(col::created_at, acc->CreatedAt());
		addAssignment(col::login_at, acc->LoginAt());
		addAssignment(col::status_2fa, acc->Status2fa());
		addAssignment(col::status, acc->Status());
	}

	const auto query{ fmt::format(
		"UPDATE {} SET {} WHERE id = {} {}",
		table,
		utils::JoinStrList(assignments, ", "),
		id
	) };

	return std::move(ExtractModels(Execute(query)).at(0));
}


bool AccountWork::Delete(const db::ID id) const
{
	const auto query{ fmt::format( "DELETE FROM {} WHERE id = {}", table, id) };

	return !(Execute(query).empty());
}


size_t AccountWork::Count(const Account::Filter& filter) const
{
	auto conditions{ filter.ToSql([this] (const std::string& rhs) {
		return this->Escape(rhs);
	}) };
	conditions = conditions.empty() ? "" : (" WHERE " + conditions);

	const auto query{ fmt::format("SELECT COUNT(*) FROM {} {}", table, conditions) };

	return Execute(query).begin()->begin()->as<size_t>();
}


Accounts AccountWork::ExtractModels(const flm::db::DbResult& result) const
{
	Accounts accounts{};

	for(const auto& row : result) {
		accounts.push_back(std::make_unique<Account>(
			row[col::id].as<db::ID>(),
			row[col::email].as<std::string>(),
			row[col::password].as<std::string>(),
			row[col::question].as<std::string>(),
			row[col::answer].as<std::string>(),
			row[col::name].as<std::string>(),
			row[col::created_at].as<Timestamp>(),
			row[col::login_at].as<Timestamp>(),
			row[col::status_2fa].as<bool>(),
			AccountStatusFromStr(row[col::status].as<std::string>())
		));
	}

	return accounts;
}


} // namespace db
