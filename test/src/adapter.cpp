#include <adapter.h>

#include <boost/test/unit_test.hpp>


using namespace std;
using namespace stdext;

BOOST_AUTO_TEST_CASE(test_concat)
{
	int first[] = { 0, 1 };
	int second[] = { 2, 3 };

	auto concat = make_range(first) >> append(make_range(second));
	auto p = concat.begin_pos();
	for (int n = 0; n < 4; ++n)
	{
		BOOST_CHECK(p != concat.end_pos());
		BOOST_CHECK_EQUAL(concat.at_pos(p), n);
		concat.increment_pos(p);
	}

	BOOST_CHECK(p == concat.end_pos());
}