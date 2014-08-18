#include "fixture.h"

#include <adapter.h>
#include <algorithm.h>

#include <boost/test/unit_test.hpp>

#include <array>
#include <numeric>


#define RANGE(c) begin(c), end(c)

using namespace std;
using namespace stdext;

#define DEFINE_INPUT_TESTS(name) \
	BOOST_FIXTURE_TEST_CASE(name ## _input, input_iterator_range_fixture) { name(first, last); } \
	DEFINE_FORWARD_TESTS(name)
#define DEFINE_FORWARD_TESTS(name) \
	BOOST_FIXTURE_TEST_CASE(name ## _forward, forward_iterator_range_fixture) { name(first, last); } \
	DEFINE_BIDIRECTIONAL_TESTS(name)
#define DEFINE_BIDIRECTIONAL_TESTS(name) \
	BOOST_FIXTURE_TEST_CASE(name ## _bidrectional, bidirectional_iterator_range_fixture) { name(first, last); } \
	DEFINE_RANDOM_ACCESS_TESTS(name)
#define DEFINE_RANDOM_ACCESS_TESTS(name) \
	BOOST_FIXTURE_TEST_CASE(name ## _random_access, random_access_iterator_range_fixture) { name(first, last); }

template <typename Iterator>
void prepend_test(Iterator first, Iterator last)
{
	array<int, 10> prev;
	iota(RANGE(prev), -ptrdiff_t(prev.size()));

	auto concat = make_range(first, last) >> prepend(make_range(prev));
	int value = prev[0];
	for (auto p = concat.begin_pos(), p_last = concat.end_pos(); p != p_last; concat.increment_pos(p))
		BOOST_CHECK_EQUAL(concat.at_pos(p), value++);

	BOOST_CHECK_EQUAL(value, distance(first, last));
}
DEFINE_INPUT_TESTS(prepend_test)

template <typename Iterator>
void append_test(Iterator first, Iterator last)
{
	array<int, 10> next;
	iota(RANGE(next), distance(first, last));

	auto concat = make_range(first, last) >> append(make_range(next));
	int value = 0;
	for (auto p = concat.begin_pos(), p_last = concat.end_pos(); p != p_last; concat.increment_pos(p))
		BOOST_CHECK_EQUAL(concat.at_pos(p), value++);

	BOOST_CHECK_EQUAL(value, distance(first, last) + next.size());
}
DEFINE_INPUT_TESTS(append_test)

template <typename Iterator>
void trim_front_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> trim_front(3);
	int value = 3;
	for (auto p = range.begin_pos(), p_last = range.end_pos(); p != p_last; range.increment_pos(p))
		BOOST_CHECK_EQUAL(range.at_pos(p), value++);

	BOOST_CHECK_EQUAL(value, distance(first, last));
}
DEFINE_INPUT_TESTS(trim_front_test)

template <typename Iterator>
void trim_back_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> trim_back(3);
	int value = 0;
	for (auto p = range.begin_pos(), p_last = range.end_pos(); p != p_last; range.increment_pos(p))
		BOOST_CHECK_EQUAL(range.at_pos(p), value++);

	BOOST_CHECK_EQUAL(value, distance(first, last) - 3);
}
DEFINE_BIDIRECTIONAL_TESTS(trim_back_test)

template <typename Iterator>
void subrange_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> subrange(3, 7);
	int value = 3;
	for (auto p = range.begin_pos(), p_last = range.end_pos(); p != p_last; range.increment_pos(p))
		BOOST_CHECK_EQUAL(range.at_pos(p), value++);

	BOOST_CHECK_EQUAL(value, 7);
}
DEFINE_RANDOM_ACCESS_TESTS(subrange_test)

template <typename Iterator>
void remove_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> remove(5);
	int values[] = { 0, 1, 2, 3, 4, 6, 7, 8, 9 };
	BOOST_CHECK(equal(range, make_range(values)));
}
DEFINE_INPUT_TESTS(remove_test)

template <typename Iterator>
void remove_if_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> remove_if([](int n) { return (n & 1) != 0; });
	int values[] = { 0, 2, 4, 6, 8 };
	BOOST_CHECK(equal(range, make_range(values)));
}
DEFINE_INPUT_TESTS(remove_if_test)

template <typename Iterator>
void select_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> select(5);
	auto p = range.begin_pos();
	BOOST_CHECK_EQUAL(range.at_pos(p), 5);
	range.increment_pos(p);
	BOOST_CHECK(p == range.end_pos());
}
DEFINE_INPUT_TESTS(select_test)

template <typename Iterator>
void select_if_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> select_if([](int n) { return (n & 1) == 0; });
	int values[] = { 0, 2, 4, 6, 8 };
	BOOST_CHECK(equal(range, make_range(values)));
}
DEFINE_INPUT_TESTS(select_if_test)

template <typename Iterator>
void transform_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> transform([](int n) { return n + 1; });
	int value = 1;
	for (auto p = range.begin_pos(), p_last = range.end_pos(); p != p_last; range.increment_pos(p))
		BOOST_CHECK_EQUAL(range.at_pos(p), value++);
}
DEFINE_INPUT_TESTS(transform_test)

template <typename Iterator>
void replace_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> replace(5, 10);
	int value = 0;
	for (auto p = range.begin_pos(), p_last = range.end_pos(); p != p_last; range.increment_pos(p))
	{
		BOOST_CHECK_EQUAL(range.at_pos(p), value == 5 ? 10 : value);
		++value;
	}
}
DEFINE_INPUT_TESTS(replace_test)

template <typename Iterator>
void replace_if_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> replace_if([](int n) { return (n & 1) == 0; }, 0);
	int value = 0;
	for (auto p = range.begin_pos(), p_last = range.end_pos(); p != p_last; range.increment_pos(p))
	{
		BOOST_CHECK_EQUAL(range.at_pos(p), (value & 1) != 0 ? value : 0);
		++value;
	}
}
DEFINE_INPUT_TESTS(replace_if_test)

template <typename Iterator>
void unique_test(Iterator first, Iterator last)
{
	int values[] = { 0, 1, 1, 2, 2, 2, 3, 3, 3, 3 };
	auto range = make_range(values) >> unique();
	int value = 0;
	for (auto p = range.begin_pos(), p_last = range.end_pos(); p != p_last; range.increment_pos(p))
		BOOST_CHECK_EQUAL(range.at_pos(p), value++);

	BOOST_CHECK_EQUAL(value, 4);
}
DEFINE_INPUT_TESTS(unique_test)

template <typename Iterator>
void unique_if_test(Iterator first, Iterator last)
{
	int values[] = { 0, 2, 1, 3, 4, 6, 5, 7, 8, 10 };
	int uniqued[] = { 0, 1, 4, 5, 8 };
	auto range = make_range(values) >> unique_if([](int a, int b) { return (a & 1) == (b & 1); });
	BOOST_CHECK(equal(range, make_range(uniqued)));
}
DEFINE_INPUT_TESTS(unique_if_test)

template <typename Iterator>
void reverse_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> reverse();
	int value = 10;
	for (auto p = range.begin_pos(), p_last = range.end_pos(); p != p_last; range.increment_pos(p))
		BOOST_CHECK_EQUAL(range.at_pos(p), --value);

	BOOST_CHECK_EQUAL(value, 0);
}
DEFINE_BIDIRECTIONAL_TESTS(reverse_test)

template <typename Iterator>
void rotate_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> rotate(4);
	int value = 4;
	for (auto p = range.begin_pos(), p_last = range.end_pos(); p != p_last; range.increment_pos(p))
	{
		BOOST_CHECK_EQUAL(range.at_pos(p), value++);
		if (value == 10)
			value = 0;
	}

	BOOST_CHECK_EQUAL(value, 4);
}
DEFINE_FORWARD_TESTS(rotate_test)

template <class Iterator>
void partition_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> partition(5);
	int values[] = { 5, 0, 1, 2, 3, 4, 6, 7, 8, 9 };
	BOOST_CHECK(equal(range, make_range(values)));
}
DEFINE_FORWARD_TESTS(partition_test)

template <class Iterator>
void partition_if_test(Iterator first, Iterator last)
{
	auto range = make_range(first, last) >> partition_if([](int n) { return (n & 1) == 0; });
	int values[] = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 };
	BOOST_CHECK(equal(range, make_range(values)));
}
DEFINE_FORWARD_TESTS(partition_if_test)