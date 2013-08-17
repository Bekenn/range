#include <algorithm>
#include <functional>
#include <iterator>

namespace stdext
{
	// 25.2, non-modifying sequence operations:
	template <class SinglePassRange, class Predicate>
	bool all_of(SinglePassRange range, Predicate pred)
	{
		while (!range.empty())
		{
			if (!pred(range.front()))
				return false;
			range.shrink_front();
		}

		return true;
	}

	template <class SinglePassRange, class Predicate>
	bool any_of(SinglePassRange range, Predicate pred)
	{
		while (!range.empty())
		{
			if (pred(range.front()))
				return true;
			range.shrink_front();
		}

		return false;
	}

	template <class SinglePassRange, class Predicate>
	bool none_of(SinglePassRange range, Predicate pred)
	{
		return !any_of(range, pred);
	}

	template<class SinglePassRange, class Function>
	Function for_each(SinglePassRange range, Function f)
	{
		while (!range.empty())
		{
			f(range.front());
			range.shrink_front();
		}
	}

	template<class InputIterator, class T>
	InputIterator find(iterator_range<InputIterator> range, const T& value)
	{
		return find_if(range, [&](typename std::iterator_traits<InputIterator>::reference a) {return a == value; });
	}

	template<class InputIterator, class Predicate>
	InputIterator find_if(iterator_range<InputIterator> range, Predicate pred)
	{
		while (!range.empty())
		{
			if (pred(range.front()))
				return range.begin();
			range.shrink_front();
		}

		return range.end();
	}

	template<class InputIterator, class Predicate>
	InputIterator find_if_not(iterator_range<InputIterator> range, Predicate pred)
	{
		return find_if(range, std::not1(pred));
	}

	template<class ForwardIterator, class MultiPassRange>
	ForwardIterator find_end(iterator_range<ForwardIterator> range1, MultiPassRange range2)
	{
		return find_end(range1, range2, std::equal_to<>());
	}

	template<class ForwardIterator, class MultiPassRange, class BinaryPredicate>
	ForwardIterator find_end(iterator_range<ForwardIterator> range1, MultiPassRange range2, BinaryPredicate pred)
	{
		auto p = range1.end();

		while (true)
		{
			auto r1 = save(range1);
			auto r2 = save(range2);
			while (!r2.empty() && !r1.empty())
			{
				if (!pred(r1.front(), r2.front()))
					break;

				r1.shrink_front();
				r2.shrink_front();
			}

			if (r2.empty())
				p = r1.begin();

			if (r1.empty())
				break;

			range1.shrink_front();
		}

		return p;
	}

	template<class InputIterator, class MultiPassRange>
	InputIterator find_first_of(iterator_range<InputIterator> range1, MultiPassRange range2)
	{
		return find_first_of(range1, range2, std::equal_to<>());
	}

	template<class InputIterator, class MultiPassRange, class BinaryPredicate>
	InputIterator find_first_of(iterator_range<InputIterator> range1, MultiPassRange range2, BinaryPredicate pred)
	{
		while (!range1.empty())
		{
			auto r2 = save(range2);
			while (!r2.empty())
			{
				if (pred(range1.front(), r2.front()))
					return range1.begin();
				r2.shrink_front();
			}

			range1.shrink_front();
		}

		return range1.end();
	}

	template<class ForwardIterator>
	ForwardIterator adjacent_find(iterator_range<ForwardIterator> range)
	{
		return adjacent_find(range, std::equal_to<>());
	}

	template<class ForwardIterator, class BinaryPredicate>
	ForwardIterator adjacent_find(iterator_range<ForwardIterator> range, BinaryPredicate pred)
	{
		if (range.empty())
			return range.end();

		auto r = save(range);
		r.shrink_front();
		while (!r.empty())
		{
			if (pred(range.front(), r.front()))
				return range.begin();
			r.shrink_front();
			range.shrink_front();
		}

		return range.end();
	}

	template<class SinglePassRange, class T>
	typename range_traits<SinglePassRange>::size_type count(SinglePassRange range, const T& value)
	{
		return count_if(range, [&](typename range_traits<SinglePassRange>::reference a) { return a == value; });
	}

	template<class SinglePassRange, class Predicate>
	typename range_traits<SinglePassRange>::size_type count_if(SinglePassRange range, Predicate pred)
	{
		while (!range.empty())
		{
			if (pred(range.front()))
				return range.begin();
			range.shrink_front;
		}

		return range.end();
	}

	template<class InputIterator1, class InputIterator2>
	std::pair<InputIterator1, InputIterator2> mismatch(iterator_range<InputIterator1> range1, InputIterator2 first2)
	{
		return mismatch(range1, first2, std::equal_to<>());
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	std::pair<InputIterator1, InputIterator2> mismatch(iterator_range<InputIterator1> range1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (!range1.empty())
		{
			if (!pred(range1.front(), *first2))
				return std::make_pair(range1.begin(), first2);
			range1.shrink_front();
			++first2;
		}

		return make_pair(range1.end(), first2);
	}

	template<class InputIterator1, class InputIterator2>
	std::pair<InputIterator1, InputIterator2> mismatch(iterator_range<InputIterator1> range1, iterator_range<InputIterator2> range2)
	{
		return mismatch(range1, range2, std::equal_to<>());
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	std::pair<InputIterator1, InputIterator2> mismatch(iterator_range<InputIterator1> range1, iterator_range<InputIterator2> range2, BinaryPredicate pred)
	{
		while (!range1.empty() && !range2.empty())
		{
			if (!pred(range1.front(), range2.front()))
				return std::make_pair(range1.begin(), range2.begin());
			range1.shrink_front();
			range2.shrink_front();
		}

		return std::make_pair(range1.begin(), range2.begin());
	}

	template<class SinglePassRange1, class InputIterator2>
	typename std::enable_if<!is_range<InputIterator2>::value, bool>::type
		equal(SinglePassRange1 range1, InputIterator2 first2)
	{
		return equal(range1, first2, std::equal_to<>());
	}

	template <class SinglePassRange1, class InputIterator2, class BinaryPredicate>
	typename std::enable_if<!is_range<InputIterator2>::value, bool>::type
		equal(SinglePassRange1 range1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (!range1.empty())
		{
			if (!pred(range1.front(), *first2))
				return false;
			range1.shrink_front();
			++first2;
		}

		return true;
	}

	template<class SinglePassRange1, class SinglePassRange2>
	typename std::enable_if<is_range<SinglePassRange2>::value, bool>::type
		equal(SinglePassRange1 range1, SinglePassRange2 range2)
	{
		return equal(range1, range2, std::equal_to<>());
	}

	template<class SinglePassRange1, class SinglePassRange2, class BinaryPredicate>
	typename std::enable_if<is_range<SinglePassRange2>::value, bool>::type
		equal(SinglePassRange1 range1, SinglePassRange2 range2, BinaryPredicate pred)
	{
		while (!range1.empty() && !range2.empty())
		{
			if (!pred(range1.front(), range2.front()))
				return false;
			range1.shrink_front();
			range2.shrink_front();
		}

		return true;
	}

	template<class MultiPassRange1, class ForwardIterator2>
	typename std::enable_if<!is_range<ForwardIterator2>::value, bool>::type
		is_permutation(MultiPassRange1 range1, ForwardIterator2 first2)
	{
		return is_permutation(range1, first2, std::equal_to<>());
	}

	template<class MultiPassRange1, class ForwardIterator2, class BinaryPredicate>
	typename std::enable_if<!is_range<ForwardIterator2>::value, bool>::type
		is_permutation(MultiPassRange1 range1, ForwardIterator2 first2, BinaryPredicate pred)
	{
		for (; !range1.empty(); range1.drop_first(), ++first2)
		{
			if (!pred(range1.front(), *first2))
				break;
		}

		if (range1.empty())
			return true;

		ForwardIterator2 last2 = std::advance(first2, length(range1));
		return is_permutation(range1, make_range(first2, last2), pred);
	}

	template<class MultiPassRange1, class MultiPassRange2>
	typename std::enable_if<is_range<MultiPassRange2>::value, bool>::type
		is_permutation(MultiPassRange1 range1, MultiPassRange2 range2)
	{
		return is_permutation(range1, range2, std::equal_to<>());
	}

	template<class MultiPassRange1, class MultiPassRange2, class BinaryPredicate>
	typename std::enable_if<is_range<MultiPassRange2>::value, bool>::type
		is_permutation(MultiPassRange1 range1, MultiPassRange2 range2, BinaryPredicate pred)
	{
		for (; !range1.empty() && !range2.empty(); range1.drop_first(), range2.drop_first())
		{
			if (!pred(range1.front(), range2.front()))
				break;
		}

		if (range1.empty() && range2.empty())
			return true;

		typename std::common_type<typename range_traits<MultiPassRange1>::size_type,
			typename range_traits<MultiPassRange2>::size_type>::type n = 0;
		auto pred1 = [&](typename range_traits<MultiPassRange1>::reference a) { return pred(a, range1.front()); };
		auto pred2 = [&](typename range_traits<MultiPassRange2>::reference a) { return pred(a, range1.front()); };
		auto basis = save(range1);
		for (; !range1.empty(); range1.drop_first(), ++n)
		{
			auto head = make_subrange(basis, 0, n);
			if (any_of(head, pred1))
				continue;

			auto r1 = range1;
			r1.drop_first();
			auto count = 1 + count_if(std::move(r1), pred1);
			if (count == 1)
			{
				if (!any_of(range2, pred2))
					return false;
			}
			else
			{
				if (count_if(range2, pred2) != count)
					return false;
			}
		}
	}

	template<class ForwardIterator, class MultiPassRange>
	ForwardIterator search(iterator_range<ForwardIterator> range1, MultiPassRange range2)
	{
		return search(std::move(range1), std::move(range2), std::equal_to<>());
	}

	template<class ForwardIterator, class MultiPassRange, class BinaryPredicate>
	ForwardIterator search(iterator_range<ForwardIterator> range1, MultiPassRange range2, BinaryPredicate pred)
	{
		for (; !range1.empty(); range1.drop_first())
		{
			auto r1 = save(range1);
			auto r2 = save(range2);
			for (; !r1.empty() && !r2.empty(); r1.drop_first(), r2.drop_first())
			{
				if (!pred(r1.front(), r2.front()))
					break;
			}

			if (r2.empty())
				return range1.begin();

			if (r1.empty())
				return range1.end();
		}

		return range1.end();
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator search_n(iterator_range<ForwardIterator> range, Size count, const T& value)
	{
		return search_n(std::move(range), std::move(count), value, std::equal_to<>());
	}

	template <class ForwardIterator, class Size, class T, class BinaryPredicate>
	ForwardIterator search_n(iterator_range<ForwardIterator> range, Size count, const T& value, BinaryPredicate pred)
	{
		for (; !range.empty(); range.drop_first())
		{
			auto r = save(range);
			auto n = count;
			for (; !r.empty() && n > 0; r.drop_first(), --n)
			{
				if (!pred(r.front(), value))
					break;
			}

			if (n == 0)
				return r.begin();

			if (r.empty())
				return r.end();
		}

		return range.end();
	}
}