#pragma once

#include "db/models/Filter.hpp"

namespace db
{

enum class AccountStatus
{
	Active,
	Disabled
};

struct Account
{
public:
	struct Filter
	{
	public:
		Filter();
		Filter(const db::ID p_id);
		Filter(const std::string& p_email);

	public:
		std::string ToSql(const Escape& escape = nullptr) const;

	public:
		ItemList<ID> id;
		ItemList<> email;
		ItemList<> pwd;
		ItemList<> question;
		ItemList<> answer;
		ItemList<> name;
		ItemRange<Timestamp> createdAt;
		ItemRange<Timestamp> loginAt;
		Item<> status2fa;
		ItemList<> status;
	};

public:
	Account();
	Account(
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
	);

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


using Accounts = std::vector<UnPtr<Account>>;


std::string ToStr(const AccountStatus& status);
AccountStatus AccountStatusFromStr(const std::string& str);


} // namespace db