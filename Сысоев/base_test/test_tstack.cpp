#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st());
}
TEST(TStack, can_check_empty)
{
	TStack<int>st = TStack<int>(1);
	EXPECT_EQ(1, st.empty());
}
TEST(TStack, throw_when_try_push_to_full_stack)
{
	TStack<int>st = TStack<int>(40);
	for (int i = 0; i < 40; i++)
		st.push(0);
	ASSERT_ANY_THROW(st.push(0));
}
TEST(TStack, can_push)
{
	TStack<int>st = TStack<int>(2);
	ASSERT_NO_THROW(st.push(0));
}
TEST(TStack, can_pop_to_stack)
{
	TStack<int>st = TStack<int>(1);
	st.push(1);
	ASSERT_NO_THROW(st.pop());
}
TEST(TStack, throw_when_try_to_pop_from_empty_stack)
{
	TStack<int>st = TStack<int>(1);
	st.push(1);
	st.pop();
	ASSERT_ANY_THROW(st.pop());

}
TEST(TStack, throw_when_try_get_top_element_from_empty_stack)
{
	TStack<int>st = TStack<int>(1);
	ASSERT_ANY_THROW(st.back());
}