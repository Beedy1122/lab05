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
	MOCK_METHOD(void, Lock, (), (override));
	MOCK_METHOD(void, Unlock, (), (override));
	MOCK_METHOD(int, id, (), (const));
};
TEST(MockTransaction_test, test_SaveToDataBase)
{
	Account test1(1, 10000);
	Account test2(2, 44444);
	MockTransaction trans;
	EXPECT_CALL(trans, SaveToDataBase(_, _, _)).Times(1);	 
	trans.SaveToDataBase(test1, test2, 150);
}

TEST(Transaction_test, test_Make) 
{
	Account test1(1, 2000);
	Account test2(2, 3322);
	Transaction trans;
	bool sus = trans.Make(test1, test2, 4000);
	EXPECT_TRUE(sus);
	
}

TEST(Transaction_test, test_Make2) 
{
	Account test1(1, 2000);
	Account test2(2, -3);
	Transaction trans;
	bool sus = trans.Make(test1, test2, 4000);
	EXPECT_FALSE(sus);
	
}

TEST(Account_test, test_GetBalance1)
{
	Account test(23434, 1000);
	int balance = test.GetBalance();
	EXPECT_EQ(balance, 1000);
}

TEST(Acc_test, t_unlock)
{
	MockAccount test(1222, 0);
	EXPECT_CALL(test, Unlock()).Times(1);
	test.Unlock();
}


TEST(Account_test, test_GetBalance2) 
{
	Account test(9, 0);
	int balance = test.GetBalance();
	EXPECT_EQ(balance, 0);
}

TEST(Account_test, test_ChangeBalance)
{
	Account test(5, 4444);
	test.Lock();
	test.ChangeBalance(87556);
	int balance = test.GetBalance();
	EXPECT_EQ(balance, 92000);
}

TEST(Account_test, test_Lock) 
{
	MockAccount test(4, 0);
	EXPECT_CALL(test, Lock()).Times(1);
	test.Lock();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
