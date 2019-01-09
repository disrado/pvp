#include "pch.hpp"

#include "db/AccountWork.hpp"
#include "db/models/Filter.hpp"
#include "db/models/Account.hpp"

TEST(Crypto, HashHashesData)
{
	auto acc{ db::Account{} };
	{
		acc.Email("n.maltsev.dis@gmail.com");
		acc.Pwd("password");
		acc.Question("Secret question");
		acc.Answer("Secret answer");
		acc.Name("Nikita");
		acc.Status2fa(false);
		acc.Status(db::AccountStatus::ACTIVE);
	}

	const auto work{ db::AccountWork{ flm::db::Pool::Inst().Acquire() } };

	work.Insert(acc);
	work.Commit();

	EXPECT_EQ(1, 1);
}