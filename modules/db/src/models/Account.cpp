#include "pch.hpp"

#include "db/models/Account.hpp"
#include "db/TypeConversion.hpp"

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
static const std::string createdAt{ "created_at" };
static const std::string loginAt{ "login_at" };
static const std::string status2fa{ "status_2fa" };
static const std::string status{ "status" };


} // namespace col
} // local namespace


namespace db
{


Account::Filter::Filter()
	: id{}
	, email{}
	, pwd{}
	, question{}
	, answer{}
	, name{}
	, createdAt{ "", "" }
	, loginAt{ "", "" }
	, status2fa{ "" }
	, status{}
{}


Account::Filter::Filter(const db::ID p_id)
	: Filter{}
{
	id.push_back(Item<ID>{ p_id });
}


Account::Filter::Filter(const std::string& p_email)
	: Filter{}
{
	email.push_back(p_email);
}


std::string Account::Filter::ToSql(const Escape& escape) const
{
	std::list<std::string> conditions;

	if (!id.empty()) {
		conditions.push_back(db::ToSql(id, col::id));
	}
	if (!email.empty()) {
		conditions.push_back(db::ToSql(email, col::email, escape));
	}
	if (!pwd.empty()) {
		conditions.push_back(db::ToSql(pwd, col::password, escape));
	}
	if (!question.empty()) {
		conditions.push_back(db::ToSql(question, col::question, escape));
	}
	if (!answer.empty()) {
		conditions.push_back(db::ToSql(answer, col::answer, escape));
	}
	if (!name.empty()) {
		conditions.push_back(db::ToSql(name, col::name, escape));
	}
	if (!createdAt.IsInited()) {
		conditions.push_back(createdAt.ToSql(col::createdAt, escape));
	}
	if (!loginAt.IsInited()) {
		conditions.push_back(loginAt.ToSql(col::loginAt, escape));
	}
	if (!status2fa.IsInited()) {
		conditions.push_back(status2fa.ToSql(col::status2fa, escape));
	}
	if (!status.empty()) {
		conditions.push_back(db::ToSql(status, col::status, escape));
	}

	return utils::JoinStrList(conditions, " AND ");
}


Account::Account()
	: m_id{ 0 }
	, m_status2fa{ false }
	, m_status{ AccountStatus::Active }
{}


Account::Account(
		db::ID id,
		std::string email,
		std::string pwd,
		std::string question,
		std::string answer,
		std::string name,
		Timestamp createdAt,
		Timestamp loginAt,
		bool status2fa,
		AccountStatus status
)
	: m_id{ id }
	, m_email{ email }
	, m_pwd{ pwd }
	, m_question{ question }
	, m_answer{ answer }
	, m_name{ name }
	, m_createdAt{ createdAt }
	, m_loginAt{ loginAt }
	, m_status2fa{ status2fa }
	, m_status{ status }
{}


ID Account::Id() const
{
	return m_id;
}


std::string Account::Email() const
{
	return m_email;
}


std::string Account::Pwd() const
{
	return m_pwd;
}


std::string Account::Question() const
{
	return m_question;
}


std::string Account::Answer() const
{
	return m_answer;
}


std::string Account::Name() const
{
	return m_name;
}


std::string Account::CreatedAt() const
{
	return m_createdAt;
}


std::string Account::LoginAt() const
{
	return m_loginAt;
}


std::string Account::Status2fa() const
{
	return ToStr(m_status2fa);
}


std::string Account::Status() const
{
	return ToStr(m_status);
}


void Account::Id(const ID id)
{
	m_id = id;
}


void Account::Email(const std::string& email)
{
	m_email = email;
}


void Account::Pwd(const std::string& pwd)
{
	m_pwd = pwd;
}


void Account::Question(const std::string& question)
{
	m_question = question;
}


void Account::Answer(const std::string& answer)
{
	m_answer = answer;
}


void Account::Name(const std::string& name)
{
	m_name = name;
}


void Account::CreatedAt(const Timestamp& createdAt)
{
	m_createdAt = createdAt;
}


void Account::LoginAt(const Timestamp& loginAt)
{
	m_loginAt = loginAt;
}


void Account::Status2fa(const bool status2fa)
{
	m_status2fa = status2fa;
}


void Account::Status2fa(const std::string& status2fa)
{
	m_status2fa = BoolFromStr(status2fa);
}


void Account::Status(const AccountStatus status)
{
	m_status = status;
}


void Account::Status(const std::string& status)
{
	m_status = AccountStatusFromStr(status);
}


std::string ToStr(const AccountStatus& status)
{
	switch(status)
	{
		case AccountStatus::Active: return "Active";
		case AccountStatus::Disabled: return "Disabled";
		default: throw std::runtime_error{ "Bad cast" };
	}
}


AccountStatus AccountStatusFromStr(const std::string& str)
{
	if (str == "Active") {
		return AccountStatus::Active;
	} else if (str == "Disabled") {
		return AccountStatus::Disabled;
	} else {
		throw std::runtime_error{ "Bad cast" };
	}
}


} // namespace db