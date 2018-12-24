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
		std::string ToSql(const std::string& key, Item<>::Escape escape) const;

	public:
		Item<ID> id;
		Item<> email;
		Item<> pwd;
		Item<> question;
		Item<> answer;
		Item<> name;
		ItemRange<Timestamp> createdAt;
		ItemRange<Timestamp> loginAt;
		Item<> status2fa;
		Item<> status;
	};

public:
	ID Id();
	std::string Email();
	std::string Pwd();
	std::string Question();
	std::string Answer();
	std::string Name();
	std::string CreatedAt();
	std::string LoginAt();
	std::string Status2fa();
	std::string Status();

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


    // • id (serial)
    // • email (text not null, unique)
    // • password (text not null)
    // • question (text not null)
    // • answer (text not null)
    // • name (text not null, unique)
    // • created_at (tymestamp not null default now)
    // • login_at (temestamp not null)
    // • status_2fa (bool not null default false)
    // • status (AccountStatus not null default active)




} // namespace db::model