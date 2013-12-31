#include <algorithm>
#include <functional>
#include <iterator>
#include <random>
#include <utility>
#include <vector>

namespace stdext
{
	// 25.2, non-modifying sequence operations:
	template <class InputRange, class Predicate>
	bool all_of(const InputRange& range, Predicate pred)
	{
		return std::all_of(range_iterator<InputRange>(range, range.begin_pos()),
						   range_iterator<InputRange>(range, range.end_pos()),
						   pred);
	}

	template <class InputRange, class Predicate>
	bool any_of(const InputRange& range, Predicate pred)
	{
		return std::any_of(range_iterator<InputRange>(range, range.begin_pos()),
						   range_iterator<InputRange>(range, range.end_pos()),
						   pred);
	}

	template <class InputRange, class Predicate>
	bool none_of(const InputRange& range, Predicate pred)
	{
		return std::none_of(range_iterator<InputRange>(range, range.begin_pos()),
							range_iterator<InputRange>(range, range.end_pos()),
							pred);
	}

	template<class InputRange, class Function>
	Function for_each(const InputRange& range, Function f)
	{
		return std::for_each(range_iterator<InputRange>(range, range.begin_pos()),
							 range_iterator<InputRange>(range, range.end_pos()),
							 f);
	}

	template<class InputRange, class T>
	typename range_traits<InputRange>::position_type find(const InputRange& range, const T& value)
	{
		return std::find(range_iterator<InputRange>(range, range.begin_pos()),
						 range_iterator<InputRange>(range, range.end_pos()),
						 value).pos();
	}

	template<class InputRange, class Predicate>
	typename range_traits<InputRange>::position_type find_if(const InputRange& range, Predicate pred)
	{
		return std::find_if(range_iterator<InputRange>(range, range.begin_pos()),
							range_iterator<InputRange>(range, range.end_pos()),
							pred).pos();
	}

	template<class InputRange, class Predicate>
	typename range_traits<InputRange>::position_type find_if_not(const InputRange& range, Predicate pred)
	{
		return std::find_if_not(range_iterator<InputRange>(range, range.begin_pos()),
								range_iterator<InputRange>(range, range.end_pos()),
								pred).pos();
	}

	template<class ForwardRange1, class ForwardRange2>
	typename range_traits<ForwardRange1>::position_type find_end(const ForwardRange1& range1, const ForwardRange2& range2)
	{
		return std::find_end(range_iterator<ForwardRange1>(range1, range1.begin_pos()),
							 range_iterator<ForwardRange1>(range1, range1.end_pos()),
							 range_iterator<ForwardRange2>(range2, range2.begin_pos()),
							 range_iterator<ForwardRange2>(range2, range2.end_pos())).pos();
	}

	template<class ForwardRange1, class ForwardRange2, class BinaryPredicate>
	typename range_traits<ForwardRange1>::position_type find_end(const ForwardRange1& range1, const ForwardRange2& range2, BinaryPredicate pred)
	{
		return std::find_end(range_iterator<ForwardRange1>(range1, range1.begin_pos()),
							 range_iterator<ForwardRange1>(range1, range1.end_pos()),
							 range_iterator<ForwardRange2>(range2, range2.begin_pos()),
							 range_iterator<ForwardRange2>(range2, range2.end_pos()),
							 pred).pos();
	}

	template<class InputRange, class ForwardRange>
	typename range_traits<InputRange>::position_type find_first_of(const InputRange& range1, const ForwardRange& range2)
	{
		return std::find_first_of(range_iterator<InputRange>(range1, range1.begin_pos()),
								  range_iterator<InputRange>(range1, range1.end_pos()),
								  range_iterator<InputRange>(range2, range2.begin_pos()),
								  range_iterator<InputRange>(range2, range2.end_pos())).pos();
	}

	template<class InputRange, class ForwardRange, class BinaryPredicate>
	typename range_traits<InputRange>::position_type find_first_of(const InputRange& range1, const ForwardRange& range2, BinaryPredicate pred)
	{
		return std::find_first_of(range_iterator<InputRange>(range1, range1.begin_pos()),
								  range_iterator<InputRange>(range1, range1.end_pos()),
								  range_iterator<InputRange>(range2, range2.begin_pos()),
								  range_iterator<InputRange>(range2, range2.end_pos()),
								  pred).pos();
	}

	template<class ForwardRange>
	typename range_traits<ForwardRange>::position_type adjacent_find(const ForwardRange& range)
	{
		return std::adjacent_find(range_iterator<ForwardRange>(range, range.begin_pos()),
								  range_iterator<ForwardRange>(range, range.end_pos())).pos();
	}

	template<class ForwardRange, class BinaryPredicate>
	typename range_traits<ForwardRange>::position_type adjacent_find(const ForwardRange& range, BinaryPredicate pred)
	{
		return std::adjacent_find(range_iterator<ForwardRange>(range, range.begin_pos()),
								  range_iterator<ForwardRange>(range, range.end_pos()),
								  pred).pos();
	}

	template<class InputRange, class T>
	typename range_traits<InputRange>::difference_type count(const InputRange& range, const T& value)
	{
		return std::count(range_iterator<InputRange>(range, range.begin_pos()),
						  range_iterator<InputRange>(range, range.end_pos()),
						  value);
	}

	template<class InputRange, class Predicate>
	typename range_traits<InputRange>::difference_type count_if(const InputRange& range, Predicate pred)
	{
		return std::count_if(range_iterator<InputRange>(range, range.begin_pos()),
							 range_iterator<InputRange>(range, range.end_pos()),
							 pred);
	}

	template<class InputRange, class InputIterator>
	std::pair<typename range_traits<InputRange>::position_type, InputIterator>
		mismatch(const InputRange& range1, InputIterator first2)
	{
		auto std_r = std::mismatch(range_iterator<InputRange>(range1, range1.begin_pos()),
								   range_iterator<InputRange>(range1, range1.end_pos()),
								   first2);
		return std::make_pair(std_r.first.pos(), std_r.second);
	}

	template <class InputRange, class InputIterator, class BinaryPredicate>
	std::pair<typename range_traits<InputRange>::position_type, InputIterator>
		mismatch(const InputRange& range1, InputIterator first2, BinaryPredicate pred)
	{
		auto std_r = std::mismatch(range_iterator<InputRange>(range1, range1.begin_pos()),
								   range_iterator<InputRange>(range1, range1.end_pos()),
								   first2, pred);
		return std::make_pair(std_r.first.pos(), std_r.second);
	}

	template<class InputRange1, class InputRange2>
	std::pair<typename range_traits<InputRange1>::position_type, typename range_traits<InputRange2>::position_type>
		mismatch_ranges(const InputRange1& range1, const InputRange2& range2)
	{
		return mismatch_ranges(range1, range2, [](typename stdext::range_traits<InputRange1>::reference a, typename stdext::range_traits<InputRange2>::reference b) { return a == b; });
	}

	template<class InputRange1, class InputRange2, class BinaryPredicate>
	std::pair<typename range_traits<InputRange1>::position_type, typename range_traits<InputRange2>::position_type>
		mismatch_ranges(const InputRange1& range1, const InputRange2& range2, BinaryPredicate pred)
	{
		auto p1 = range1.begin_pos(), p1_last = range1.end_pos();
		auto p2 = range2.begin_pos(), p2_last = range2.end_pos();
		for (; p1 != p1_last && p2 != p2_last; range1.increment_pos(p1), range2.increment_pos(p2))
		{
			if (!pred(range1.at_pos(p1), range2.at_pos(p2)))
				break;
		}
		return std::make_pair(p1, p2);
	}

	template<class InputRange1, class InputIterator2>
	typename std::enable_if<!is_range<InputIterator2>::value, bool>::type
		equal(const InputRange1& range1, InputIterator2 first2)
	{
		return std::equal(range_iterator<InputRange1>(range1, range1.begin_pos()),
						  range_iterator<InputRange1>(range1, range1.end_pos()),
						  first2);
	}

	template <class InputRange1, class InputIterator2, class BinaryPredicate>
	typename std::enable_if<!is_range<InputIterator2>::value, bool>::type
		equal(const InputRange1& range1, InputIterator2 first2, BinaryPredicate pred)
	{
		return std::equal(range_iterator<InputRange1>(range1, range1.begin_pos()),
						  range_iterator<InputRange1>(range1, range1.end_pos()),
						  first2, pred);
	}

	template<class InputRange1, class InputRange2>
	typename std::enable_if<is_range<InputRange2>::value, bool>::type
		equal(const InputRange1& range1, const InputRange2& range2)
	{
		return equal(range1, range2, [](typename range_traits<InputRange1>::reference a, typename range_traits<InputRange2>::reference b) { return a == b; });
	}

	template<class InputRange1, class InputRange2, class BinaryPredicate>
	typename std::enable_if<is_range<InputRange2>::value, bool>::type
		equal(const InputRange1& range1, const InputRange2& range2, BinaryPredicate pred)
	{
		auto positions = mismatch(range1, range2, pred);
		return positions.first == range1.end_pos()
			&& positions.second == range2.end_pos();
	}

	template<class ForwardRange1, class ForwardIterator2>
	typename std::enable_if<!is_range<ForwardIterator2>::value, bool>::type
		is_permutation(const ForwardRange1& range1, ForwardIterator2 first2)
	{
		return std::is_permutation(range_iterator<ForwardRange1>(range1, range1.begin_pos()),
								   range_iterator<ForwardRange1>(range1, range1.end_pos()),
								   first2);
	}

	template<class ForwardRange1, class ForwardIterator2, class BinaryPredicate>
	typename std::enable_if<!is_range<ForwardIterator2>::value, bool>::type
		is_permutation(const ForwardRange1& range1, ForwardIterator2 first2, BinaryPredicate pred)
	{
		return std::is_permutation(range_iterator<ForwardRange1>(range1, range1.begin_pos()),
								   range_iterator<ForwardRange1>(range1, range1.end_pos()),
								   first2, pred);
	}

	template<class ForwardRange1, class ForwardRange2>
	typename std::enable_if<is_range<ForwardRange2>::value, bool>::type
		is_permutation(const ForwardRange1& range1, const ForwardRange2& range2)
	{
		return is_permutation(range1, range2, [](typename range_traits<ForwardRange1>::reference a, typename range_traits<ForwardRange2>::reference b) { return a == b; });
	}

	template<class ForwardRange1, class ForwardRange2, class BinaryPredicate>
	typename std::enable_if<is_range<ForwardRange2>::value, bool>::type
		is_permutation(const ForwardRange1& range1, const ForwardRange2& range2, BinaryPredicate pred)
	{
		if (length(range1) != length(range2))
			return false;

		return std::is_permutation(range_iterator<ForwardRange1>(range1, range1.begin_pos()),
								   range_iterator<ForwardRange1>(range1, range1.end_pos()),
								   range_iterator<ForwardRange2>(range2, range2.begin_pos()),
								   pred);
	}

	template<class ForwardRange1, class ForwardRange2>
	typename range_traits<ForwardRange1>::position_type search(const ForwardRange1& range1, const ForwardRange2& range2)
	{
		return std::search(range_iterator<ForwardRange1>(range1, range1.begin_pos()),
						   range_iterator<ForwardRange1>(range1, range1.end_pos()),
						   range_iterator<ForwardRange2>(range2, range2.begin_pos()),
						   range_iterator<ForwardRange2>(range2, range2.end_pos())).pos();
	}

	template<class ForwardRange1, class ForwardRange2, class BinaryPredicate>
	typename range_traits<ForwardRange1>::position_type search(const ForwardRange1& range1, const ForwardRange2& range2, BinaryPredicate pred)
	{
		return std::search(range_iterator<ForwardRange1>(range1, range1.begin_pos()),
						   range_iterator<ForwardRange1>(range1, range1.end_pos()),
						   range_iterator<ForwardRange2>(range2, range2.begin_pos()),
						   range_iterator<ForwardRange2>(range2, range2.end_pos()),
						   pred).pos();
	}

	template<class ForwardRange, class Size, class T>
	typename range_traits<ForwardRange>::position_type search_n(const ForwardRange& range, Size count, const T& value)
	{
		return std::search_n(range_iterator<ForwardRange>(range, range.begin_pos()),
							 range_iterator<ForwardRange>(range, range.end_pos()),
							 count, value).pos();
	}

	template <class ForwardRange, class Size, class T, class BinaryPredicate>
	typename range_traits<ForwardRange>::position_type search_n(const ForwardRange& range, Size count, const T& value, BinaryPredicate pred)
	{
		return std::search_n(range_iterator<ForwardRange>(range, range.begin_pos()),
							 range_iterator<ForwardRange>(range, range.end_pos()),
							 count, value, pred).pos();
	}

	template<class InputRange, class OutputIterator>
	OutputIterator copy(const InputRange& range, OutputIterator result)
	{
		return std::copy(range_iterator<InputRange>(range, range.begin_pos()),
						 range_iterator<InputRange>(range, range.end_pos()),
						 result);
	}

	template<class InputRange, class Size, class OutputIterator>
	OutputIterator copy_n(const InputRange& range, Size n, OutputIterator result)
	{
		return std::copy_n(range_iterator<InputRange>(range, range.begin_pos()),
						   n, result);
	}

	template<class InputRange, class OutputIterator, class Predicate>
	OutputIterator copy_if(const InputRange& range, OutputIterator result, Predicate pred)
	{
		return std::copy_if(range_iterator<InputRange>(range, range.begin_pos()),
							range_iterator<InputRange>(range, range.end_pos()),
							result, pred);
	}

	template<class BidirectionalRange1, class BidirectionalIterator2>
	BidirectionalIterator2 copy_backward(BidirectionalRange1 range, BidirectionalIterator2 result)
	{
		return std::copy_backward(range_iterator<BidirectionalRange1>(range, range.begin_pos()),
								  range_iterator<BidirectionalRange1>(range, range.end_pos()),
								  result);
	}

	template<class InputRange, class OutputIterator>
	OutputIterator move(const InputRange& range, OutputIterator result)
	{
		return std::move(range_iterator<InputRange>(range, range.begin_pos()),
						 range_iterator<InputRange>(range, range.end_pos()),
						 result);
	}

	template<class BidirectionalRange1, class BidirectionalIterator2>
	BidirectionalIterator2 move_backward(BidirectionalRange1 range, BidirectionalIterator2 result)
	{
		return std::move_backward(range_iterator<BidirectionalRange1>(range, range.begin_pos()),
								  range_iterator<BidirectionalRange1>(range, range.end_pos()),
								  result);
	}

	template<class ForwardRange1, class ForwardIterator2>
	ForwardIterator2 swap_ranges(const ForwardRange1& range1, ForwardIterator2 first2)
	{
		return std::swap_ranges(range_iterator<ForwardRange1>(range1, range1.begin_pos()),
								range_iterator<ForwardRange1>(range1, range1.end_pos()),
								first2);
	}

	template<class InputRange, class OutputIterator, class UnaryOperation>
	OutputIterator transform(const InputRange& range, OutputIterator result, UnaryOperation op)
	{
		return std::transform(range_iterator<InputRange>(range, range.begin_pos()),
							  range_iterator<InputRange>(range, range.end_pos()),
							  result, op);
	}

	template<class InputRange1, class InputIterator2, class OutputIterator, class BinaryOperation>
	OutputIterator transform(const InputRange1& range1, InputIterator2 first2, OutputIterator result, BinaryOperation binary_op)
	{
		return std::transform(range_iterator<InputRange1>(range1, range1.begin_pos()),
							  range_iterator<InputRange1>(range1, range1.end_pos()),
							  first2, result, binary_op);
	}

	template<class ForwardRange, class T>
	void replace(const ForwardRange& range, const T& old_value, const T& new_value)
	{
		std::replace(range_iterator<ForwardRange>(range, range.begin_pos()),
					 range_iterator<ForwardRange>(range, range.end_pos()),
					 old_value, new_value);
	}

	template<class ForwardRange, class Predicate, class T>
	void replace_if(const ForwardRange& range, Predicate pred, const T& new_value)
	{
		std::replace_if(range_iterator<ForwardRange>(range, range.begin_pos()),
						range_iterator<ForwardRange>(range, range.end_pos()),
						pred, new_value);
	}

	template<class InputRange, class OutputIterator, class T>
	OutputIterator replace_copy(const InputRange& range, OutputIterator result, const T& old_value, const T& new_value)
	{
		return std::replace_copy(range_iterator<InputRange>(range, range.begin_pos()),
								 range_iterator<InputRange>(range, range.end_pos()),
								 result, old_value, new_value);
	}

	template<class InputRange, class OutputIterator, class Predicate, class T>
	OutputIterator replace_copy_if(const InputRange& range, OutputIterator result, Predicate pred, const T& new_value)
	{
		return std::replace_copy_if(range_iterator<InputRange>(range, range.begin_pos()),
									range_iterator<InputRange>(range, range.end_pos()),
									result, pred, new_value);
	}

	template<class ForwardRange, class T>
	void fill(const ForwardRange& range, const T& value)
	{
		std::fill(range_iterator<ForwardRange>(range, range.begin_pos()),
				  range_iterator<ForwardRange>(range, range.end_pos()),
				  value);
	}

	template<class OutputRange, class Size, class T>
	OutputRange fill_n(OutputRange range, Size n, const T& value)
	{
		return std::fill_n(range_iterator<OutputRange>(range, range.begin_pos()),
						   n, value);
	}

	template<class ForwardRange, class Generator>
	void generate(const ForwardRange& range, Generator gen)
	{
		std::generate(range_iterator<ForwardRange>(range, range.begin_pos()),
					  range_iterator<ForwardRange>(range, range.end_pos()),
					  gen);
	}

	template<class OutputRange, class Size, class Generator>
	typename range_traits<OutputRange>::position_type generate_n(OutputRange range, Size n, Generator gen)
	{
		return std::generate_n(range_iterator<OutputRange>(range, range.begin_pos()),
							   n, gen).pos();
	}

	template<class ForwardRange, class T>
	typename range_traits<ForwardRange>::position_type remove(const ForwardRange& range, const T& value)
	{
		return std::remove(range_iterator<ForwardRange>(range, range.begin_pos()),
						   range_iterator<ForwardRange>(range, range.end_pos()),
						   value).pos();
	}

	template<class ForwardRange, class Predicate>
	typename range_traits<ForwardRange>::position_type remove_if(const ForwardRange& range, Predicate pred)
	{
		return std::remove_if(range_iterator<ForwardRange>(range, range.begin_pos()),
							  range_iterator<ForwardRange>(range, range.end_pos()),
							  pred).pos();
	}

	template<class InputRange, class OutputIterator, class T>
	OutputIterator remove_copy(const InputRange& range, OutputIterator result, const T& value)
	{
		return std::remove_copy(range_iterator<InputRange>(range, range.begin_pos()),
								range_iterator<InputRange>(range, range.end_pos()),
								result, value);
	}

	template<class InputRange, class OutputIterator, class Predicate>
	OutputIterator remove_copy_if(const InputRange& range, OutputIterator result, Predicate pred)
	{
		return std::remove_copy_if(range_iterator<InputRange>(range, range.begin_pos()),
								   range_iterator<InputRange>(range, range.end_pos()),
								   result, pred);
	}

	template<class ForwardRange>
	typename range_traits<ForwardRange>::position_type unique(const ForwardRange& range)
	{
		return std::unique(range_iterator<ForwardRange>(range, range.begin_pos()),
						   range_iterator<ForwardRange>(range, range.end_pos())).pos();
	}

	template<class ForwardRange, class BinaryPredicate>
	typename range_traits<ForwardRange>::position_type unique(const ForwardRange& range, BinaryPredicate pred)
	{
		return std::unique(range_iterator<ForwardRange>(range, range.begin_pos()),
						   range_iterator<ForwardRange>(range, range.end_pos()),
						   pred).pos();
	}

	template<class InputRange, class OutputIterator>
	OutputIterator unique_copy(const InputRange& range, OutputIterator result)
	{
		return std::unique_copy(range_iterator<InputRange>(range, range.begin_pos()),
								range_iterator<InputRange>(range, range.end_pos()),
								result);
	}

	template<class InputRange, class OutputIterator, class BinaryPredicate>
	OutputIterator unique_copy(const InputRange& range, OutputIterator result, BinaryPredicate pred)
	{
		return std::unique_copy(range_iterator<InputRange>(range, range.begin_pos()),
								range_iterator<InputRange>(range, range.end_pos()),
								result, pred);
	}

	template<class BidirectionalRange>
	void reverse(const BidirectionalRange& range)
	{
		std::reverse(range_iterator<BidirectionalRange>(range, range.begin_pos()),
					 range_iterator<BidirectionalRange>(range, range.end_pos()));
	}

	template<class BidirectionalRange, class OutputIterator>
	OutputIterator reverse_copy(const BidirectionalRange& range, OutputIterator result)
	{
		return std::reverse_copy(range_iterator<BidirectionalRange>(range, range.begin_pos()),
								 range_iterator<BidirectionalRange>(range, range.end_pos()),
								 result);
	}

	template<class ForwardRange>
	typename range_traits<ForwardRange>::position_type rotate(const ForwardRange& range, typename range_traits<ForwardRange>::position_type middle)
	{
		return std::rotate(range_iterator<ForwardRange>(range, range.begin_pos()),
						   range_iterator<ForwardRange>(range, middle),
						   range_iterator<ForwardRange>(range, range.end_pos())).pos();
	}

	template<class ForwardRange, class OutputIterator>
	OutputIterator rotate_copy(const ForwardRange& range, typename range_traits<ForwardRange>::position_type middle, OutputIterator result)
	{
		return std::rotate_copy(range_iterator<ForwardRange>(range, range.begin_pos()),
								range_iterator<ForwardRange>(range, middle),
								range_iterator<ForwardRange>(range, range.end_pos()),
								result);
	}

	template<class RandomAccessRange>
	void random_shuffle(const RandomAccessRange& range)
	{
		std::random_shuffle(range_iterator<RandomAccessRange>(range, range.begin_pos()),
							range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class RandomNumberGenerator>
	void random_shuffle(const RandomAccessRange& range, RandomNumberGenerator&& rand)
	{
		std::random_shuffle(range_iterator<RandomAccessRange>(range, range.begin_pos()),
							range_iterator<RandomAccessRange>(range, range.end_pos()),
							std::forward<RandomNumberGenerator>(rand));
	}

	template<class RandomAccessRange, class UniformRandomNumberGenerator>
	void shuffle(const RandomAccessRange& range, UniformRandomNumberGenerator&& rand)
	{
		std::shuffle(range_iterator<RandomAccessRange>(range, range.begin_pos()),
					 range_iterator<RandomAccessRange>(range, range.end_pos()),
					 std::forward<UniformRandomNumberGenerator>(rand));
	}

	template <class InputRange, class Predicate>
	bool is_partitioned(const InputRange& range, Predicate pred)
	{
		return std::is_partitioned(range_iterator<InputRange>(range, range.begin_pos()),
								   range_iterator<InputRange>(range, range.end_pos()),
								   pred);
	}

	template<class ForwardRange, class Predicate>
	typename range_traits<ForwardRange>::position_type partition(const ForwardRange& range, Predicate pred)
	{
		return std::partition(range_iterator<ForwardRange>(range, range.begin_pos()),
							  range_iterator<ForwardRange>(range, range.end_pos()),
							  pred).pos();
	}

	template<class BidirectionalRange, class Predicate>
	typename range_traits<BidirectionalRange>::position_type stable_partition(const BidirectionalRange& range, Predicate pred)
	{
		return std::stable_partition(range_iterator<BidirectionalRange>(range, range.begin_pos()),
									 range_iterator<BidirectionalRange>(range, range.end_pos()),
									 pred).pos();
	}

	template <class InputRange, class OutputIterator1, class OutputIterator2, class Predicate>
	std::pair<OutputIterator1, OutputIterator2>
		partition_copy(const InputRange& range, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred)
	{
		return std::partition_copy(range_iterator<InputRange>(range, range.begin_pos()),
									range_iterator<InputRange>(range, range.end_pos()),
									out_true, out_false, pred);
	}

	template<class ForwardRange, class Predicate>
	typename range_traits<ForwardRange>::position_type partition_point(const ForwardRange& range, Predicate pred)
	{
		return std::partition_point(range_iterator<ForwardRange>(range, range.begin_pos()),
									range_iterator<ForwardRange>(range, range.end_pos()),
									pred).pos();
	}

	template<class RandomAccessRange>
	void sort(const RandomAccessRange& range)
	{
		std::sort(range_iterator<RandomAccessRange>(range, range.begin_pos()),
				  range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class Compare>
	void sort(const RandomAccessRange& range, Compare comp)
	{
		std::sort(range_iterator<RandomAccessRange>(range, range.begin_pos()),
				  range_iterator<RandomAccessRange>(range, range.end_pos()),
				  comp);
	}

	template<class RandomAccessRange>
	void stable_sort(const RandomAccessRange& range)
	{
		std::stable_sort(range_iterator<RandomAccessRange>(range, range.begin_pos()),
						 range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class Compare>
	void stable_sort(const RandomAccessRange& range, Compare comp)
	{
		std::stable_sort(range_iterator<RandomAccessRange>(range, range.begin_pos()),
						 range_iterator<RandomAccessRange>(range, range.end_pos()),
						 comp);
	}

	template<class RandomAccessRange>
	void partial_sort(const RandomAccessRange& range, typename range_traits<RandomAccessRange>::position_type middle)
	{
		std::partial_sort(range_iterator<RandomAccessRange>(range, range.begin_pos()),
						  range_iterator<RandomAccessRange>(range, middle),
						  range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class Compare>
	void partial_sort(const RandomAccessRange& range, typename range_traits<RandomAccessRange>::position_type middle, Compare comp)
	{
		std::partial_sort(range_iterator<RandomAccessRange>(range, range.begin_pos()),
						  range_iterator<RandomAccessRange>(range, middle),
						  range_iterator<RandomAccessRange>(range, range.end_pos()),
						  comp);
	}

	template<class InputRange, class RandomAccessRange>
	typename range_traits<RandomAccessRange>::position_type partial_sort_copy(const InputRange& range, RandomAccessRange result_range)
	{
		return std::partial_sort_copy(range_iterator<InputRange>(range, range.begin_pos()),
									  range_iterator<InputRange>(range, range.end_pos()),
									  range_iterator<RandomAccessRange>(result_range, result_range.begin_pos()),
									  range_iterator<RandomAccessRange>(result_range, result_range.end_pos())).pos();
	}

	template<class InputRange, class RandomAccessRange, class Compare>
	typename range_traits<RandomAccessRange>::position_type partial_sort_copy(const InputRange& range, RandomAccessRange result_range, Compare comp)
	{
		return std::partial_sort_copy(range_iterator<InputRange>(range, range.begin_pos()),
									  range_iterator<InputRange>(range, range.end_pos()),
									  range_iterator<RandomAccessRange>(result_range, result_range.begin_pos()),
									  range_iterator<RandomAccessRange>(result_range, result_range.end_pos()),
									  comp).pos();
	}

	template<class ForwardRange>
	bool is_sorted(const ForwardRange& range)
	{
		return std::is_sorted(range_iterator<ForwardRange>(range, range.begin_pos()),
							  range_iterator<ForwardRange>(range, range.end_pos()));
	}

	template<class ForwardRange, class Compare>
	bool is_sorted(const ForwardRange& range, Compare comp)
	{
		return std::is_sorted(range_iterator<ForwardRange>(range, range.begin_pos()),
							  range_iterator<ForwardRange>(range, range.end_pos()),
							  comp);
	}

	template<class ForwardRange>
	typename range_traits<ForwardRange>::position_type is_sorted_until(const ForwardRange& range)
	{
		return std::is_sorted_until(range_iterator<ForwardRange>(range, range.begin_pos()),
									range_iterator<ForwardRange>(range, range.end_pos())).pos();
	}

	template<class ForwardRange, class Compare>
	typename range_traits<ForwardRange>::position_type is_sorted_until(const ForwardRange& range, Compare comp)
	{
		return std::is_sorted_until(range_iterator<ForwardRange>(range, range.begin_pos()),
									range_iterator<ForwardRange>(range, range.end_pos()),
									comp).pos();
	}

	template<class RandomAccessRange>
	void nth_element(const RandomAccessRange& range, typename range_traits<RandomAccessRange>::position_type nth)
	{
		std::nth_element(range_iterator<RandomAccessRange>(range, range.begin_pos()),
						 range_iterator<RandomAccessRange>(range, nth),
						 range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class Compare>
	void nth_element(const RandomAccessRange& range, typename range_traits<RandomAccessRange>::position_type nth, Compare comp)
	{
		std::nth_element(range_iterator<RandomAccessRange>(range, range.begin_pos()),
						 range_iterator<RandomAccessRange>(range, nth),
						 range_iterator<RandomAccessRange>(range, range.end_pos()),
						 comp);
	}

	template<class ForwardRange, class T>
	typename range_traits<ForwardRange>::position_type lower_bound(const ForwardRange& range, const T& value)
	{
		return std::lower_bound(range_iterator<ForwardRange>(range, range.begin_pos()),
								range_iterator<ForwardRange>(range, range.end_pos()),
								value).pos();
	}

	template<class ForwardRange, class T, class Compare>
	typename range_traits<ForwardRange>::position_type lower_bound(const ForwardRange& range, const T& value, Compare comp)
	{
		return std::lower_bound(range_iterator<ForwardRange>(range, range.begin_pos()),
								range_iterator<ForwardRange>(range, range.end_pos()),
								value, comp).pos();
	}

	template<class ForwardRange, class T>
	typename range_traits<ForwardRange>::position_type upper_bound(const ForwardRange& range, const T& value)
	{
		return std::upper_bound(range_iterator<ForwardRange>(range, range.begin_pos()),
								range_iterator<ForwardRange>(range, range.end_pos()),
								value).pos();
	}

	template<class ForwardRange, class T, class Compare>
	typename range_traits<ForwardRange>::position_type upper_bound(const ForwardRange& range, const T& value, Compare comp)
	{
		return std::upper_bound(range_iterator<ForwardRange>(range, range.begin_pos()),
								range_iterator<ForwardRange>(range, range.end_pos()),
								value, comp).pos();
	}

	template<class ForwardRange, class T>
	ForwardRange equal_range(ForwardRange range, const T& value)
	{
		auto positions = std::equal_range(range_iterator<ForwardRange>(range, range.begin_pos()),
										  range_iterator<ForwardRange>(range, range.end_pos()),
										  value);
		range.begin_pos(positions.first.pos());
		range.end_pos(positions.second.pos());
		return range;
	}

	template<class ForwardRange, class T, class Compare>
	ForwardRange equal_range(ForwardRange range, const T& value, Compare comp)
	{
		auto positions = std::equal_range(range_iterator<ForwardRange>(range, range.begin_pos()),
										  range_iterator<ForwardRange>(range, range.end_pos()),
										  value, comp);
		range.begin_pos(positions.first.pos());
		range.end_pos(positions.second.pos());
		return range;
	}

	template<class ForwardRange, class T>
	bool binary_search(const ForwardRange& range, const T& value)
	{
		return std::binary_search(range_iterator<ForwardRange>(range, range.begin_pos()),
								  range_iterator<ForwardRange>(range, range.end_pos()),
								  value);
	}

	template<class ForwardRange, class T, class Compare>
	bool binary_search(const ForwardRange& range, const T& value, Compare comp)
	{
		return std::binary_search(range_iterator<ForwardRange>(range, range.begin_pos()),
								  range_iterator<ForwardRange>(range, range.end_pos()),
								  value, comp);
	}

	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator merge(const InputRange1& range1, const InputRange2& range2, OutputIterator result)
	{
		return std::merge(range_iterator<InputRange1>(range1, range1.begin_pos()),
						  range_iterator<InputRange1>(range1, range1.end_pos()),
						  range_iterator<InputRange2>(range2, range2.begin_pos()),
						  range_iterator<InputRange2>(range2, range2.end_pos()),
						  result);
	}

	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator merge(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp)
	{
		return std::merge(range_iterator<InputRange1>(range1, range1.begin_pos()),
						  range_iterator<InputRange1>(range1, range1.end_pos()),
						  range_iterator<InputRange2>(range2, range2.begin_pos()),
						  range_iterator<InputRange2>(range2, range2.end_pos()),
						  result);
	}

	template<class BidirectionalRange>
	void inplace_merge(const BidirectionalRange& range, typename range_traits<BidirectionalRange>::position_type middle)
	{
		std::inplace_merge(range_iterator<BidirectionalRange>(range, range.begin_pos()),
						   range_iterator<BidirectionalRange>(range, middle),
						   range_iterator<BidirectionalRange>(range, range.end_pos()));
	}

	template<class BidirectionalRange, class Compare>
	void inplace_merge(const BidirectionalRange& range, typename range_traits<BidirectionalRange>::position_type middle, Compare comp)
	{
		std::inplace_merge(range_iterator<BidirectionalRange>(range, range.begin_pos()),
						   range_iterator<BidirectionalRange>(range, middle),
						   range_iterator<BidirectionalRange>(range, range.end_pos()),
						   comp);
	}

	template<class InputRange1, class InputRange2>
	bool includes(const InputRange1& range1, const InputRange2& range2)
	{
		return std::includes(range_iterator<InputRange1>(range1, range1.begin_pos()),
							 range_iterator<InputRange1>(range1, range1.end_pos()),
							 range_iterator<InputRange2>(range2, range2.begin_pos()),
							 range_iterator<InputRange2>(range2, range2.end_pos()));
	}

	template<class InputRange1, class InputRange2, class Compare>
	bool includes(const InputRange1& range1, const InputRange2& range2, Compare comp)
	{
		return std::includes(range_iterator<InputRange1>(range1, range1.begin_pos()),
							 range_iterator<InputRange1>(range1, range1.end_pos()),
							 range_iterator<InputRange2>(range2, range2.begin_pos()),
							 range_iterator<InputRange2>(range2, range2.end_pos()),
							 comp);
	}

	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator set_union(const InputRange1& range1, const InputRange2& range2, OutputIterator result)
	{
		return std::set_union(range_iterator<InputRange1>(range1, range1.begin_pos()),
							  range_iterator<InputRange1>(range1, range1.end_pos()),
							  range_iterator<InputRange2>(range2, range2.begin_pos()),
							  range_iterator<InputRange2>(range2, range2.end_pos()),
							  result);
	}

	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_union(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp)
	{
		return std::set_union(range_iterator<InputRange1>(range1, range1.begin_pos()),
							  range_iterator<InputRange1>(range1, range1.end_pos()),
							  range_iterator<InputRange2>(range2, range2.begin_pos()),
							  range_iterator<InputRange2>(range2, range2.end_pos()),
							  result, comp);
	}

	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator set_intersection(const InputRange1& range1, const InputRange2& range2, OutputIterator result)
	{
		return std::set_intersection(range_iterator<InputRange1>(range1, range1.begin_pos()),
									 range_iterator<InputRange1>(range1, range1.end_pos()),
									 range_iterator<InputRange2>(range2, range2.begin_pos()),
									 range_iterator<InputRange2>(range2, range2.end_pos()),
									 result);
	}

	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_intersection(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp)
	{
		return std::set_intersection(range_iterator<InputRange1>(range1, range1.begin_pos()),
									 range_iterator<InputRange1>(range1, range1.end_pos()),
									 range_iterator<InputRange2>(range2, range2.begin_pos()),
									 range_iterator<InputRange2>(range2, range2.end_pos()),
									 result, comp);
	}

	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator set_difference(const InputRange1& range1, const InputRange2& range2, OutputIterator result)
	{
		return std::set_difference(range_iterator<InputRange1>(range1, range1.begin_pos()),
								   range_iterator<InputRange1>(range1, range1.end_pos()),
								   range_iterator<InputRange2>(range2, range2.begin_pos()),
								   range_iterator<InputRange2>(range2, range2.end_pos()),
								   result);
	}

	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_difference(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp)
	{
		return std::set_difference(range_iterator<InputRange1>(range1, range1.begin_pos()),
								   range_iterator<InputRange1>(range1, range1.end_pos()),
								   range_iterator<InputRange2>(range2, range2.begin_pos()),
								   range_iterator<InputRange2>(range2, range2.end_pos()),
								   result, comp);
	}

	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator set_symmetric_difference(const InputRange1& range1, const InputRange2& range2, OutputIterator result)
	{
		return std::set_symmetric_difference(range_iterator<InputRange1>(range1, range1.begin_pos()),
											 range_iterator<InputRange1>(range1, range1.end_pos()),
											 range_iterator<InputRange2>(range2, range2.begin_pos()),
											 range_iterator<InputRange2>(range2, range2.end_pos()),
											 result);
	}

	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_symmetric_difference(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp)
	{
		return std::set_symmetric_difference(range_iterator<InputRange1>(range1, range1.begin_pos()),
											 range_iterator<InputRange1>(range1, range1.end_pos()),
											 range_iterator<InputRange2>(range2, range2.begin_pos()),
											 range_iterator<InputRange2>(range2, range2.end_pos()),
											 result, comp);
	}

	template<class RandomAccessRange>
	void push_heap(const RandomAccessRange& range)
	{
		std::push_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
					   range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class Compare>
	void push_heap(const RandomAccessRange& range, Compare comp)
	{
		std::push_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
					   range_iterator<RandomAccessRange>(range, range.end_pos()),
					   comp);
	}

	template<class RandomAccessRange>
	void pop_heap(const RandomAccessRange& range)
	{
		std::pop_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
					  range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class Compare>
	void pop_heap(const RandomAccessRange& range, Compare comp)
	{
		std::pop_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
					  range_iterator<RandomAccessRange>(range, range.end_pos()),
					  comp);
	}

	template<class RandomAccessRange>
	void make_heap(const RandomAccessRange& range)
	{
		std::make_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
					   range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class Compare>
	void make_heap(const RandomAccessRange& range, Compare comp)
	{
		std::make_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
					   range_iterator<RandomAccessRange>(range, range.end_pos()),
					   comp);
	}

	template<class RandomAccessRange>
	void sort_heap(const RandomAccessRange& range)
	{
		std::sort_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
					   range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class Compare>
	void sort_heap(const RandomAccessRange& range, Compare comp)
	{
		std::sort_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
					   range_iterator<RandomAccessRange>(range, range.end_pos()),
					   comp);
	}

	template<class RandomAccessRange>
	bool is_heap(const RandomAccessRange& range)
	{
		return std::is_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
							range_iterator<RandomAccessRange>(range, range.end_pos()));
	}

	template<class RandomAccessRange, class Compare>
	bool is_heap(const RandomAccessRange& range, Compare comp)
	{
		return std::is_heap(range_iterator<RandomAccessRange>(range, range.begin_pos()),
							range_iterator<RandomAccessRange>(range, range.end_pos()),
							comp);
	}

	template<class RandomAccessRange>
	typename range_traits<RandomAccessRange>::position_type is_heap_until(const RandomAccessRange& range)
	{
		return std::is_heap_until(range_iterator<RandomAccessRange>(range, range.begin_pos()),
								  range_iterator<RandomAccessRange>(range, range.end_pos())).pos();
	}

	template<class RandomAccessRange, class Compare>
	typename range_traits<RandomAccessRange>::position_type is_heap_until(const RandomAccessRange& range, Compare comp)
	{
		return std::is_heap_until(range_iterator<RandomAccessRange>(range, range.begin_pos()),
								  range_iterator<RandomAccessRange>(range, range.end_pos()),
								  comp).pos();
	}

	template<class ForwardRange>
	typename range_traits<ForwardRange>::position_type min_element(const ForwardRange& range)
	{
		return std::min_element(range_iterator<ForwardRange>(range, range.begin_pos()),
								range_iterator<ForwardRange>(range, range.end_pos())).pos();
	}

	template<class ForwardRange, class Compare>
	typename range_traits<ForwardRange>::position_type min_element(const ForwardRange& range, Compare comp)
	{
		return std::min_element(range_iterator<ForwardRange>(range, range.begin_pos()),
								range_iterator<ForwardRange>(range, range.end_pos()),
								comp).pos();
	}

	template<class ForwardRange>
	typename range_traits<ForwardRange>::position_type max_element(const ForwardRange& range)
	{
		return std::max_element(range_iterator<ForwardRange>(range, range.begin_pos()),
								range_iterator<ForwardRange>(range, range.end_pos())).pos();
	}

	template<class ForwardRange, class Compare>
	typename range_traits<ForwardRange>::position_type max_element(const ForwardRange& range, Compare comp)
	{
		return std::max_element(range_iterator<ForwardRange>(range, range.begin_pos()),
								range_iterator<ForwardRange>(range, range.end_pos()),
								comp).pos();
	}

	template<class ForwardRange>
	std::pair<typename range_traits<ForwardRange>::position_type, typename range_traits<ForwardRange>::position_type>
		minmax_element(const ForwardRange& range)
	{
		auto positions = std::minmax_element(range_iterator<ForwardRange>(range, range.begin_pos()),
											 range_iterator<ForwardRange>(range, range.end_pos()));
		return std::make_pair(positions.first.pos(), positions.second.pos());
	}

	template<class ForwardRange, class Compare>
	std::pair<typename range_traits<ForwardRange>::position_type, typename range_traits<ForwardRange>::position_type>
		minmax_element(const ForwardRange& range, Compare comp)
	{
		auto positions = std::minmax_element(range_iterator<ForwardRange>(range, range.begin_pos()),
												range_iterator<ForwardRange>(range, range.end_pos()),
												comp);
		return std::make_pair(positions.first.pos(), positions.second.pos());
	}

	template<class InputRange1, class InputRange2>
	bool lexicographical_compare(const InputRange1& range1, const InputRange2& range2)
	{
		return std::lexicographical_compare(range_iterator<InputRange1>(range1, range1.begin_pos()),
											range_iterator<InputRange1>(range1, range1.end_pos()),
											range_iterator<InputRange2>(range2, range2.begin_pos()),
											range_iterator<InputRange2>(range2, range2.end_pos()));
	}

	template<class InputRange1, class InputRange2, class Compare>
	bool lexicographical_compare(const InputRange1& range1, const InputRange2& range2, Compare comp)
	{
		return std::lexicographical_compare(range_iterator<InputRange1>(range1, range1.begin_pos()),
											range_iterator<InputRange1>(range1, range1.end_pos()),
											range_iterator<InputRange2>(range2, range2.begin_pos()),
											range_iterator<InputRange2>(range2, range2.end_pos()),
											comp);
	}

	template<class BidirectionalRange>
	bool next_permutation(const BidirectionalRange& range)
	{
		return std::next_permutation(range_iterator<BidirectionalRange>(range, range.begin_pos()),
									 range_iterator<BidirectionalRange>(range, range.end_pos()));
	}

	template<class BidirectionalRange, class Compare>
	bool next_permutation(const BidirectionalRange& range, Compare comp)
	{
		return std::next_permutation(range_iterator<BidirectionalRange>(range, range.begin_pos()),
									 range_iterator<BidirectionalRange>(range, range.end_pos()),
									 comp);
	}

	template<class BidirectionalRange>
	bool prev_permutation(const BidirectionalRange& range)
	{
		return std::prev_permutation(range_iterator<BidirectionalRange>(range, range.begin_pos()),
									 range_iterator<BidirectionalRange>(range, range.end_pos()));
	}

	template<class BidirectionalRange, class Compare>
	bool prev_permutation(const BidirectionalRange& range, Compare comp)
	{
		return std::prev_permutation(range_iterator<BidirectionalRange>(range, range.begin_pos()),
									 range_iterator<BidirectionalRange>(range, range.end_pos()),
									 comp);
	}
}