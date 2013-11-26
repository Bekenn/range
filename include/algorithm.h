#ifndef STDEXT_ALGORITHM_INCLUDED
#define STDEXT_ALGORITHM_INCLUDED
#pragma once

#include <range.h>
#include <initializer_list>


namespace stdext
{
	// 25.2, non-modifying sequence operations:
	template <class SinglePassRange, class Predicate>
	bool all_of(SinglePassRange range, Predicate pred);
	template <class SinglePassRange, class Predicate>
	bool any_of(SinglePassRange range, Predicate pred);
	template <class SinglePassRange, class Predicate>
	bool none_of(SinglePassRange range, Predicate pred);

	template<class SinglePassRange, class Function>
	Function for_each(SinglePassRange range, Function f);
	template<class SinglePassRange, class T>
	typename range_traits<SinglePassRange>::position_type find(SinglePassRange range, const T& value);
	template<class SinglePassRange, class Predicate>
	typename range_traits<SinglePassRange>::position_type find_if(SinglePassRange range, Predicate pred);
	template<class SinglePassRange, class Predicate>
	typename range_traits<SinglePassRange>::position_type find_if_not(SinglePassRange range, Predicate pred);
	template<class MultiPassRange1, class MultiPassRange2>
	typename range_traits<MultiPassRange1>::position_type find_end(MultiPassRange1 range1, MultiPassRange2 range2);
	template<class MultiPassRange1, class MultiPassRange2, class BinaryPredicate>
	typename range_traits<MultiPassRange1>::position_type find_end(MultiPassRange1 range1, MultiPassRange2 range2, BinaryPredicate pred);

	template<class SinglePassRange, class MultiPassRange>
	typename range_traits<SinglePassRange>::position_type find_first_of(SinglePassRange range1, MultiPassRange range2);
	template<class SinglePassRange, class MultiPassRange, class BinaryPredicate>
	typename range_traits<SinglePassRange>::position_type find_first_of(SinglePassRange range1, MultiPassRange range2, BinaryPredicate pred);

	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::position_type adjacent_find(MultiPassRange range);
	template<class MultiPassRange, class BinaryPredicate>
	typename range_traits<MultiPassRange>::position_type adjacent_find(MultiPassRange range, BinaryPredicate pred);

	template<class SinglePassRange, class T>
	typename range_traits<SinglePassRange>::size_type count(SinglePassRange range, const T& value);
	template<class SinglePassRange, class Predicate>
	typename range_traits<SinglePassRange>::size_type count_if(SinglePassRange range, Predicate pred);

	template<class SinglePassRange, class InputIterator>
	typename std::enable_if<!is_range<InputIterator>::value, std::pair<typename range_traits<SinglePassRange>::position_type, InputIterator>>::type
		mismatch(SinglePassRange range1, InputIterator first2);
	template <class SinglePassRange, class InputIterator, class BinaryPredicate>
	typename std::enable_if<!is_range<InputIterator>::value, std::pair<typename range_traits<SinglePassRange>::position_type, InputIterator>>::type
		mismatch(SinglePassRange range1, InputIterator first2, BinaryPredicate pred);
	template<class SinglePassRange1, class SinglePassRange2>
	typename std::enable_if<is_range<SinglePassRange2>::value, std::pair<typename range_traits<SinglePassRange1>::position_type, typename range_traits<SinglePassRange2>::position_type>>::type
		mismatch(SinglePassRange1 range1, SinglePassRange2 range2);
	template<class SinglePassRange1, class SinglePassRange2, class BinaryPredicate>
	typename std::enable_if<is_range<SinglePassRange2>::value, std::pair<typename range_traits<SinglePassRange1>::position_type, typename range_traits<SinglePassRange2>::position_type>>::type
		mismatch(SinglePassRange1 range1, SinglePassRange2 range2, BinaryPredicate pred);

	template<class SinglePassRange1, class InputIterator2>
	typename std::enable_if<!is_range<InputIterator2>::value, bool>::type
		equal(SinglePassRange1 range1, InputIterator2 first2);
	template <class SinglePassRange1, class InputIterator2, class BinaryPredicate>
	typename std::enable_if<!is_range<InputIterator2>::value, bool>::type
		equal(SinglePassRange1 range1, InputIterator2 first2, BinaryPredicate pred);
	template<class SinglePassRange1, class SinglePassRange2>
	typename std::enable_if<is_range<SinglePassRange2>::value, bool>::type
		equal(SinglePassRange1 range1, SinglePassRange2 range2);
	template<class SinglePassRange1, class SinglePassRange2, class BinaryPredicate>
	typename std::enable_if<is_range<SinglePassRange2>::value, bool>::type
		equal(SinglePassRange1 range1, SinglePassRange2 range2, BinaryPredicate pred);

	template<class MultiPassRange1, class ForwardIterator2>
	typename std::enable_if<!is_range<ForwardIterator2>::value, bool>::type
		is_permutation(MultiPassRange1 range1, ForwardIterator2 first2);
	template<class MultiPassRange1, class ForwardIterator2, class BinaryPredicate>
	typename std::enable_if<!is_range<ForwardIterator2>::value, bool>::type
		is_permutation(MultiPassRange1 range1, ForwardIterator2 first2, BinaryPredicate pred);
	template<class MultiPassRange1, class MultiPassRange2>
	typename std::enable_if<is_range<MultiPassRange2>::value, bool>::type
		is_permutation(MultiPassRange1 range1, MultiPassRange2 range2);
	template<class MultiPassRange1, class MultiPassRange2, class BinaryPredicate>
	typename std::enable_if<is_range<MultiPassRange2>::value, bool>::type
		is_permutation(MultiPassRange1 range1, MultiPassRange2 range2, BinaryPredicate pred);

	template<class MultiPassRange1, class MultiPassRange2>
	typename range_traits<MultiPassRange1>::position_type search(MultiPassRange1 range1, MultiPassRange2 range2);
	template<class MultiPassRange1, class MultiPassRange2, class BinaryPredicate>
	typename range_traits<MultiPassRange1>::position_type search(MultiPassRange1 range1, MultiPassRange2 range2, BinaryPredicate pred);
	template<class MultiPassRange, class Size, class T>
	typename range_traits<MultiPassRange>::position_type search_n(MultiPassRange range, Size count, const T& value);
	template <class MultiPassRange, class Size, class T, class BinaryPredicate>
	typename range_traits<MultiPassRange>::position_type search_n(MultiPassRange range, Size count, const T& value, BinaryPredicate pred);

	// 25.3, modifying sequence operations:
	// 25.3.1, copy:
	template<class SinglePassRange, class OutputIterator>
	OutputIterator copy(SinglePassRange range, OutputIterator result);
	template<class SinglePassRange, class Size, class OutputIterator>
	OutputIterator copy_n(SinglePassRange range, Size n, OutputIterator result);
	template<class SinglePassRange, class OutputIterator, class Predicate>
	OutputIterator copy_if(SinglePassRange range, OutputIterator result, Predicate pred);
	template<class DoubleEndedRange1, class BidirectionalIterator2>
	BidirectionalIterator2 copy_backward(DoubleEndedRange1 range, BidirectionalIterator2 result);

	// 25.3.2, move:
	template<class SinglePassRange, class OutputIterator>
	OutputIterator move(SinglePassRange range, OutputIterator result);
	template<class DoubleEndedRange1, class BidirectionalIterator2>
	BidirectionalIterator2 move_backward(DoubleEndedRange1 range, BidirectionalIterator2 result);

	// 25.3.3, swap:
	template<class MultiPassRange1, class ForwardIterator2>
	ForwardIterator2 swap_ranges(MultiPassRange1 range1, ForwardIterator2 first2);

	template<class SinglePassRange, class OutputIterator, class UnaryOperation>
	OutputIterator transform(SinglePassRange range, OutputIterator result, UnaryOperation op);
	template<class SinglePassRange1, class InputIterator2, class OutputIterator, class BinaryOperation>
	OutputIterator transform(SinglePassRange1 range1, InputIterator2 first2, OutputIterator result, BinaryOperation binary_op);

	template<class MultiPassRange, class T>
	void replace(MultiPassRange range, const T& old_value, const T& new_value);
	template<class MultiPassRange, class Predicate, class T>
	void replace_if(MultiPassRange range, Predicate pred, const T& new_value);
	template<class SinglePassRange, class OutputIterator, class T>
	OutputIterator replace_copy(SinglePassRange range, OutputIterator result, const T& old_value, const T& new_value);
	template<class SinglePassRange, class OutputIterator, class Predicate, class T>
	OutputIterator replace_copy_if(SinglePassRange range, OutputIterator result, Predicate pred, const T& new_value);

	template<class MultiPassRange, class T>
	void fill(MultiPassRange range, const T& value);
	template<class OutputRange, class Size, class T>
	typename range_traits<OutputRange>::position_type fill_n(OutputRange first, Size n, const T& value);

	template<class MultiPassRange, class Generator>
	void generate(MultiPassRange range, Generator gen);
	template<class OutputRange, class Size, class Generator>
	typename range_traits<OutputRange>::position_type generate_n(OutputRange range, Size n, Generator gen);

	template<class MultiPassRange, class T>
	typename range_traits<MultiPassRange>::position_type remove(MultiPassRange range, const T& value);
	template<class MultiPassRange, class Predicate>
	typename range_traits<MultiPassRange>::position_type remove_if(MultiPassRange range, Predicate pred);
	template<class SinglePassRange, class OutputIterator, class T>
	OutputIterator remove_copy(SinglePassRange range, OutputIterator result, const T& value);
	template<class SinglePassRange, class OutputIterator, class Predicate>
	OutputIterator remove_copy_if(SinglePassRange range, OutputIterator result, Predicate pred);

	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::position_type unique(MultiPassRange range);
	template<class MultiPassRange, class BinaryPredicate>
	typename range_traits<MultiPassRange>::position_type unique(MultiPassRange range, BinaryPredicate pred);
	template<class SinglePassRange, class OutputIterator>
	OutputIterator unique_copy(SinglePassRange range, OutputIterator result);
	template<class SinglePassRange, class OutputIterator, class BinaryPredicate>
	OutputIterator unique_copy(SinglePassRange range, OutputIterator result, BinaryPredicate pred);

	template<class DoubleEndedRange>
	void reverse(DoubleEndedRange range);
	template<class DoubleEndedRange, class OutputIterator>
	OutputIterator reverse_copy(DoubleEndedRange range, OutputIterator result);

	template<class MultiPassRange>
	typename MultiPassRange::position_type rotate(MultiPassRange range, typename MultiPassRange::position_type middle);
	template<class MultiPassRange, class OutputIterator>
	OutputIterator rotate_copy(MultiPassRange range, typename MultiPassRange::position_type middle, OutputIterator result);

	template<class RandomAccessRange>
	void random_shuffle(RandomAccessRange range);
	template<class RandomAccessRange, class RandomNumberGenerator>
	void random_shuffle(RandomAccessRange range, RandomNumberGenerator&& rand);
	template<class RandomAccessRange, class UniformRandomNumberGenerator>
	void shuffle(RandomAccessRange range, UniformRandomNumberGenerator&& rand);

	// 25.3.13, partitions:
	template <class SinglePassRange, class Predicate>
	bool is_partitioned(SinglePassRange range, Predicate pred);
	template<class MultiPassRange, class Predicate>
	typename range_traits<MultiPassRange>::position_type partition(MultiPassRange range, Predicate pred);
	template<class DoubleEndedRange, class Predicate>
	typename range_traits<DoubleEndedRange>::position_type stable_partition(DoubleEndedRange range, Predicate pred);
	template <class SinglePassRange, class OutputIterator1, class OutputIterator2, class Predicate>
	std::pair<OutputIterator1, OutputIterator2> partition_copy(SinglePassRange range, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred);
	template<class MultiPassRange, class Predicate>
	typename range_traits<MultiPassRange>::position_type partition_point(MultiPassRange range, Predicate pred);

	// 25.4, sorting and related operations:
	// 25.4.1, sorting:
	template<class RandomAccessRange>
	void sort(RandomAccessRange range);
	template<class RandomAccessRange, class Compare>
	void sort(RandomAccessRange range, Compare comp);

	template<class RandomAccessRange>
	void stable_sort(RandomAccessRange range);
	template<class RandomAccessRange, class Compare>
	void stable_sort(RandomAccessRange range, Compare comp);

	template<class RandomAccessRange>
	void partial_sort(RandomAccessRange range, typename range_traits<RandomAccessRange>::position_type middle);
	template<class RandomAccessRange, class Compare>
	void partial_sort(RandomAccessRange range, typename range_traits<RandomAccessRange>::position_type middle, Compare comp);
	template<class SinglePassRange, class RandomAccessRange>
	typename range_traits<RandomAccessRange>::position_type partial_sort_copy(SinglePassRange range, RandomAccessRange result_range);
	template<class SinglePassRange, class RandomAccessRange, class Compare>
	typename range_traits<RandomAccessRange>::position_type partial_sort_copy(SinglePassRange range, RandomAccessRange result_range, Compare comp);
	template<class MultiPassRange>
	bool is_sorted(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	bool is_sorted(MultiPassRange range, Compare comp);
	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::position_type is_sorted_until(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	typename range_traits<MultiPassRange>::position_type is_sorted_until(MultiPassRange range, Compare comp);

	template<class RandomAccessRange>
	void nth_element(RandomAccessRange range, typename range_traits<RandomAccessRange>::position_type nth);
	template<class RandomAccessRange, class Compare>
	void nth_element(RandomAccessRange range, typename range_traits<RandomAccessRange>::position_type nth, Compare comp);

	// 25.4.3, binary search:
	template<class MultiPassRange, class T>
	typename range_traits<MultiPassRange>::position_type lower_bound(MultiPassRange range, const T& value);
	template<class MultiPassRange, class T, class Compare>
	typename range_traits<MultiPassRange>::position_type lower_bound(MultiPassRange range, const T& value, Compare comp);
	template<class MultiPassRange, class T>
	typename range_traits<MultiPassRange>::position_type upper_bound(MultiPassRange range, const T& value);
	template<class MultiPassRange, class T, class Compare>
	typename range_traits<MultiPassRange>::position_type upper_bound(MultiPassRange range, const T& value, Compare comp);

	template<class MultiPassRange, class T>
	MultiPassRange equal_range(MultiPassRange range, const T& value);
	template<class MultiPassRange, class T, class Compare>
	MultiPassRange equal_range(MultiPassRange range, const T& value, Compare comp);

	template<class MultiPassRange, class T>
	bool binary_search(MultiPassRange range, const T& value);
	template<class MultiPassRange, class T, class Compare>
	bool binary_search(MultiPassRange range, const T& value, Compare comp);

	// 25.4.4, merge:
	template<class SinglePassRange1, class SinglePassRange2, class OutputIterator>
	OutputIterator merge(SinglePassRange1 range1, SinglePassRange2 range2, OutputIterator result);
	template<class SinglePassRange1, class SinglePassRange2, class OutputIterator, class Compare>
	OutputIterator merge(SinglePassRange1 range1, SinglePassRange2 range2, OutputIterator result, Compare comp);

	template<class DoubleEndedRange>
	void inplace_merge(DoubleEndedRange range, typename range_traits<DoubleEndedRange>::position_type middle);
	template<class DoubleEndedRange, class Compare>
	void inplace_merge(DoubleEndedRange range, typename range_traits<DoubleEndedRange>::position_type middle, Compare comp);

	// 25.4.5, set operations:
	template<class SinglePassRange1, class InputRange2>
	bool includes(SinglePassRange1 range1, InputRange2 range2);
	template<class SinglePassRange1, class InputRange2, class Compare>
	bool includes(SinglePassRange1 range1, InputRange2 range2, Compare comp);

	template<class SinglePassRange1, class InputRange2, class OutputIterator>
	OutputIterator set_union(SinglePassRange1 range1, InputRange2 range2, OutputIterator result);
	template<class SinglePassRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_union(SinglePassRange1 range1, InputRange2 range2, OutputIterator result, Compare comp);

	template<class SinglePassRange1, class InputRange2, class OutputIterator>
	OutputIterator set_intersection(SinglePassRange1 range1, InputRange2 range2, OutputIterator result);
	template<class SinglePassRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_intersection(SinglePassRange1 range1, InputRange2 range2, OutputIterator result, Compare comp);

	template<class SinglePassRange1, class InputRange2, class OutputIterator>
	OutputIterator set_difference(SinglePassRange1 range1, InputRange2 range2, OutputIterator result);
	template<class SinglePassRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_difference(SinglePassRange1 range1, InputRange2 range2, OutputIterator result, Compare comp);

	template<class SinglePassRange1, class InputRange2, class OutputIterator>
	OutputIterator set_symmetric_difference(SinglePassRange1 range1, InputRange2 range2, OutputIterator result);
	template<class SinglePassRange1, class InputRange2, class OutputIterator, class Compare>
	OutputIterator set_symmetric_difference(SinglePassRange1 range1, InputRange2 range2, OutputIterator result, Compare comp);

	// 25.4.6, heap operations:
	template<class RandomAccessRange>
	void push_heap(RandomAccessRange range);
	template<class RandomAccessRange, class Compare>
	void push_heap(RandomAccessRange range, Compare comp);

	template<class RandomAccessRange>
	void pop_heap(RandomAccessRange range);
	template<class RandomAccessRange, class Compare>
	void pop_heap(RandomAccessRange range, Compare comp);

	template<class RandomAccessRange>
	void make_heap(RandomAccessRange range);
	template<class RandomAccessRange, class Compare>
	void make_heap(RandomAccessRange range, Compare comp);

	template<class RandomAccessRange>
	void sort_heap(RandomAccessRange range);
	template<class RandomAccessRange, class Compare>
	void sort_heap(RandomAccessRange range, Compare comp);

	template<class RandomAccessRange>
	bool is_heap(RandomAccessRange range);
	template<class RandomAccessRange, class Compare>
	bool is_heap(RandomAccessRange range, Compare comp);
	template<class RandomAccessRange>
	typename range_traits<RandomAccessRange>::position_type is_heap_until(RandomAccessRange range);
	template<class RandomAccessRange, class Compare>
	typename range_traits<RandomAccessRange>::position_type is_heap_until(RandomAccessRange range, Compare comp);

	// 25.4.7, minimum and maximum:
	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::position_type min_element(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	typename range_traits<MultiPassRange>::position_type min_element(MultiPassRange range, Compare comp);
	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::position_type max_element(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	typename range_traits<MultiPassRange>::position_type max_element(MultiPassRange range, Compare comp);
	template<class MultiPassRange>
	std::pair<typename range_traits<MultiPassRange>::position_type, typename range_traits<MultiPassRange>::position_type>
		minmax_element(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	std::pair<typename range_traits<MultiPassRange>::position_type, typename range_traits<MultiPassRange>::position_type>
		minmax_element(MultiPassRange range, Compare comp);

	template<class SinglePassRange1, class SinglePassRange2>
	bool lexicographical_compare(SinglePassRange1 range1, SinglePassRange2 range2);
	template<class SinglePassRange1, class SinglePassRange2, class Compare>
	bool lexicographical_compare(SinglePassRange1 range1, SinglePassRange2 range2, Compare comp);

	// 25.4.9, permutations:
	template<class DoubleEndedRange>
	bool next_permutation(DoubleEndedRange range);
	template<class DoubleEndedRange, class Compare>
	bool next_permutation(DoubleEndedRange range, Compare comp);
	template<class DoubleEndedRange>
	bool prev_permutation(DoubleEndedRange range);
	template<class DoubleEndedRange, class Compare>
	bool prev_permutation(DoubleEndedRange range, Compare comp);
}

#include "algorithm.inl"

#endif