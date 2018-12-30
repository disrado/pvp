#pragma once

#include "db/Aliases.hpp"
#include "db/models/Filter.hpp"

namespace db
{

enum class AccountStatus
{
	ACTIVE,
	DISABLED
};

struct Account
{
public:
	struct Filter
	{
	public:
		Filter();

	public:
		std::string ToSql(Item<>::Escape escape) const;

	public:
		Item<ID> id;
		Item<> email;
		Item<> pwd;
		Item<> question;
		Item<> answer;
		Item<> name;
		Range<Timestamp> createdAt;
		Range<Timestamp> loginAt;
		Item<> status2fa;
		Item<> status;
	};

public:
	ID Id() const;
	std::string Email() const;
	std::string Pwd() const;
	std::string Question() const;
	std::string Answer() const;
	std::string Name() const;
	std::string CreatedAt() const;
	std::string LoginAt() const;
	std::string Status2fa() const;
	std::string Status() const;

	void Id(const ID id);
	void Email(const std::string& email);
	void Pwd(const std::string& pwd);
	void Question(const std::string& question);
	void Answer(const std::string& answer);
	void Name(const std::string& name);
	void CreatedAt(const Timestamp& createdAt);
	void LoginAt(const Timestamp& loginAt);
	void Status2fa(const bool status2fa);
	void Status2fa(const std::string& status2fa);
	void Status(const AccountStatus status);
	void Status(const std::string& status);

public:
	ID m_id;
	std::string m_email;
	std::string m_pwd;
	std::string m_question;
	std::string m_answer;
	std::string m_name;
	Timestamp m_createdAt;
	Timestamp m_loginAt;
	bool m_status2fa;
	AccountStatus m_status;
};


} // namespace db::model