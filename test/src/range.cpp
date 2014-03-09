#include <range.h>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <forward_list>
#include <list>
#include <numeric>
#include <vector>


using namespace std;
using namespace stdext;

template <typename T>
class memory_input_iterator : public iterator<input_iterator_tag, T, ptrdiff_t, T*, T>
{
public:
	typedef typename memory_input_iterator::value_type value_type;
	typedef typename memory_input_iterator::pointer pointer;
	typedef typename memory_input_iterator::reference reference;

public:
	memory_input_iterator() : p(nullptr) { }
	memory_input_iterator(pointer p, size_t length) : p(p), length(length)
	{
		if (length == 0)
			p = nullptr;
		else
			v = *p;
	}

public:
	reference operator * () const { return v; }
	memory_input_iterator& operator ++ ()
	{
		++p;
		if (--length == 0)
			p = nullptr;
		else
			v = *p;
		return *this;
	}
	memory_input_iterator operator ++ (int)
	{
		auto i = *this;
		++*this;
		return i;
	}

private:
	friend bool operator == (const memory_input_iterator& a, const memory_input_iterator& b) { return a.p == b.p && a.length == b.length; }
	pointer p;
	size_t length;
	value_type v;
};

template <typename T>
bool operator != (const memory_input_iterator<T>& a, const memory_input_iterator<T>& b) { return !(a == b); }

struct input_iterator_range_fixture
{
	vector<int> numbers;

	input_iterator_range_fixture() : numbers(10)
	{
		iota(numbers.begin(), numbers.end(), 0);
	}
};

struct forward_iterator_range_fixture
{
	forward_list<int> numbers;

	forward_iterator_range_fixture() : numbers(10)
	{
		iota(numbers.begin(), numbers.end(), 0);
	}
};

struct bidirectional_iterator_range_fixture
{
	list<int> numbers;

	bidirectional_iterator_range_fixture() : numbers(10)
	{
		iota(numbers.begin(), numbers.end(), 0);
	}
};

struct random_access_iterator_range_fixture
{
	vector<int> numbers;

	random_access_iterator_range_fixture() : numbers(10)
	{
		iota(numbers.begin(), numbers.end(), 0);
	}
};

BOOST_FIXTURE_TEST_CASE(test_input_iterator_range, input_iterator_range_fixture)
{
	// memory_input_iterator behaves like an input iterator in all ways except
	// that it is possible to re-traverse a range.  This is an important trait
	// for testing.
	auto first = memory_input_iterator<int>(numbers.data(), numbers.size());
	auto last = memory_input_iterator<int>();
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
	auto range = make_range(numbers);
	BOOST_CHECK(range.begin_pos() == numbers.begin());
	BOOST_CHECK(range.end_pos() == numbers.end());
	BOOST_CHECK_EQUAL(&front(range), &numbers.front());

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

	range = make_range(numbers);
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
	auto range = make_range(numbers);
	BOOST_CHECK(range.begin_pos() == numbers.begin());
	BOOST_CHECK(range.end_pos() == numbers.end());
	BOOST_CHECK_EQUAL(&front(range), &numbers.front());
	BOOST_CHECK_EQUAL(&back(range), &numbers.back());
	BOOST_CHECK_EQUAL(length(range), numbers.size());

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

	range = make_range(numbers);
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
	auto range = make_range(numbers);
	BOOST_CHECK(range.begin_pos() == numbers.begin());
	BOOST_CHECK(range.end_pos() == numbers.end());
	BOOST_CHECK_EQUAL(&front(range), &numbers.front());
	BOOST_CHECK_EQUAL(&back(range), &numbers.back());
	BOOST_CHECK_EQUAL(length(range), numbers.size());

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

	range = make_range(numbers);
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
