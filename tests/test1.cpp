#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Transaction.h"
#include "Account.h"
using ::testing::_;


class MockTransaction : public Transaction {
public:
	MOCK_METHOD(bool, Make, (Account& from, Account& to, int sum), ());
	MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

class MockAccount : public Account {
public:
	MockAccount(int id, int balance) : Account(id, balance) {};
	MOCK_METHOD(int, GetBalance, (), (const, override));
	MOCK_METHOD(void, ChangeBalance, (int diff), (override));
	MOCK_METHOD(void, Lock, (), (override));
	MOCK_METHOD(void, Unlock, (), (override));
	MOCK_METHOD(int, id, (), (const));
};

TEST(Transaction_test, test_SaveToDataBase) {

	Account test1(1, 10000);
	Account test2(2, 44444);
	MockTransaction trans;
	EXPECT_CALL(trans, SaveToDataBase(_, _, _)).Times(1);	 
	trans.SaveToDataBase(test1, test2, 150);
}

TEST(Transaction_test, test_set_fee) {
	Transaction trans;
	trans.set_fee(5);
	EXPECT_TRUE(5 == trans.fee());
}

TEST(Transaction_test, test_fee) {
	Transaction trans;
	EXPECT_TRUE(1 == trans.fee());
}

TEST(MockAccount_test, test_lock) {
	MockAccount acc1(1, 200);
	MockAccount acc2(2, 873);
	Transaction trans;

	EXPECT_CALL(acc1, Lock()).Times(::testing::AtLeast(1));
	EXPECT_CALL(acc2, Lock()).Times(::testing::AtLeast(1));

	trans.Make(acc1, acc2, 150);
}

TEST(MockAccount_test, test_unlock) {
	MockAccount acc1(1, 200);
	MockAccount acc2(2, 873);
	Transaction trans;

	EXPECT_CALL(acc1, Unlock()).Times(::testing::AtLeast(1));
	EXPECT_CALL(acc2, Unlock()).Times(::testing::AtLeast(1));

	trans.Make(acc1, acc2, 150);
}


TEST(Account_test, test_GetBalance1) {
	Account acc(101, 1337);

	int balance = acc.GetBalance();

	EXPECT_EQ(balance, 1337);
}

TEST(Account_test, test_GetBalance2) {
	Account acc(99, 0);// Arrange

	int balance = acc.GetBalance();//Act

	EXPECT_EQ(balance, 0);//Assert
}

TEST(Account_test, test_ChangeBalance) {
	Account acc(99, 1);

	acc.Lock();
	acc.ChangeBalance(87556);
	acc.Unlock();
	int balance = acc.GetBalance();

	EXPECT_EQ(balance, 87557);
}

TEST(Account_test, test_Lock) {
	Account acc(99, 0);

	ASSERT_ANY_THROW(acc.ChangeBalance(87556));
}

TEST(Account_test, test_Lock2) {
	Account acc(99, 0);

	acc.Lock();
	
	ASSERT_ANY_THROW(acc.Lock(););
}

TEST(Account_test, test_UnLock) {
	Account acc(99, 0);

	acc.Lock();
	acc.Unlock();
	ASSERT_NO_THROW(acc.Lock());
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
