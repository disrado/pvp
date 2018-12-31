#include "pch.hpp"

#include "db/models/Account.hpp"
#include "db/TypeConversion.hpp"


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

namespace db
{


Account::Filter::Filter()
	: id{ 0 }
	, email{ "" }
	, pwd{ "" }
	, question{ "" }
	, answer{ "" }
	, name{ "" }
	, createdAt{ "", "" }
	, loginAt{ "", "" }
	, status2fa{ "" }
	, status{ "" }
{}


Account::Filter::Filter(const db::ID p_id)
	: Filter{}
{
	id.Add(p_id);
}


Account::Filter::Filter(const std::string& p_email)
	: Filter{}
{
	email.Add(p_email);
}


std::string Account::Filter::ToSql(const ItemList<>::Escape& escape) const
{
	return fmt::format("{} {} {} {} {} {} {} {} {} {}",
		id.ToSql(col::id, escape),
		email.ToSql(col::email, escape),
		pwd.ToSql(col::password, escape),
		question.ToSql(col::question, escape),
		answer.ToSql(col::answer, escape),
		name.ToSql(col::name, escape),
		createdAt.ToSql(col::createdAt, escape),
		loginAt.ToSql(col::loginAt, escape),
		status2fa.ToSql(col::status2fa, escape),
		status.ToSql(col::status, escape)
	);
}


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


} // namespace db