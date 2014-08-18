#include "fixture.h"

#include <range.h>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <forward_list>
#include <list>
#include <numeric>
#include <vector>


using namespace std;
using namespace stdext;

BOOST_FIXTURE_TEST_CASE(test_input_iterator_range, input_iterator_range_fixture)
{
	// memory_input_iterator behaves like an input iterator in all ways except
	// that it is possible to re-traverse a range.  This is an important trait
	// for testing.
	auto range = make_range(first, last);

	BOOST_CHECK(range.begin_pos() == first);
	BOOST_CHECK(range.end_pos() == last);
	BOOST_CHECK_EQUAL(front(range), *first);

	auto p = range.begin_pos();
	BOOST_CHECK_EQUAL(range.at_pos(p), 0);
	range.increment_pos(p);
	BOOST_CHECK_EQUAL(range.at_pos(p), 1);

	drop_first(range);
	BOOST_CHECK_EQUAL(front(range), 1);
	drop_first(range, 3);
	BOOST_CHECK_EQUAL(front(range), 4);

	range = make_range(first, last);
	p = range.begin_pos();
	auto q = p;
	for (auto n = 0; n < 5; ++n)
		range.increment_pos(p);
	advance_pos(range, q, 5);
	BOOST_CHECK(p == q);
	BOOST_CHECK_EQUAL(range.at_pos(p), 5);
	p = range.end_pos();
	BOOST_CHECK_THROW(advance_pos(range, q, -5), logic_error);
}

BOOST_FIXTURE_TEST_CASE(test_forward_iterator_range, forward_iterator_range_fixture)
{
	auto range = make_range(first, last);
	BOOST_CHECK(range.begin_pos() == first);
	BOOST_CHECK(range.end_pos() == last);
	BOOST_CHECK_EQUAL(&front(range), &*first);

	auto p = range.begin_pos();
	BOOST_CHECK_EQUAL(range.at_pos(p), 0);
	range.increment_pos(p);
	BOOST_CHECK_EQUAL(range.at_pos(p), 1);

	BOOST_CHECK_EQUAL(length(range), 10);
	drop_first(range);
	BOOST_CHECK_EQUAL(length(range), 9);
	BOOST_CHECK_EQUAL(front(range), 1);
	drop_first(range, 3);
	BOOST_CHECK_EQUAL(length(range), 6);
	BOOST_CHECK_EQUAL(front(range), 4);

	range = make_range(first, last);
	p = range.begin_pos();
	auto q = p;
	for (auto n = 0; n < 5; ++n)
		range.increment_pos(p);
	advance_pos(range, q, 5);
	BOOST_CHECK(p == q);
	BOOST_CHECK_EQUAL(range.at_pos(p), 5);
	p = range.end_pos();
	BOOST_CHECK_THROW(advance_pos(range, q, -5), logic_error);
}

BOOST_FIXTURE_TEST_CASE(test_bidirectional_iterator_range, bidirectional_iterator_range_fixture)
{
	auto range = make_range(first, last);
	auto range_back = last;
	--range_back;
	BOOST_CHECK(range.begin_pos() == first);
	BOOST_CHECK(range.end_pos() == last);
	BOOST_CHECK_EQUAL(&front(range), &*first);
	BOOST_CHECK_EQUAL(&back(range), &*range_back);
	BOOST_CHECK_EQUAL(length(range), distance(first, last));

	auto p = range.begin_pos();
	BOOST_CHECK_EQUAL(range.at_pos(p), 0);
	range.increment_pos(p);
	BOOST_CHECK_EQUAL(range.at_pos(p), 1);
	p = range.end_pos();
	range.decrement_pos(p);
	BOOST_CHECK_EQUAL(range.at_pos(p), 9);
	range.decrement_pos(p);
	BOOST_CHECK_EQUAL(range.at_pos(p), 8);

	BOOST_CHECK_EQUAL(length(range), 10);
	drop_first(range);
	BOOST_CHECK_EQUAL(length(range), 9);
	BOOST_CHECK_EQUAL(front(range), 1);
	drop_last(range);
	BOOST_CHECK_EQUAL(length(range), 8);
	BOOST_CHECK_EQUAL(back(range), 8);
	drop_first(range, 3);
	BOOST_CHECK_EQUAL(length(range), 5);
	drop_last(range, 3);
	BOOST_CHECK_EQUAL(length(range), 2);
	BOOST_CHECK_EQUAL(front(range), 4);
	BOOST_CHECK_EQUAL(back(range), 5);

	range = make_range(first, last);
	p = range.begin_pos();
	auto q = p;
	for (auto n = 0; n < 5; ++n)
		range.increment_pos(p);
	advance_pos(range, q, 5);
	BOOST_CHECK(p == q);
	BOOST_CHECK_EQUAL(range.at_pos(p), 5);
	p = range.end_pos();
	q = p;
	for (auto n = 0; n < 5; ++n)
		range.decrement_pos(p);
	advance_pos(range, q, -5);
	BOOST_CHECK(p == q);
	BOOST_CHECK_EQUAL(range.at_pos(p), 5);
}

BOOST_FIXTURE_TEST_CASE(test_random_access_iterator_range, random_access_iterator_range_fixture)
{
	auto range = make_range(first, last);
	BOOST_CHECK(range.begin_pos() == first);
	BOOST_CHECK(range.end_pos() == last);
	BOOST_CHECK_EQUAL(&front(range), &*first);
	BOOST_CHECK_EQUAL(&back(range), &*(last - 1));
	BOOST_CHECK_EQUAL(length(range), distance(first, last));

	auto p = range.begin_pos();
	BOOST_CHECK_EQUAL(range.at_pos(p), 0);
	range.increment_pos(p);
	BOOST_CHECK_EQUAL(range.at_pos(p), 1);
	p = range.end_pos();
	range.decrement_pos(p);
	BOOST_CHECK_EQUAL(range.at_pos(p), 9);
	range.decrement_pos(p);
	BOOST_CHECK_EQUAL(range.at_pos(p), 8);

	BOOST_CHECK_EQUAL(length(range), 10);
	drop_first(range);
	BOOST_CHECK_EQUAL(length(range), 9);
	BOOST_CHECK_EQUAL(front(range), 1);
	drop_last(range);
	BOOST_CHECK_EQUAL(length(range), 8);
	BOOST_CHECK_EQUAL(back(range), 8);
	drop_first(range, 3);
	BOOST_CHECK_EQUAL(length(range), 5);
	drop_last(range, 3);
	BOOST_CHECK_EQUAL(length(range), 2);
	BOOST_CHECK_EQUAL(front(range), 4);
	BOOST_CHECK_EQUAL(back(range), 5);

	range = make_range(first, last);
	p = range.begin_pos();
	auto q = p;
	range.advance_pos(p, 5);
	advance_pos(range, q, 5);
	BOOST_CHECK(p == q);
	BOOST_CHECK_EQUAL(range.at_pos(p), 5);
	p = range.end_pos();
	q = p;
	range.advance_pos(p, -5);
	advance_pos(range, q, -5);
	BOOST_CHECK(p == q);
	BOOST_CHECK_EQUAL(range.at_pos(p), 5);
}
