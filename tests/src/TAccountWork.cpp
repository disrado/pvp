#include "pch.hpp"

#include "db/AccountWork.hpp"
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

	const auto work{ db::AccountWork{ flm::db::Pool::Inst().Acquire() } };
	auto result{ work.Insert(acc) };
	work.Commit();

	EXPECT_NE(result, nullptr);
}

TEST(Account, Select)
{
	const auto work{ db::AccountWork{ flm::db::Pool::Inst().Acquire() } };
	auto filter{ db::Account::Filter{ test::email } };

	EXPECT_FALSE(work.Select(filter).empty());
}

TEST(Account, Update)
{
	// const auto work{ db::AccountWork{ flm::db::Pool::Inst().Acquire() } };
	// auto filter{ db::Account::Filter{ test::email } };
	// auto accs{ work.Select(filter) };
	
	// const std::shared_ptr<db::Account> acc{ std::move(accs.at(0)) };
	// acc->Name("Nik");

	// auto result{ work.Update(acc->Id(), std::move(acc)) };
	// work.Commit();

	// EXPECT_EQ(result->Name(), "Nik");
}

TEST(Account, Count)
{
	// const auto work{ db::AccountWork{ flm::db::Pool::Inst().Acquire() } };
	// auto filter{ db::Account::Filter{ test::email } };

	// EXPECT_NE(work.Count(filter), 0);
}

TEST(Account, Delete)
{
	// const auto work{ db::AccountWork{ flm::db::Pool::Inst().Acquire() } };
	// auto filter{ db::Account::Filter{ test::email } };
	// auto accs{ work.Select(filter) };

	// EXPECT_TRUE(work.Delete(accs.at(0)->Id()));
	// work.Commit();
}