#ifndef STDEXT_ALGORITHM_INCLUDED
#define STDEXT_ALGORITHM_INCLUDED
#pragma once

#include <range.h>
#include <initializer_list>
#include <cstddef>	// for std::size_t


namespace stdext
{
	// 25.2, non-modifying sequence operations:
	template <class InputRange, class Predicate>
	bool all_of(const InputRange& range, Predicate pred);
	template <class InputRange, class Predicate>
	bool any_of(const InputRange& range, Predicate pred);
	template <class InputRange, class Predicate>
	bool none_of(const InputRange& range, Predicate pred);

	template<class InputRange, class Function>
	Function for_each(const InputRange& range, Function f);
	template<class InputRange, class T>
	typename range::range_traits<InputRange>::position_type find(const InputRange& range, const T& value);
	template<class InputRange, class Predicate>
	typename range::range_traits<InputRange>::position_type find_if(const InputRange& range, Predicate pred);
	template<class InputRange, class Predicate>
	typename range::range_traits<InputRange>::position_type find_if_not(const InputRange& range, Predicate pred);
	template<class ForwardRange1, class ForwardRange2>
	typename range::range_traits<ForwardRange1>::position_type find_end(const ForwardRange1& range1, const ForwardRange2& range2);
	template<class ForwardRange1, class ForwardRange2, class BinaryPredicate>
	typename range::range_traits<ForwardRange1>::position_type find_end(const ForwardRange1& range1, const ForwardRange2& range2, BinaryPredicate pred);

	template<class InputRange, class ForwardRange>
	typename range::range_traits<InputRange>::position_type find_first_of(const InputRange& range1, const ForwardRange& range2);
	template<class InputRange, class ForwardRange, class BinaryPredicate>
	typename range::range_traits<InputRange>::position_type find_first_of(const InputRange& range1, const ForwardRange& range2, BinaryPredicate pred);

	template<class ForwardRange>
	typename range::range_traits<ForwardRange>::position_type adjacent_find(const ForwardRange& range);
	template<class ForwardRange, class BinaryPredicate>
	typename range::range_traits<ForwardRange>::position_type adjacent_find(const ForwardRange& range, BinaryPredicate pred);

	template<class InputRange, class T>
	std::size_t count(const InputRange& range, const T& value);
	template<class InputRange, class Predicate>
	std::size_t count_if(const InputRange& range, Predicate pred);

	template<class InputRange, class InputIterator>
	typename std::enable_if<!range::is_range<InputIterator>::value, std::pair<typename range::range_traits<InputRange>::position_type, InputIterator>>::type
		mismatch(const InputRange& range1, InputIterator first2);
	template <class InputRange, class InputIterator, class BinaryPredicate>
	typename std::enable_if<!range::is_range<InputIterator>::value, std::pair<typename range::range_traits<InputRange>::position_type, InputIterator>>::type
		mismatch(const InputRange& range1, InputIterator first2, BinaryPredicate pred);
	template<class InputRange1, class InputRange2>
	typename std::enable_if<range::is_range<InputRange2>::value, std::pair<typename range::range_traits<InputRange1>::position_type, typename range::range_traits<InputRange2>::position_type>>::type
		mismatch(const InputRange1& range1, const InputRange2& range2);
	template<class InputRange1, class InputRange2, class BinaryPredicate>
	typename std::enable_if<range::is_range<InputRange2>::value, std::pair<typename range::range_traits<InputRange1>::position_type, typename range::range_traits<InputRange2>::position_type>>::type
		mismatch(const InputRange1& range1, const InputRange2& range2, BinaryPredicate pred);

	template<class InputRange1, class InputIterator2>
	typename std::enable_if<!range::is_range<InputIterator2>::value, bool>::type
		equal(const InputRange1& range1, InputIterator2 first2);
	template <class InputRange1, class InputIterator2, class BinaryPredicate>
	typename std::enable_if<!range::is_range<InputIterator2>::value, bool>::type
		equal(const InputRange1& range1, InputIterator2 first2, BinaryPredicate pred);
	template<class InputRange1, class InputRange2>
	typename std::enable_if<range::is_range<InputRange2>::value, bool>::type
		equal(const InputRange1& range1, const InputRange2& range2);
	template<class InputRange1, class InputRange2, class BinaryPredicate>
	typename std::enable_if<range::is_range<InputRange2>::value, bool>::type
		equal(const InputRange1& range1, const InputRange2& range2, BinaryPredicate pred);

	template<class ForwardRange1, class ForwardIterator2>
	typename std::enable_if<!range::is_range<ForwardIterator2>::value, bool>::type
		is_permutation(const ForwardRange1& range1, ForwardIterator2 first2);
	template<class ForwardRange1, class ForwardIterator2, class BinaryPredicate>
	typename std::enable_if<!range::is_range<ForwardIterator2>::value, bool>::type
		is_permutation(const ForwardRange1& range1, ForwardIterator2 first2, BinaryPredicate pred);
	template<class ForwardRange1, class ForwardRange2>
	typename std::enable_if<range::is_range<ForwardRange2>::value, bool>::type
		is_permutation(const ForwardRange1& range1, const ForwardRange2& range2);
	template<class ForwardRange1, class ForwardRange2, class BinaryPredicate>
	typename std::enable_if<range::is_range<ForwardRange2>::value, bool>::type
		is_permutation(const ForwardRange1& range1, const ForwardRange2& range2, BinaryPredicate pred);

	template<class ForwardRange1, class ForwardRange2>
	typename range::range_traits<ForwardRange1>::position_type search(const ForwardRange1& range1, const ForwardRange2& range2);
	template<class ForwardRange1, class ForwardRange2, class BinaryPredicate>
	typename range::range_traits<ForwardRange1>::position_type search(const ForwardRange1& range1, const ForwardRange2& range2, BinaryPredicate pred);
	template<class ForwardRange, class Size, class T>
	typename range::range_traits<ForwardRange>::position_type search_n(const ForwardRange& range, Size count, const T& value);
	template <class ForwardRange, class Size, class T, class BinaryPredicate>
	typename range::range_traits<ForwardRange>::position_type search_n(const ForwardRange& range, Size count, const T& value, BinaryPredicate pred);

	// 25.3, modifying sequence operations:
	// 25.3.1, copy:
	template<class InputRange, class OutputIterator>
	OutputIterator copy(const InputRange& range, OutputIterator result);
	template<class InputRange, class Size, class OutputIterator>
	OutputIterator copy_n(const InputRange& range, Size n, OutputIterator result);
	template<class InputRange, class OutputIterator, class Predicate>
	OutputIterator copy_if(const InputRange& range, OutputIterator result, Predicate pred);
	template<class BidirectionalRange1, class BidirectionalIterator2>
	BidirectionalIterator2 copy_backward(const BidirectionalRange1& range, BidirectionalIterator2 result);

	// 25.3.2, move:
	template<class InputRange, class OutputIterator>
	OutputIterator move(const InputRange& range, OutputIterator result);
	template<class BidirectionalRange1, class BidirectionalIterator2>
	BidirectionalIterator2 move_backward(const BidirectionalRange1& range, BidirectionalIterator2 result);

	// 25.3.3, swap:
	template<class ForwardRange1, class ForwardIterator2>
	ForwardIterator2 swap_ranges(const ForwardRange1& range1, ForwardIterator2 first2);

	template<class InputRange, class OutputIterator, class UnaryOperation>
	OutputIterator transform(const InputRange& range, OutputIterator result, UnaryOperation op);
	template<class InputRange1, class InputIterator2, class OutputIterator, class BinaryOperation>
	OutputIterator transform(const InputRange1& range1, InputIterator2 first2, OutputIterator result, BinaryOperation binary_op);

	template<class ForwardRange, class T>
	void replace(const ForwardRange& range, const T& old_value, const T& new_value);
	template<class ForwardRange, class Predicate, class T>
	void replace_if(const ForwardRange& range, Predicate pred, const T& new_value);
	template<class InputRange, class OutputIterator, class T>
	OutputIterator replace_copy(const InputRange& range, OutputIterator result, const T& old_value, const T& new_value);
	template<class InputRange, class OutputIterator, class Predicate, class T>
	OutputIterator replace_copy_if(const InputRange& range, OutputIterator result, Predicate pred, const T& new_value);

	template<class ForwardRange, class T>
	void fill(const ForwardRange& range, const T& value);
	template<class OutputRange, class Size, class T>
	typename range::range_traits<OutputRange>::position_type fill_n(OutputRange first, Size n, const T& value);

	template<class ForwardRange, class Generator>
	void generate(const ForwardRange& range, Generator gen);
	template<class OutputRange, class Size, class Generator>
	typename range::range_traits<OutputRange>::position_type generate_n(OutputRange range, Size n, Generator gen);

	template<class ForwardRange, class T>
	typename range::range_traits<ForwardRange>::position_type remove(const ForwardRange& range, const T& value);
	template<class ForwardRange, class Predicate>
	typename range::range_traits<ForwardRange>::position_type remove_if(const ForwardRange& range, Predicate pred);
	template<class InputRange, class OutputIterator, class T>
	OutputIterator remove_copy(const InputRange& range, OutputIterator result, const T& value);
	template<class InputRange, class OutputIterator, class Predicate>
	OutputIterator remove_copy_if(const InputRange& range, OutputIterator result, Predicate pred);

	template<class ForwardRange>
	typename range::range_traits<ForwardRange>::position_type unique(const ForwardRange& range);
	template<class ForwardRange, class BinaryPredicate>
	typename range::range_traits<ForwardRange>::position_type unique(const ForwardRange& range, BinaryPredicate pred);
	template<class InputRange, class OutputIterator>
	OutputIterator unique_copy(const InputRange& range, OutputIterator result);
	template<class InputRange, class OutputIterator, class BinaryPredicate>
	OutputIterator unique_copy(const InputRange& range, OutputIterator result, BinaryPredicate pred);

	template<class BidirectionalRange>
	void reverse(const BidirectionalRange& range);
	template<class BidirectionalRange, class OutputIterator>
	OutputIterator reverse_copy(const BidirectionalRange& range, OutputIterator result);

	template<class ForwardRange>
	typename range::range_traits<ForwardRange>::position_type rotate(const ForwardRange& range, typename range::range_traits<ForwardRange>::position_type middle);
	template<class ForwardRange, class OutputIterator>
	OutputIterator rotate_copy(const ForwardRange& range, typename range::range_traits<ForwardRange>::position_type middle, OutputIterator result);

	template<class RandomAccessRange>
	void random_shuffle(const RandomAccessRange& range);
	template<class RandomAccessRange, class RandomNumberGenerator>
	void random_shuffle(const RandomAccessRange& range, RandomNumberGenerator&& rand);
	template<class RandomAccessRange, class UniformRandomNumberGenerator>
	void shuffle(const RandomAccessRange& range, UniformRandomNumberGenerator&& rand);

	// 25.3.13, partitions:
	template <class InputRange, class Predicate>
	bool is_partitioned(const InputRange& range, Predicate pred);
	template<class ForwardRange, class Predicate>
	typename range::range_traits<ForwardRange>::position_type partition(const ForwardRange& range, Predicate pred);
	template<class BidirectionalRange, class Predicate>
	typename range::range_traits<BidirectionalRange>::position_type stable_partition(const BidirectionalRange& range, Predicate pred);
	template <class InputRange, class OutputIterator1, class OutputIterator2, class Predicate>
	std::pair<OutputIterator1, OutputIterator2> partition_copy(const InputRange& range, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred);
	template<class ForwardRange, class Predicate>
	typename range::range_traits<ForwardRange>::position_type partition_point(const ForwardRange& range, Predicate pred);

	// 25.4, sorting and related operations:
	// 25.4.1, sorting:
	template<class RandomAccessRange>
	void sort(const RandomAccessRange& range);
	template<class RandomAccessRange, class Compare>
	void sort(const RandomAccessRange& range, Compare comp);

	template<class RandomAccessRange>
	void stable_sort(const RandomAccessRange& range);
	template<class RandomAccessRange, class Compare>
	void stable_sort(const RandomAccessRange& range, Compare comp);

	template<class RandomAccessRange>
	void partial_sort(const RandomAccessRange& range, typename range::range_traits<RandomAccessRange>::position_type middle);
	template<class RandomAccessRange, class Compare>
	void partial_sort(const RandomAccessRange& range, typename range::range_traits<RandomAccessRange>::position_type middle, Compare comp);
	template<class InputRange, class RandomAccessRange>
	typename range::range_traits<RandomAccessRange>::position_type partial_sort_copy(const InputRange& range, const RandomAccessRange& result_range);
	template<class InputRange, class RandomAccessRange, class Compare>
	typename range::range_traits<RandomAccessRange>::position_type partial_sort_copy(const InputRange& range, const RandomAccessRange& result_range, Compare comp);
	template<class ForwardRange>
	bool is_sorted(const ForwardRange& range);
	template<class ForwardRange, class Compare>
	bool is_sorted(const ForwardRange& range, Compare comp);
	template<class ForwardRange>
	typename range::range_traits<ForwardRange>::position_type is_sorted_until(const ForwardRange& range);
	template<class ForwardRange, class Compare>
	typename range::range_traits<ForwardRange>::position_type is_sorted_until(const ForwardRange& range, Compare comp);

	template<class RandomAccessRange>
	void nth_element(const RandomAccessRange& range, typename range::range_traits<RandomAccessRange>::position_type nth);
	template<class RandomAccessRange, class Compare>
	void nth_element(const RandomAccessRange& range, typename range::range_traits<RandomAccessRange>::position_type nth, Compare comp);

	// 25.4.3, binary search:
	template<class ForwardRange, class T>
	typename range::range_traits<ForwardRange>::position_type lower_bound(const ForwardRange& range, const T& value);
	template<class ForwardRange, class T, class Compare>
	typename range::range_traits<ForwardRange>::position_type lower_bound(const ForwardRange& range, const T& value, Compare comp);
	template<class ForwardRange, class T>
	typename range::range_traits<ForwardRange>::position_type upper_bound(const ForwardRange& range, const T& value);
	template<class ForwardRange, class T, class Compare>
	typename range::range_traits<ForwardRange>::position_type upper_bound(const ForwardRange& range, const T& value, Compare comp);

	template<class ForwardRange, class T>
	ForwardRange equal_range(ForwardRange range, const T& value);
	template<class ForwardRange, class T, class Compare>
	ForwardRange equal_range(ForwardRange range, const T& value, Compare comp);

	template<class ForwardRange, class T>
	bool binary_search(const ForwardRange& range, const T& value);
	template<class ForwardRange, class T, class Compare>
	bool binary_search(const ForwardRange& range, const T& value, Compare comp);

	// 25.4.4, merge:
	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator merge(const InputRange1& range1, const InputRange2& range2, OutputIterator result);
	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator merge(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp);

	template<class BidirectionalRange>
	void inplace_merge(const BidirectionalRange& range, typename range::range_traits<BidirectionalRange>::position_type middle);
	template<class BidirectionalRange, class Compare>
	void inplace_merge(const BidirectionalRange& range, typename range::range_traits<BidirectionalRange>::position_type middle, Compare comp);

	// 25.4.5, set operations:
	template<class InputRange1, class InputRange2>
	bool includes(const InputRange1& range1, const InputRange2& range2);
	template<class InputRange1, class InputRange2, class Compare>
	bool includes(const InputRange1& range1, const InputRange2& range2, Compare comp);

	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator set_union(const InputRange1& range1, const InputRange2& range2, OutputIterator result);
	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_union(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp);

	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator set_intersection(const InputRange1& range1, const InputRange2& range2, OutputIterator result);
	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_intersection(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp);

	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator set_difference(const InputRange1& range1, const InputRange2& range2, OutputIterator result);
	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_difference(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp);

	template<class InputRange1, class InputRange2, class OutputIterator>
	OutputIterator set_symmetric_difference(const InputRange1& range1, const InputRange2& range2, OutputIterator result);
	template<class InputRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_symmetric_difference(const InputRange1& range1, const InputRange2& range2, OutputIterator result, Compare comp);

	// 25.4.6, heap operations:
	template<class RandomAccessRange>
	void push_heap(const RandomAccessRange& range);
	template<class RandomAccessRange, class Compare>
	void push_heap(const RandomAccessRange& range, Compare comp);

	template<class RandomAccessRange>
	void pop_heap(const RandomAccessRange& range);
	template<class RandomAccessRange, class Compare>
	void pop_heap(const RandomAccessRange& range, Compare comp);

	template<class RandomAccessRange>
	void make_heap(const RandomAccessRange& range);
	template<class RandomAccessRange, class Compare>
	void make_heap(const RandomAccessRange& range, Compare comp);

	template<class RandomAccessRange>
	void sort_heap(const RandomAccessRange& range);
	template<class RandomAccessRange, class Compare>
	void sort_heap(const RandomAccessRange& range, Compare comp);

	template<class RandomAccessRange>
	bool is_heap(const RandomAccessRange& range);
	template<class RandomAccessRange, class Compare>
	bool is_heap(const RandomAccessRange& range, Compare comp);
	template<class RandomAccessRange>
	typename range::range_traits<RandomAccessRange>::position_type is_heap_until(const RandomAccessRange& range);
	template<class RandomAccessRange, class Compare>
	typename range::range_traits<RandomAccessRange>::position_type is_heap_until(const RandomAccessRange& range, Compare comp);

	// 25.4.7, minimum and maximum:
	template<class ForwardRange>
	typename range::range_traits<ForwardRange>::position_type min_element(const ForwardRange& range);
	template<class ForwardRange, class Compare>
	typename range::range_traits<ForwardRange>::position_type min_element(const ForwardRange& range, Compare comp);
	template<class ForwardRange>
	typename range::range_traits<ForwardRange>::position_type max_element(const ForwardRange& range);
	template<class ForwardRange, class Compare>
	typename range::range_traits<ForwardRange>::position_type max_element(const ForwardRange& range, Compare comp);
	template<class ForwardRange>
	std::pair<typename range::range_traits<ForwardRange>::position_type, typename range::range_traits<ForwardRange>::position_type>
		minmax_element(const ForwardRange& range);
	template<class ForwardRange, class Compare>
	std::pair<typename range::range_traits<ForwardRange>::position_type, typename range::range_traits<ForwardRange>::position_type>
		minmax_element(const ForwardRange& range, Compare comp);

	template<class InputRange1, class InputRange2>
	bool lexicographical_compare(const InputRange1& range1, const InputRange2& range2);
	template<class InputRange1, class InputRange2, class Compare>
	bool lexicographical_compare(const InputRange1& range1, const InputRange2& range2, Compare comp);

	// 25.4.9, permutations:
	template<class BidirectionalRange>
	bool next_permutation(const BidirectionalRange& range);
	template<class BidirectionalRange, class Compare>
	bool next_permutation(const BidirectionalRange& range, Compare comp);
	template<class BidirectionalRange>
	bool prev_permutation(const BidirectionalRange& range);
	template<class BidirectionalRange, class Compare>
	bool prev_permutation(const BidirectionalRange& range, Compare comp);
}

#include "algorithm.inl"

#endif