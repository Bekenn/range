#include <algorithm>
#include <functional>
#include <iterator>
#include <random>
#include <utility>
#include <vector>

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
	SinglePassRange find(SinglePassRange range, const T& value)
	{
		return find_if(std::move(range), [&](typename range_traits<SinglePassRange>::reference a) {return a == value; });
	}

	template<class SinglePassRange, class Predicate>
	SinglePassRange find_if(SinglePassRange range, Predicate pred)
	{
		while (!range.empty())
		{
			if (pred(range.front()))
				return range;
			range.shrink_front();
		}

		return range;
	}

	template<class SinglePassRange, class Predicate>
	SinglePassRange find_if_not(SinglePassRange range, Predicate pred)
	{
		return find_if(std::move(range), std::not1(pred));
	}

	template<class MultiPassRange1, class MultiPassRange2>
	MultiPassRange1 find_end(MultiPassRange1 range1, MultiPassRange2 range2)
	{
		return find_end(range1, range2, std::equal_to<>());
	}

	template<class MultiPassRange1, class MultiPassRange2, class BinaryPredicate>
	MultiPassRange1 find_end(MultiPassRange1 range1, MultiPassRange2 range2, BinaryPredicate pred)
	{
		auto result = range1;
		result.keep_after(result);

		while (true)
		{
			auto r1 = range1;
			auto r2 = range2;
			while (!r2.empty() && !r1.empty())
			{
				if (!pred(r1.front(), r2.front()))
					break;

				r1.shrink_front();
				r2.shrink_front();
			}

			if (r2.empty())
				result = r1;

			if (r1.empty())
				break;

			range1.shrink_front();
		}

		return result;
	}

	template<class SinglePassRange, class MultiPassRange>
	SinglePassRange find_first_of(SinglePassRange range1, MultiPassRange range2)
	{
		return find_first_of(range1, range2, std::equal_to<>());
	}

	template<class SinglePassRange, class MultiPassRange, class BinaryPredicate>
	SinglePassRange find_first_of(SinglePassRange range1, MultiPassRange range2, BinaryPredicate pred)
	{
		while (!range1.empty())
		{
			auto r2 = range2;
			while (!r2.empty())
			{
				if (pred(range1.front(), r2.front()))
					return range1;
				r2.shrink_front();
			}

			range1.shrink_front();
		}

		return range1;
	}

	template<class MultiPassRange>
	MultiPassRange adjacent_find(MultiPassRange range)
	{
		return adjacent_find(range, std::equal_to<>());
	}

	template<class MultiPassRange, class BinaryPredicate>
	MultiPassRange adjacent_find(MultiPassRange range, BinaryPredicate pred)
	{
		if (range.empty())
			return range;

		auto r = range;
		r.shrink_front();
		while (!r.empty())
		{
			if (pred(range.front(), r.front()))
				return range;
			r.shrink_front();
			range.shrink_front();
		}

		return r;
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

	template<class SinglePassRange, class InputIterator>
	typename std::enable_if<!is_range<InputIterator>::value, std::pair<SinglePassRange, InputIterator>>::type
		mismatch(SinglePassRange range1, InputIterator first2)
	{
		return mismatch(range1, first2, std::equal_to<>());
	}

	template <class SinglePassRange, class InputIterator, class BinaryPredicate>
	typename std::enable_if<!is_range<InputIterator>::value, std::pair<SinglePassRange, InputIterator>>::type
		mismatch(SinglePassRange range1, InputIterator first2, BinaryPredicate pred)
	{
		while (!range1.empty())
		{
			if (!pred(range1.front(), *first2))
				return std::make_pair(range1, first2);
			range1.shrink_front();
			++first2;
		}

		return make_pair(range1, first2);
	}

	template<class SinglePassRange1, class SinglePassRange2>
	typename std::enable_if<is_range<SinglePassRange2>::value, std::pair<SinglePassRange1, SinglePassRange2>>::type
		mismatch(SinglePassRange1 range1, SinglePassRange2 range2)
	{
		return mismatch(range1, range2, std::equal_to<>());
	}

	template<class SinglePassRange1, class SinglePassRange2, class BinaryPredicate>
	typename std::enable_if<is_range<SinglePassRange2>::value, std::pair<SinglePassRange1, SinglePassRange2>>::type
		mismatch(SinglePassRange1 range1, SinglePassRange2 range2, BinaryPredicate pred)
	{
		while (!range1.empty() && !range2.empty())
		{
			if (!pred(range1.front(), range2.front()))
				return std::make_pair(range1, range2);
			range1.shrink_front();
			range2.shrink_front();
		}

		return std::make_pair(range1, range2);
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

		ForwardIterator2 last2 = std::advance(first2, range_length(range1));
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
		auto basis = range1;
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

	template<class MultiPassRange1, class MultiPassRange2>
	MultiPassRange1 search(MultiPassRange1 range1, MultiPassRange2 range2)
	{
		return search(std::move(range1), std::move(range2), std::equal_to<>());
	}

	template<class MultiPassRange1, class MultiPassRange2, class BinaryPredicate>
	MultiPassRange1 search(MultiPassRange1 range1, MultiPassRange2 range2, BinaryPredicate pred)
	{
		for (; !range1.empty(); range1.drop_first())
		{
			auto r1 = range1;
			auto r2 = range2;
			for (; !r1.empty() && !r2.empty(); r1.drop_first(), r2.drop_first())
			{
				if (!pred(r1.front(), r2.front()))
					break;
			}

			if (r2.empty())
				return range1;

			if (r1.empty())
				return r1;
		}

		return range1;
	}

	template<class MultiPassRange, class Size, class T>
	MultiPassRange search_n(MultiPassRange range, Size count, const T& value)
	{
		return search_n(std::move(range), std::move(count), value, std::equal_to<>());
	}

	template <class MultiPassRange, class Size, class T, class BinaryPredicate>
	MultiPassRange search_n(MultiPassRange range, Size count, const T& value, BinaryPredicate pred)
	{
		for (; !range.empty(); range.drop_first())
		{
			auto r = range;
			auto n = count;
			for (; !r.empty() && n > 0; r.drop_first(), --n)
			{
				if (!pred(r.front(), value))
					break;
			}

			if (n == 0)
				return range;

			if (r.empty())
				return r;
		}

		return range;
	}

	template<class SinglePassRange, class OutputIterator>
	OutputIterator copy(SinglePassRange range, OutputIterator result)
	{
		for (; !range.empty(); range.drop_first())
			*result++ = range.front();

		return result;
	}

	template<class SinglePassRange, class Size, class OutputIterator>
	OutputIterator copy_n(SinglePassRange range, Size n, OutputIterator result)
	{
		for (; !range.empty() && n > 0; range.drop_first(), --n)
			*result++ = range.front();

		return result;
	}

	template<class SinglePassRange, class OutputIterator, class Predicate>
	OutputIterator copy_if(SinglePassRange range, OutputIterator result, Predicate pred)
	{
		for (; !range.empty(); range.drop_first())
		{
			if (pred(range.front()))
				*result++ = range.front();
		}

		return result;
	}

	template<class DoubleEndedRange1, class BidirectionalIterator2>
	BidirectionalIterator2 copy_backward(DoubleEndedRange1 range, BidirectionalIterator2 result)
	{
		for (; !range.empty(); range.drop_last())
			*--result = range.back();

		return result;
	}

	template<class SinglePassRange, class OutputIterator>
	OutputIterator move(SinglePassRange range, OutputIterator result)
	{
		for (; !range.empty(); range.drop_first())
			*result++ = std::move(range.front());

		return result;
	}

	template<class DoubleEndedRange1, class BidirectionalIterator2>
	BidirectionalIterator2 move_backward(DoubleEndedRange1 range, BidirectionalIterator2 result)
	{
		for (; !range.empty(); range.drop_last())
			*--result = std::move(range.back());

		return result;
	}

	template<class MultiPassRange1, class ForwardIterator2>
	ForwardIterator2 swap_ranges(MultiPassRange1 range1, ForwardIterator2 first2)
	{
		using std::swap;
		for (; !range1.empty(); range1.drop_first())
			swap(range1.front(), *first2++);

		return first2;
	}

	template<class SinglePassRange, class OutputIterator, class UnaryOperation>
	OutputIterator transform(SinglePassRange range, OutputIterator result, UnaryOperation op)
	{
		for (; !range.empty(); range.drop_first())
			*result++ = op(range.front());

		return result;
	}

	template<class SinglePassRange1, class InputIterator2, class OutputIterator, class BinaryOperation>
	OutputIterator transform(SinglePassRange1 range1, InputIterator2 first2, OutputIterator result, BinaryOperation binary_op)
	{
		for (; !range1.empty(); range1.drop_first())
			*result++ = binary_op(range1.front(), *first2++);

		return result;
	}

	template<class MultiPassRange, class T>
	void replace(MultiPassRange range, const T& old_value, const T& new_value)
	{
		replace_if(range, [&](typename range_traits<MultiPassRange>::reference a) { return a == old_value; }, new_value);
	}

	template<class MultiPassRange, class Predicate, class T>
	void replace_if(MultiPassRange range, Predicate pred, const T& new_value)
	{
		for (; !range.empty(); range.drop_first())
		{
			if (pred(range.front()))
				range.front() = new_value;
		}
	}

	template<class SinglePassRange, class OutputIterator, class T>
	OutputIterator replace_copy(SinglePassRange range, OutputIterator result, const T& old_value, const T& new_value)
	{
		return replace_copy_if(std::move(range), std::move(result),
							   [&](typename range_traits<SinglePassRange>::reference a) { return a == old_value; },
							   new_value);
	}

	template<class SinglePassRange, class OutputIterator, class Predicate, class T>
	OutputIterator replace_copy_if(SinglePassRange range, OutputIterator result, Predicate pred, const T& new_value)
	{
		for (; !range.empty(); range.drop_first())
			*result++ = pred(range.front()) ? new_value : range.front();

		return result;
	}

	template<class MultiPassRange, class T>
	void fill(MultiPassRange range, const T& value)
	{
		for (; !range.empty(); range.drop_first())
			range.front() = value;
	}

	template<class OutputRange, class Size, class T>
	OutputRange fill_n(OutputRange first, Size n, const T& value)
	{
		for (; !range.empty() && n > 0; range.drop_first(), --n)
			range.front() = value;

		return range;
	}

	template<class MultiPassRange, class Generator>
	void generate(MultiPassRange range, Generator gen)
	{
		for (; !range.empty(); range.drop_first())
			range.front() = gen();
	}

	template<class OutputRange, class Size, class Generator>
	OutputRange generate_n(OutputRange range, Size n, Generator gen)
	{
		for (; !range.empty() && n > 0; range.drop_first(), --n)
			range.front() = gen();

		return range;
	}

	template<class MultiPassRange, class T>
	MultiPassRange remove(MultiPassRange range, const T& value)
	{
		return remove_if(std::move(range), [&](typename std::iterator_traits<ForwardIterator>::reference a) { return a == value; });
	}

	template<class MultiPassRange, class Predicate>
	MultiPassRange remove_if(MultiPassRange range, Predicate pred)
	{
		auto r = range;
		for (; !r.empty(); r.drop_first())
		{
			if (pred(r.front()))
				break;
		}

		if (r.empty())
			return range;

		auto r2 = r;
		for (r2.drop_first(); !r2.empty(); r2.drop_first())
		{
			if (!pred(r2.front()))
			{
				r.front() = std::move(r2.front());
				r.drop_first();
			}
		}

		return range.drop_after(r.begin_pos());
	}

	template<class SinglePassRange, class OutputIterator, class T>
	OutputIterator remove_copy(SinglePassRange range, OutputIterator result, const T& value)
	{
		return remove_copy_if(std::move(range), std::move(result), [&](typename range_traits<SinglePassRange>::reference a) { return a == value; });
	}

	template<class SinglePassRange, class OutputIterator, class Predicate>
	OutputIterator remove_copy_if(SinglePassRange range, OutputIterator result, Predicate pred)
	{
		for (; !range.empty(); range.drop_first())
		{
			if (!pred(range.front()))
				*result++ = range.front();
		}

		return result;
	}

	template<class MultiPassRange>
	MultiPassRange unique(MultiPassRange range)
	{
		return unique(std::move(range), std::equal_to<>());
	}

	template<class MultiPassRange, class BinaryPredicate>
	MultiPassRange unique(MultiPassRange range, BinaryPredicate pred)
	{
		if (range.empty())
			return range;

		auto src = range;
		auto dest = range;

		src.drop_first();
		while (!src.empty())
		{
			src = find_if(src, [&](typename std::iterator_traits<ForwardIterator>::reference a) { return !pred(dest.front(), a); });
			dest.drop_first();
			if (found.empty())
			{
				range.keep_until(dest);
				return range.keep_until(dest);
			}

			dest.front() = std::move(src.front());
			src.drop_first();
		}

		dest.drop_first();
		range.drop_after(dest.begin_pos());
		return range;
	}

	template<class SinglePassRange, class OutputIterator>
	OutputIterator unique_copy(SinglePassRange range, OutputIterator result)
	{
		return unique_copy(std::move(range), std::move(result));
	}

	namespace detail
	{
		template <class SinglePassRange, class OutputIterator, class BinaryPredicate>
		OutputIterator unique_copy(SinglePassRange range, OutputIterator output, BinaryPredicate pred, single_pass_range_tag)
		{
			typename range_traits<SinglePassRange>::value_type value;
			while (!range.empty())
			{
				value = range.front();
				*output++ = value;

				for (range.drop_first(); !range.empty(); range.drop_first())
				{
					if (!pred(range.front(), value))
						break;
				}
			}

			return output;
		}

		template <class MultiPassRange, class OutputIterator, class BinaryPredicate>
		OutputIterator unique_copy(MultiPassRange range, OutputIterator output, BinaryPredicate pred, multi_pass_range_tag)
		{
			while (!range.empty())
			{
				*output++ = range.front();

				auto r = range;
				for (r.drop_first(); !r.empty(); r.drop_first())
				{
					if (!pred(range.front(), r.front()))
						break;
				}

				range = std::move(r);
			}

			return output;
		}
	}

	template<class SinglePassRange, class OutputIterator, class BinaryPredicate>
	OutputIterator unique_copy(SinglePassRange range, OutputIterator result, BinaryPredicate pred)
	{
		return detail::unique_copy(range, result, pred, typename range_traits<range>::range_category());
	}

	template<class DoubleEndedRange>
	void reverse(DoubleEndedRange range)
	{
		using std::swap;

		while (!range.empty())
		{
			if (&range.front() != &range.back())
				swap(range.front(), range.back());

			range.drop_first();
			if (!range.empty())
				range.drop_last();
		}
	}

	template<class DoubleEndedRange, class OutputIterator>
	OutputIterator reverse_copy(DoubleEndedRange range, OutputIterator result)
	{
		while (!range.empty())
		{
			*result++ = range.back();
			range.drop_last();
		}
	}

	template<class MultiPassRange>
	typename MultiPassRange::position_type rotate(MultiPassRange range, typename MultiPassRange::position_type middle)
	{
		using std::swap;

		if (middle == range.begin_pos())
			return range.end_pos();
		if (middle == range.end_pos())
			return range.begin_pos();

		auto first = range_before(range, middle);
		auto second = range_after(range, middle);
		auto saved = second;
		auto result = middle;
		while (!first.empty())
		{
			if (second.empty())
			{
				second = saved;
				if (result == middle)
					result = first.begin_pos();
			}

			swap(first.front(), second.front());
			first.drop_first();
			second.drop_first();
		}

		auto result2 = rotate(saved, second.begin_pos());
		return result == middle ? result2 : result;
	}

	template<class MultiPassRange, class OutputIterator>
	OutputIterator rotate_copy(MultiPassRange range, typename MultiPassRange::position_type middle, OutputIterator result)
	{
		auto first = range_before(range, middle);
		auto second = range_after(range, middle);
		for (; !second.empty(); second.drop_first())
			*result++ = second.front();
		for (; !first.empty(); first.drop_first())
			*result++ = first.front();

		return result;
	}

	namespace detail
	{
		extern std::default_random_engine random_engine;
	}

	template<class RandomAccessRange>
	void random_shuffle(RandomAccessRange range)
	{
		random_shuffle(std::move(range), detail::random_engine);
	}

	template<class RandomAccessRange, class RandomNumberGenerator>
	void random_shuffle(RandomAccessRange range, RandomNumberGenerator && rand)
	{
		using std::swap;

		for (; range.length() > 1; range.drop_first())
		{
			auto index = rand() % range.length();
			swap(range.front(), range[index]);
		}
	}

	template<class RandomAccessRange, class UniformRandomNumberGenerator>
	void shuffle(RandomAccessRange range, UniformRandomNumberGenerator && rand)
	{
		random_shuffle(std::move(range), std::forward<UniformRandomNumberGenerator>(rand));
	}

	template <class SinglePassRange, class Predicate>
	bool is_partitioned(SinglePassRange range, Predicate pred)
	{
		for (; !range.empty(); range.drop_first())
		{
			if (!pred(range.front()))
				break;
		}

		for (; !range.empty(); range.drop_first())
		{
			if (pred(range.front()))
				return false;
		}

		return true;
	}

	namespace detail
	{
		template<class MultiPassRange, class Predicate>
		typename range_traits<MultiPassRange>::position_type
			partition(MultiPassRange range, Predicate pred, multi_pass_range_tag)
		{
			using std::swap;

			for (; !range.empty(); range.drop_first())
			{
				if (!pred(range.front()))
					break;
			}

			if (range.empty())
				return range.end_pos();

			auto r = range;
			for (r.drop_first(); !r.empty(); r.drop_first())
			{
				if (pred(r.front()))
				{
					swap(range.front(), r.front());
					range.drop_first();
				}
			}

			return range.begin_pos();
		}

		template<class DoubleEndedRange, class Predicate>
		typename range_traits<DoubleEndedRange>::position_type
			partition(DoubleEndedRange range, Predicate pred, double_ended_range_tag)
		{
			using std::swap;

			while (!range.empty())
			{
				for (; !range.empty(); range.drop_first())
				{
					if (!pred(range.front()))
						break;
				}

				for (; !range.empty(); range.drop_last())
				{
					if (pred(range.back()))
						break;
				}

				if (!range.empty())
				{
					swap(range.front(), range.back());
					range.drop_first();
					range.drop_last();
				}
			}

			return range.begin_pos();
		}
	}

	template<class MultiPassRange, class Predicate>
	typename range_traits<MultiPassRange>::position_type partition(MultiPassRange range, Predicate pred)
	{
		return detail::partition(std::move(range), std::move(pred), typename range_traits<MultiPassRange>::range_category());
	}

	template<class DoubleEndedRange, class Predicate>
	typename range_traits<DoubleEndedRange>::position_type stable_partition(DoubleEndedRange range, Predicate pred)
	{
	}

	template <class SinglePassRange, class OutputIterator1, class OutputIterator2, class Predicate>
	std::pair<OutputIterator1, OutputIterator2>
		partition_copy(SinglePassRange range, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred)
	{
		for (; !range.empty(); range.drop_first())
		{
			if (pred(range.front()))
				*out_true++ = range.front();
			else
				*out_false++ = range.front();
		}

		return make_pair(out_true, out_false);
	}

	namespace detail
	{
		template<class MultiPassRange, class Predicate>
		typename range_traits<MultiPassRange>::position_type
			partition_point(MultiPassRange range, Predicate pred, multi_pass_range_tag)
		{
			auto length = range_length(range);
			while (length > 1)
			{
				auto offset = length / 2;
				auto r = range;
				r.drop_first(offset);
				if (pred(r.front()))
				{
					range = r;
					length -= offset;
				}
				else
				{
					range.drop_after(r.begin_pos());
					length = offset;
				}
			}

			if (range.length() == 1)
				return pred(range.front()) ? range.end_pos() : range.begin_pos();

			return range.begin_pos();
		}

		template<class RandomAccessRange, class Predicate>
		typename range_traits<RandomAccessRange>::position_type
			partition_point(RandomAccessRange range, Predicate pred, random_access_range_tag)
		{
			while (range.length() > 1)
			{
				auto pos = range.position_at(range.length() / 2);
				if (pred(range.at_pos(pos)))
					range.drop_before(pos);
				else
					range.drop_after(pos);
			}

			if (range.length() == 1)
				return pred(range.front()) ? range.end_pos() : range.begin_pos();

			return range.begin_pos();
		}
	}

	template<class MultiPassRange, class Predicate>
	typename range_traits<MultiPassRange>::position_type partition_point(MultiPassRange range, Predicate pred)
	{
		return detail::partition_point(std::move(range), std::move(pred), typename range_traits<MultiPassRange>::range_category());
	}

	template<class RandomAccessRange>
	void sort(RandomAccessRange range)
	{
		sort(std::move(range), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	void sort(RandomAccessRange range, Compare comp)
	{
		using std::swap;

		auto length = range.length();
		if (length > 2)
		{
			// Ranges typically start out either unsorted or mostly sorted; this makes
			// the first element a poor choice for a pivot.  The middle element will be
			// appropriate for both types of ranges.  Since comp(a, a) == false, just move
			// it to the end and then partition the rest of the range.
			swap(range[length / 2], range.back());
			auto& value = range.back();
			auto pivot = partition(range_before(range.position_at(length - 1)), [&](typename range_traits<RandomAccessRange>::reference a)
			{
				return comp(a, value);
			});
			sort(range_before(range, pivot), comp);
			sort(range_after(range, pivot), comp);
		}
		else if (length == 2)
		{
			if (!comp(range.front(), range.back()))
				swap(range.front(), range.back());
		}
	}

	template<class RandomAccessRange>
	void stable_sort(RandomAccessRange range)
	{
		return stable_sort(std::move(range), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	void stable_sort(RandomAccessRange range, Compare comp)
	{
		using std::swap;

		auto length = range.length();
		if (length > 2)
		{
			// Ranges typically start out either unsorted or mostly sorted; this makes
			// the first element a poor choice for a pivot.  The middle element will be
			// appropriate for both types of ranges.  Since comp(a, a) == false, just move
			// it to the end and then partition the rest of the range.
			swap(range[length / 2], range.back());
			auto& value = range.back();
			auto pivot = stable_partition(range_before(range.position_at(length - 1)), [&](typename range_traits<RandomAccessRange>::reference a)
			{
				return comp(a, value);
			});
			sort(range_before(range, pivot), comp);
			sort(range_after(range, pivot), comp);
		}
		else if (length == 2)
		{
			if (!comp(range.front(), range.back()))
				swap(range.front(), range.back());
		}
	}

	template<class RandomAccessRange>
	void partial_sort(RandomAccessRange range, typename range_traits<RandomAccessRange>::position_type middle)
	{
		partial_sort(std:move(range), std::move(middle), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	void partial_sort(RandomAccessRange range, typename range_traits<RandomAccessRange>::position_type middle, Compare comp)
	{
		using std::swap;

		auto length = range.length();
		if (length > 2)
		{
			// Ranges typically start out either unsorted or mostly sorted; this makes
			// the first element a poor choice for a pivot.  The middle element will be
			// appropriate for both types of ranges.  Since comp(a, a) == false, just move
			// it to the end and then partition the rest of the range.
			swap(range[length / 2], range.back());
			auto& value = range.back();
			auto pivot = partition(range_before(range.position_at(length - 1)), [&](typename range_traits<RandomAccessRange>::reference a)
			{
				return comp(a, value);
			});

			if (range.index_at(middle) < range.index_at(pivot))
				partial_sort(range_before(range, pivot), middle, comp);
			else
			{
				sort(range_before(range, pivot), comp);
				if (range.index_at(pivot) < range.index_at(middle))
					partial_sort(range_after(range, pivot), middle, comp);
			}
		}
		else if (length == 2)
		{
			if (!comp(range.front(), range.back()))
				swap(range.front(), range.back());
		}
	}

	template<class SinglePassRange, class RandomAccessRange>
	typename range_traits<RandomAccessRange>::position_type partial_sort_copy(SinglePassRange range, RandomAccessRange result_range)
	{
		return partial_sort_copy(std::move(range), std::move(result_range), std::less<>());
	}

	template<class SinglePassRange, class RandomAccessRange, class Compare>
	typename range_traits<RandomAccessRange>::position_type partial_sort_copy(SinglePassRange range, RandomAccessRange result_range, Compare comp)
	{
		// TODO: Make sure this meets the complexity requirements.
		std::partial_sort_copy
		if (range.empty() || result_range.empty())
			return result_range.begin_pos();

		auto r = result_range;
		for (; !range.empty() && !r.empty(); range.drop_first(), r.drop_first())
			r.front() = range.front();

		if (range.empty())
			result_range.drop_after(r.begin_pos());

		while (!range.empty())
		{
			auto greatest_pos = result_range.begin_pos();
			r = result_range;
			r.drop_front();

			for (; !r.empty(); r.drop_first())
			{
				if (!comp(r.front(), result_range.at_pos(greatest_pos)))
					greatest_pos = r.begin_pos();
			}

			for (; !range.empty(); range.drop_first())
			{
				if (comp(range.front()), result_range.at_pos(greatest_pos))
				{
					result_range.at_pos(greatest_pos) = range.front();
					break;
				}
			}
		}

		sort(result_range, comp);
	}

	template<class MultiPassRange>
	bool is_sorted(MultiPassRange range)
	{
		return is_sorted(std::move(range), std::less<>());
	}

	template<class MultiPassRange, class Compare>
	bool is_sorted(MultiPassRange range, Compare comp)
	{
		return is_sorted_until(range, comp) == range.end_pos();
	}

	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::position_type is_sorted_until(MultiPassRange range)
	{
		return is_sorted_until(std::move(range), std::less<>());
	}

	template<class MultiPassRange, class Compare>
	typename range_traits<MultiPassRange>::position_type is_sorted_until(MultiPassRange range, Compare comp)
	{
		if (range.empty())
			return range.end_pos();

		auto r = range;
		for (r.drop_first(); !r.empty(); range.drop_first, r.drop_first())
		{
			if (!comp(range.first(), r.first()))
				return r.begin_pos();
		}

		return r.end_pos();
	}

	template<class RandomAccessRange>
	void nth_element(RandomAccessRange range, typename range_traits<RandomAccessRange>::position_type nth)
	{
		nth_element(std::move(range), std::move(nth), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	void nth_element(RandomAccessRange range, typename range_traits<RandomAccessRange>::position_type nth, Compare comp)
	{
		using std::swap;

		auto length = range.length();
		if (length > 2)
		{
			// Ranges typically start out either unsorted or mostly sorted; this makes
			// the first element a poor choice for a pivot.  The middle element will be
			// appropriate for both types of ranges.  Since comp(a, a) == false, just move
			// it to the end and then partition the rest of the range.
			swap(range[length / 2], range.back());
			auto& value = range.back();
			auto pivot = partition(range_before(range.position_at(length - 1)), [&](typename range_traits<RandomAccessRange>::reference a)
			{
				return comp(a, value);
			});
			if (range.index_at(nth) < range.index_at(pivot))
				nth_element(range_before(range, pivot), nth, comp);
			else
				nth_element(range_after(range, pivot), nth, comp);
		}
		else if (length == 2)
		{
			if (!comp(range.front(), range.back()))
				swap(range.front(), range.back());
		}
	}

	template<class MultiPassRange, class T>
	typename range_traits<MultiPassRange>::position_type lower_bound(MultiPassRange range, const T& value)
	{
		return lower_bound(std::move(range), value, std::less<>());
	}

	template<class MultiPassRange, class T, class Compare>
	typename range_traits<MultiPassRange>::position_type lower_bound(MultiPassRange range, const T& value, Compare comp)
	{
		return partition_point(range, [&](typename range_traits<MultiPassRange>::reference a) { return comp(a, value); });
	}

	template<class MultiPassRange, class T>
	typename range_traits<MultiPassRange>::position_type upper_bound(MultiPassRange range, const T& value)
	{
		return upper_bound(std::move(range), value, std::less<>());
	}

	template<class MultiPassRange, class T, class Compare>
	typename range_traits<MultiPassRange>::position_type upper_bound(MultiPassRange range, const T& value, Compare comp)
	{
		return partition_point(range, [&](typename range_traits<MultiPassRange>::reference a) { return !comp(value, a); });
	}

	template<class MultiPassRange, class T>
	MultiPassRange equal_range(MultiPassRange range, const T& value)
	{
		return equal_range(std::move(range), value);
	}

	template<class MultiPassRange, class T, class Compare>
	MultiPassRange equal_range(MultiPassRange range, const T& value, Compare comp)
	{
		range.drop_before(lower_bound(range, value, comp));
		range.drop_after(upper_bound(range, value, comp));
		return range;
	}

	template<class MultiPassRange, class T>
	bool binary_search(MultiPassRange range, const T& value)
	{
		return binary_search(std::move(range), value);
	}

	template<class MultiPassRange, class T, class Compare>
	bool binary_search(MultiPassRange range, const T& value, Compare comp)
	{
		range.drop_before(lower_bound(range, value, comp));
		return !range.empty() && !comp(value, range.front());
	}

	template<class SinglePassRange1, class SinglePassRange2, class OutputIterator>
	OutputIterator merge(SinglePassRange1 range1, SinglePassRange2 range2, OutputIterator result)
	{
		return merge(std::move(rane1), std::move(range2), std::move(result), std::less<>());
	}

	template<class SinglePassRange1, class SinglePassRange2, class OutputIterator, class Compare>
	OutputIterator merge(SinglePassRange1 range1, SinglePassRange2 range2, OutputIterator result, Compare comp)
	{
		while (!range1.empty() && !range2.empty())
		{
			if (comp(range2.front(), range1.front()))
			{
				*result++ = range2.front();
				range2.drop_first();
			}
			else
			{
				*result++ = range1.front();
				range1.drop_first();
			}
		}

		if (range1.empty())
			result = copy(range2, result);
		else
			result = copy(range1, result);

		return result;
	}

	template<class DoubleEndedRange>
	void inplace_merge(DoubleEndedRange range, typename range_traits<DoubleEndedRange>::position_type middle)
	{
		return inplace_merge(std::move(range), std::move(middle), std::less<>());
	}

	template<class DoubleEndedRange, class Compare>
	void inplace_merge(DoubleEndedRange range, typename range_traits<DoubleEndedRange>::position_type middle, Compare comp)
	{
		auto length = range;
		try
		{
			auto elements = std::vector<typename range_traits<DoubleEndedRange>::value_type>(length);
			auto r1 = range_before(range, middle);
			auto r2 = range_after(range, middle);
			auto out = elements.begin();
			while (!r1.empty() && !r2.empty())
			{
				if (comp(r2.front(), r1.front()))
				{
					*out++ = std::move(r1.front());
					r1.drop_first();
				}
				else
				{
					*out++ = std::move(r2.front());
					r2.drop_first();
				}
			}

			while (!r1.empty())
			{
				*out++ = r1.front();
				r1.drop_first();
			}
			while (!r2.empty())
			{
				*out++ = r2.front();
				r2.drop_first();
			}

			std::move(elements.begin(), elements.end(), range_iterator(range));
		}
		catch (const std::bad_alloc&)
		{
		}
	}

	template<class SinglePassRange1, class InputRange2>
	bool includes(SinglePassRange1 range1, InputRange2 range2)
	{
		return includes(std::move(range1), std::move(range2), std::less<>());
	}

	template<class SinglePassRange1, class InputRange2, class Compare>
	bool includes(SinglePassRange1 range1, InputRange2 range2, Compare comp)
	{
		while (!range1.empty() && !range2.empty())
		{
			if (comp(range2.front(), range1.front()))
				return false;
			if (!comp(range1.front(), range2.front()))
				range2.drop_first();

			range1.drop_first();
		}

		return range2.empty();
	}

	template<class SinglePassRange1, class InputRange2, class OutputIterator>
	OutputIterator set_union(SinglePassRange1 range1, InputRange2 range2, OutputIterator result)
	{
		return set_union(std::move(range1), std::move(range2), std::move(result), std::less<>());
	}

	template<class SinglePassRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_union(SinglePassRange1 range1, InputRange2 range2, OutputIterator result, Compare comp)
	{
		while (!range1.empty() && !range2.empty())
		{
			if (comp(range1.front(), range2.front()))
			{
				*result++ = range1.front();
				range1.drop_first();
			}
			else if (comp(range2.front(), range1.front()))
			{
				*result++ = range2.front();
				range2.drop_first();
			}
			else
			{
				*result++ = range1.front();
				range1.drop_first();
				range2.drop_first();
			}
		}

		if (!range1.empty())
			return copy(std::move(range1), std::move(result));
		if (!range2.empty())
			return copy(std::move(range2), std::move(result));

		return result;
	}

	template<class SinglePassRange1, class InputRange2, class OutputIterator>
	OutputIterator set_intersection(SinglePassRange1 range1, InputRange2 range2, OutputIterator result)
	{
		return set_intersection(std::move(range1), std::move(range2), std::move(result), std::less<>());
	}

	template<class SinglePassRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_intersection(SinglePassRange1 range1, InputRange2 range2, OutputIterator result, Compare comp)
	{
		while (!range1.empty() && !range2.empty())
		{
			if (comp(range1.front(), range2.front()))
				range1.drop_first();
			else if (comp(range2.front(), range1.front()))
				range2.drop_first();
			else
			{
				*result++ = range1.front();
				range1.drop_first();
				range2.drop_first();
			}
		}

		return result;
	}

	template<class SinglePassRange1, class InputRange2, class OutputIterator>
	OutputIterator set_difference(SinglePassRange1 range1, InputRange2 range2, OutputIterator result)
	{
		return set_difference(std::move(range1), std::move(range2), std::move(result), std::less<>());
	}

	template<class SinglePassRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_difference(SinglePassRange1 range1, InputRange2 range2, OutputIterator result, Compare comp)
	{
		while (!range1.empty() && !range2.empty())
		{
			if (comp(range1.front(), range2.front()))
			{
				*result++ = range1.front();
				range1.drop_first();
			}
			else
			{
				if (!comp(range2.front(), range1.front()))
					range1.drop_first();
				range2.drop_first();
			}
		}

		while (!range1.empty())
		{
			*result++ = range1.front();
			range1.drop_first();
		}
	}

	template<class SinglePassRange1, class InputRange2, class OutputIterator>
	OutputIterator set_symmetric_difference(SinglePassRange1 range1, InputRange2 range2, OutputIterator result)
	{
		return set_symmetric_difference(std::move(range1), std::move(range2), std::move(result), std::less<>());
	}

	template<class SinglePassRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_symmetric_difference(SinglePassRange1 range1, InputRange2 range2, OutputIterator result, Compare comp)
	{
		while (!range1.empty() && !range2.empty())
		{
			if (comp(range1.front(), range2.front()))
			{
				*result++ = range1.front();
				range1.drop_first();
			}
			else if (comp(range2.front(), range1.front()))
			{
				*result++ = range2.front();
				range2.drop_first();
			}
			else
			{
				range1.drop_first();
				range2.drop_first();
			}
		}

		while (!range1.empty())
		{
			*result++ = range1.front();
			range1.drop_first();
		}

		while (!range2.empty())
		{
			*result++ = range2.front();
			range2.drop_first();
		}
	}

	template<class RandomAccessRange>
	void push_heap(RandomAccessRange range)
	{
		return push_heap(std::move(range), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	void push_heap(RandomAccessRange range, Compare comp)
	{
	}

	template<class RandomAccessRange>
	void pop_heap(RandomAccessRange range)
	{
		return pop_heap(std::move(range), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	void pop_heap(RandomAccessRange range, Compare comp)
	{
	}

	template<class RandomAccessRange>
	void make_heap(RandomAccessRange range)
	{
		return make_heap(std::move(range), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	void make_heap(RandomAccessRange range, Compare comp)
	{
	}

	template<class RandomAccessRange>
	void sort_heap(RandomAccessRange range)
	{
		return sort_heap(std::move(range), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	void sort_heap(RandomAccessRange range, Compare comp)
	{
	}

	template<class RandomAccessRange>
	bool is_heap(RandomAccessRange range)
	{
		return is_heap(std::move(range), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	bool is_heap(RandomAccessRange range, Compare comp)
	{
	}

	template<class RandomAccessRange>
	typename range_traits<RandomAccessRange>::position_type is_heap_until(RandomAccessRange range)
	{
		return is_heap_until(std::move(range), std::less<>());
	}

	template<class RandomAccessRange, class Compare>
	typename range_traits<RandomAccessRange>::position_type is_heap_until(RandomAccessRange range, Compare comp)
	{
	}

	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::position_type min_element(MultiPassRange range)
	{
		return min_element(std::move(range), std::less<>());
	}

	template<class MultiPassRange, class Compare>
	typename range_traits<MultiPassRange>::position_type min_element(MultiPassRange range, Compare comp)
	{
		if (range.empty())
			return range.end_pos();

		auto r = range;
		for (r.drop_first(); !r.empty(); r.drop_first())
		{
			if (comp(r.front(), range.front()))
				range.drop_before(r.begin_pos());
		}

		return range.begin_pos();
	}

	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::position_type max_element(MultiPassRange range)
	{
		return max_element(std::move(range), std::less<>());
	}

	template<class MultiPassRange, class Compare>
	typename range_traits<MultiPassRange>::position_type max_element(MultiPassRange range, Compare comp)
	{
		if (range.empty())
			return range.end_pos();

		auto r = range;
		for (r.drop_first(); !r.empty(); r.drop_first())
		{
			if (comp(range.front(), r.front()))
				range.drop_before(r.begin_pos());
		}

		return range.begin_pos();
	}

	template<class MultiPassRange>
	std::pair<typename range_traits<MultiPassRange>::position_type, typename range_traits<MultiPassRange>::position_type>
		minmax_element(MultiPassRange range)
	{
		return minmax_element(std::move(range), std::less<>());
	}

	template<class MultiPassRange, class Compare>
	std::pair<typename range_traits<MultiPassRange>::position_type, typename range_traits<MultiPassRange>::position_type>
		minmax_element(MultiPassRange range, Compare comp)
	{
		if (range.empty())
			return std::make_pair(range.begin_pos(), range.begin_pos());

		auto min_range = range;
		auto max_range = range;
		for (range.drop_first(); !range.empty(); range.drop_first())
		{
			if (comp(range.front(), min_range.front()))
				min_range.drop_before(range.begin_pos());
			if (comp(max_range.front(), range.front()))
				max_range.drop_before(range.begin_pos());
		}

		return std::make_pair(min_range.begin_pos(), max_range.begin_pos());
	}

	template<class SinglePassRange1, class SinglePassRange2>
	bool lexicographical_compare(SinglePassRange1 range1, SinglePassRange2 range2)
	{
		return lexicographical_compare(std::move(range1), std::move(range2), std::less<>());
	}

	template<class SinglePassRange1, class SinglePassRange2, class Compare>
	bool lexicographical_compare(SinglePassRange1 range1, SinglePassRange2 range2, Compare comp)
	{
		for (; !range1.empty() && !range2.empty(); range1.drop_first(), range2.drop_first())
		{
			if (comp(range1.front(), range2.front()))
				return true;
			if (comp(range2.front(), range1.front()))
				return false;
		}

		return !range2.empty();
	}

	template<class DoubleEndedRange>
	bool next_permutation(DoubleEndedRange range)
	{
		return next_permutation(std::move(range), std::less<>())
	}

	template<class DoubleEndedRange, class Compare>
	bool next_permutation(DoubleEndedRange range, Compare comp)
	{
		using std::swap;

		if (range.empty())
			return false;

		auto r1 = range, r2 = range;
		for (r1.drop_last(); !r1.empty(); r1.drop_last(), r2.drop_last())
		{
			if (comp(r.front(), r2.front()))
			{
				swap(r.front(), r2.front());
				range.drop_before(r2.begin_pos());
				range.drop_first();
				sort(std::move(range), std::move(comp));
				return true;
			}
		}

		reverse(std::move(range));
		return false;
	}

	template<class DoubleEndedRange>
	bool prev_permutation(DoubleEndedRange range)
	{
		return prev_permutation(std::move(range), std::less<>());
	}

	template<class DoubleEndedRange, class Compare>
	bool prev_permutation(DoubleEndedRange range, Compare comp)
	{
		using std::swap;

		if (range.empty())
			return false;

		auto r1 = range, r2 = range;
		for (r1.drop_last(); !r1.empty(); r1.drop_last(), r2.drop_last())
		{
			if (comp(r2.front(), r.front()))
			{
				swap(r.front(), r2.front());
				range.drop_before(r2.begin_pos());
				range.drop_first();
				sort(std::move(range), std::move(comp));
				return true;
			}
		}

		reverse(std::move(range));
		return false;
	}
}