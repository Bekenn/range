#include <functional>

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

	template<class SinglePassRange, class T>
	typename range_traits<SinglePassRange>::iterator find(SinglePassRange range, const T& value)
	{
		return find_if(range, [&](range_traits<SinglePassRange>::reference a) {return a == value; });
	}

	template<class SinglePassRange, class Predicate>
	typename range_traits<SinglePassRange>::iterator find_if(SinglePassRange range, Predicate pred)
	{
		while (!range.empty())
		{
			if (pred(range.front()))
				return range.begin();
			range.shrink_front();
		}

		return range.end();
	}

	template<class SinglePassRange, class Predicate>
	typename range_traits<SinglePassRange>::iterator find_if_not(SinglePassRange range, Predicate pred)
	{
		return find_if(range, std::not1(pred));
	}

	template<class MultiPassRange1, class MultiPassRange2>
	typename range_traits<MultiPassRange1>::iterator find_end(MultiPassRange1 range1, MultiPassRange2 range2)
	{
		return find_end(range1, range2, std::equal_to<>());
	}

	template<class MultiPassRange1, class MultiPassRange2, class BinaryPredicate>
	typename range_traits<MultiPassRange1>::iterator find_end(MultiPassRange1 range1, MultiPassRange2 range2, BinaryPredicate pred)
	{
		auto p = range1.end();

		while (true)
		{
			MultiPassRange1 r1 = range1.save();
			MultiPassRange2 r2 = range2.save();
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

	template<class SinglePassRange, class MultiPassRange>
	typename range_traits<SinglePassRange>::iterator find_first_of(SinglePassRange range1, MultiPassRange range2)
	{
		return find_first_of(range1, range2, std::equal_to<>());
	}

	template<class SinglePassRange, class MultiPassRange, class BinaryPredicate>
	typename range_traits<SinglePassRange>::iterator find_first_of(SinglePassRange range1, MultiPassRange range2, BinaryPredicate pred)
	{
		while (!range1.empty())
		{
			auto r2 = range2.save();
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

	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::iterator adjacent_find(MultiPassRange range)
	{
		return adjacent_find(range, std::equal_to<>());
	}

	template<class MultiPassRange, class BinaryPredicate>
	typename range_traits<MultiPassRange>::iterator adjacent_find(MultiPassRange range, BinaryPredicate pred)
	{
		if (range.empty())
			return range.end();

		auto r = range.save();
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

	template<class SinglePassRange1, class InputIterator2>
	std::pair<typename range_traits<SinglePassRange1>::iterator, InputIterator2> mismatch(SinglePassRange1 range1, InputIterator2 first2)
	{
		return mismatch(range1, first2, std::equal_to<>());
	}

	template <class SinglePassRange1, class InputIterator2, class BinaryPredicate>
	std::pair<typename range_traits<SinglePassRange1>::iterator, InputIterator2> mismatch(SinglePassRange1 range1, InputIterator2 first2, BinaryPredicate pred)
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

	template<class SinglePassRange1, class InputIterator2>
	bool equal(SinglePassRange1 range1, InputIterator2 first2)
	{
		return equal(range1, first2, std::equal_to<>());
	}

	template <class SinglePassRange1, class InputIterator2, class BinaryPredicate>
	bool equal(SinglePassRange1 range1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (!range1.empty())
		{
			if (!pred(range1.front(), *first2))
				return false;
			++first2;
			range1.shrink_front();
		}

		return true;
	}

	template<class MultiPassRange1, class ForwardIterator2>
	bool is_permutation(MultiPassRange1 range1, ForwardIterator2 first2)
	{
		return is_permutation(range1, first2, std::equal_to<>());
	}

#if 0
	template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				break;
			++first1;
			++first2;
		}

		if (first1 != last1)
		{
			ForwardIterator2 last2 = std::advance(first2, std::distance(first1, last1));
			for (ForwardIterator1 i = first1; i != last1; ++i)
			{
				auto pred1 = [&](typename std::iterator_traits<ForwardIterator1>::reference a) { return pred(a, *i); };
				ForwardIterator1 prev = std::find_if(first1, i, pred1);
				if (prev == i)
				{
					auto n = 1 + std::count_if(std::advance(i, 1), last1, pred1);
					auto pred2 = [&](typename std::iterator_traits<ForwardIterator2>::reference a) { return pred(a, *i); };
					if (n == 1)
					{
						if (std::find_if(first2, last2, pred2) == last2)
							return false;
					}
					else if (n != std::count_if(first2, last2, pred2))
						return false;
				}
			}
		}

		return true;
	}
#endif

	template<class MultiPassRange1, class ForwardIterator2, class BinaryPredicate>
	bool is_permutation(MultiPassRange1 range1, ForwardIterator2 first2, BinaryPredicate pred)
	{
		while (!range1.empty())
		{
			if (range1.front() != *first2)
				break;
			range1.shrink_front();
			++first2;
		}

		if (!range1.empty())
		{
			MultiPassRange1 r1 = range1.save();
			while (!r1.empty())
			{
				r1.shrink_front();
			}
		}

		return true;
	}
}