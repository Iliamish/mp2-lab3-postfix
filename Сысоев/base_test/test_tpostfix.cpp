#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, can_set_string)
{
	TPostfix pf;
	string a = "a+a";
	pf.SetInfix(a);
	EXPECT_EQ("a + a", pf.GetInfix());
}
TEST(TPostfix, can_put_spaces_after_ops_const_and_alt_in_infix)
{
	TPostfix pf;
	string a = { "a+a" };
	pf.SetInfix(a);
	EXPECT_EQ("a + a", pf.GetInfix());
}

TEST(TPostfix, can_to_postfix_correct_string)
{
	TPostfix pf;
	string a = "a+a";
	string k = SEPARATOR;
	pf.SetInfix(a);
	string res = "";
	res+=("a" + k + "a" + k + "+" + k);
	EXPECT_EQ(res, pf.ToPostfix());
}
TEST(TPostfix, throw_when_try_to_postfix_with_two_ops_in_row)
{
	TPostfix pf;
	string a =  "a++" ;
	pf.SetInfix(a);
	ASSERT_ANY_THROW(pf.ToPostfix());
}
TEST(TPostfix, throw_when_try_to_postfix_with_two_alts_or_const_in_row)
{
	TPostfix pf;
	string a = { "a 2" };
	pf.SetInfix(a);
	ASSERT_ANY_THROW(pf.ToPostfix());
}
TEST(TPostfix, throw_when_try_to_postfix_with_incorrect_start)
{
	TPostfix pf;
	string a = { "+2-a" };
	pf.SetInfix(a);
	ASSERT_ANY_THROW(pf.ToPostfix());
}
TEST(TPostfix, throw_when_try_to_postfix_with_op_after_open_bracket)
{
	TPostfix pf;
	string a = { "a+(+a)" };
	pf.SetInfix(a);
	ASSERT_ANY_THROW(pf.ToPostfix());
}
TEST(TPostfix, throw_when_try_to_postfix_with_op_before_close_bracket)
{
	TPostfix pf;
	string a = { "a+(a+)" };
	pf.SetInfix(a);
	ASSERT_ANY_THROW(pf.ToPostfix());
}
TEST(TPostfix, can_calculate)
{
	TPostfix pf;
	string a = { "2+3+4+1" };
	pf.SetInfix(a);
	pf.ToPostfix();
	EXPECT_EQ(10, pf.Calculate());
}