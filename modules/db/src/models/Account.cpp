#include "pch.hpp"

#include "db/models/Account.hpp"
#include "db/models/TypeConversion.hpp"
#include <algorithm>
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


std::string Account::Filter::ToSql(const std::string& key, Item<>::Escape escape) const
{
	std::string sql;

	if (!id.list.empty()) {
		sql += key;
	}

	return escape(sql);
}


ID Account::Id()
{
	return m_id;
}


std::string Account::Email()
{
	return m_email;
}


std::string Account::Pwd()
{
	return m_pwd;
}


std::string Account::Question()
{
	return m_question;
}


std::string Account::Answer()
{
	return m_answer;
}


std::string Account::Name()
{
	return m_name;
}


std::string Account::CreatedAt()
{
	return m_createdAt;
}


std::string Account::LoginAt()
{
	return m_loginAt;
}


std::string Account::Status2fa()
{
	return ToStr(m_status2fa);
}


std::string Account::Status()
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