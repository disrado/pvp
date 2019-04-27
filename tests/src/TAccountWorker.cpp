#include "pch.hpp"

#include "db/AccountWorker.hpp"
#include "db/models/Filter.hpp"
#include "db/models/Account.hpp"

namespace test
{


static const std::string email{ "n.maltsev.dis82@gmail.com" };


}

TEST(Account, Insert)
{
	auto acc{ db::Account{} };
	{
		acc.Email(test::email);
		acc.Pwd("password");
		acc.Question("Secret question");
		acc.Answer("Secret answer");
		acc.Name("Nikita");
		acc.Status2fa(false);
		acc.Status(db::AccountStatus::Active);
	}

	const auto work{ db::AccountWorker{} };
	auto result{ work.Insert(acc) };

	EXPECT_NE(result, nullptr);
}

TEST(Account, Select)
{

}

TEST(Account, Update)
{

}

TEST(Account, Count)
{

}

TEST(Account, Delete)
{

}