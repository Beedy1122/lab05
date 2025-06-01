#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Transaction.h"
#include "Account.h"

class AccountMock : public Account {
public:
  AccountMock(int id, int balance) : Account(id, balance) {};
  MOCK_METHOD(int, GetBalance, (), (const, override));
  MOCK_METHOD(void, ChangeBalance, (int diff), (override));
  MOCK_METHOD(void, Lock, (), (override));
  MOCK_METHOD(void, Unlock, (), (override));
  MOCK_METHOD(int, id, (), (const));
};

TEST(Transaction_test, test_fee) {
  Transaction trans;
  EXPECT_TRUE(1 == trans.fee());
}

TEST(Transaction_test, test_set_fee) {
  Transaction trans;
  trans.set_fee(5);
  EXPECT_TRUE(5 == trans.fee());
}

TEST(Account_test, test_GetBalance1) {
  Account acc(69, 2001);

  int balance = acc.GetBalance();

  EXPECT_EQ(balance, 2001);
}

TEST(Account_test, test_GetBalance2) {
  Account acc(12, 45);

  int balance = acc.GetBalance();

  EXPECT_EQ(balance, 45);
}

TEST(Account_test, test_ChangeBalance) {
  Account acc(22, 1);

  acc.Lock();
  acc.ChangeBalance(2220);
  acc.Unlock();
  int balance = acc.GetBalance();

  EXPECT_EQ(balance, 2221);
}

TEST(AccountMock_test, test_ChangeBalance) {
  AccountMock acc1(1, 100);
  AccountMock acc2(2, 873);
  Transaction trans;

  ON_CALL(acc1, GetBalance()).WillByDefault(::testing::Return(200));
  EXPECT_CALL(acc1, ChangeBalance(::testing::_)).Times(::testing::AtLeast(1));

  EXPECT_CALL(acc2, ChangeBalance(150)).Times(::testing::AtLeast(1));
   
  trans.Make(acc1, acc2, 150);
}

TEST(AccountMock_test, test_GetbBalance) {
  AccountMock acc1(1, 100);
  AccountMock acc2(2, 873);
  Transaction trans;

  EXPECT_CALL(acc1, GetBalance()).Times(2);
  EXPECT_CALL(acc2, GetBalance()).Times(1);

  trans.Make(acc1, acc2, 150);
}

TEST(Transaction_test, test_SaveToDataBase) {

  Account acc1(1, 100);
  Account acc2(2, 873);
  Transaction trans;
  bool succes = trans.Make(acc1, acc2, 150);
  EXPECT_TRUE(acc1.GetBalance() == (200-150 - trans.fee()));
  EXPECT_TRUE(acc2.GetBalance() == (150+873));
  EXPECT_TRUE(succes);
}

TEST(AccountMock_test, test_lock) {
  AccountMock acc1(1, 100);
  AccountMock acc2(2, 873);
  Transaction trans;

  EXPECT_CALL(acc1, Lock()).Times(::testing::AtLeast(1));
  EXPECT_CALL(acc2, Lock()).Times(::testing::AtLeast(1));

  trans.Make(acc1, acc2, 150);
}

TEST(AccountMock_test, test_unlock) {
  AccountMock acc1(1, 100);
  AccountMock acc2(2, 873);
  Transaction trans;

  EXPECT_CALL(acc1, Unlock()).Times(::testing::AtLeast(1));
  EXPECT_CALL(acc2, Unlock()).Times(::testing::AtLeast(1));

  trans.Make(acc1, acc2, 150);
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
  ::testing::FLAGS_gmock_verbose = "error";
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
