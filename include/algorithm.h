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
	template<class InputIterator, class T>
	InputIterator find(iterator_range<InputIterator> range, const T& value);
	template<class InputIterator, class Predicate>
	InputIterator find_if(iterator_range<InputIterator> range, Predicate pred);
	template<class InputIterator, class Predicate>
	InputIterator find_if_not(iterator_range<InputIterator> range, Predicate pred);
	template<class ForwardIterator, class MultiPassRange>
	ForwardIterator find_end(iterator_range<ForwardIterator> range1, MultiPassRange range2);
	template<class ForwardIterator, class MultiPassRange, class BinaryPredicate>
	ForwardIterator find_end(iterator_range<ForwardIterator> range1, MultiPassRange range2, BinaryPredicate pred);

	template<class InputIterator, class MultiPassRange>
	InputIterator find_first_of(iterator_range<InputIterator> range1, MultiPassRange range2);
	template<class InputIterator, class MultiPassRange, class BinaryPredicate>
	InputIterator find_first_of(iterator_range<InputIterator> range1, MultiPassRange range2, BinaryPredicate pred);

	template<class ForwardIterator>
	ForwardIterator adjacent_find(iterator_range<ForwardIterator> range);
	template<class ForwardIterator, class BinaryPredicate>
	ForwardIterator adjacent_find(iterator_range<ForwardIterator> range, BinaryPredicate pred);

	template<class SinglePassRange, class T>
	typename range_traits<SinglePassRange>::size_type count(SinglePassRange range, const T& value);
	template<class SinglePassRange, class Predicate>
	typename range_traits<SinglePassRange>::size_type count_if(SinglePassRange range, Predicate pred);

	template<class InputIterator1, class InputIterator2>
	std::pair<InputIterator1, InputIterator2> mismatch(iterator_range<InputIterator1> range1, InputIterator2 first2);
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	std::pair<InputIterator1, InputIterator2> mismatch(iterator_range<InputIterator1> range1, InputIterator2 first2, BinaryPredicate pred);
	template<class InputIterator1, class InputIterator2>
	std::pair<InputIterator1, InputIterator2> mismatch(iterator_range<InputIterator1> range1, iterator_range<InputIterator2> range2);
	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	std::pair<InputIterator1, InputIterator2> mismatch(iterator_range<InputIterator1> range1, iterator_range<InputIterator2> range2, BinaryPredicate pred);

	template<class SinglePassRange1, class InputIterator2>
	bool equal(SinglePassRange1 range1, InputIterator2 first2);
	template <class SinglePassRange1, class InputIterator2, class BinaryPredicate>
	bool equal(SinglePassRange1 range1, InputIterator2 first2, BinaryPredicate pred);
	template<class SinglePassRange1, class SinglePassRange2>
	bool equal(SinglePassRange1 range1, SinglePassRange2 range2);
	template<class SinglePassRange1, class SinglePassRange2, class BinaryPredicate>
	bool equal(SinglePassRange1 range1, SinglePassRange2 range2, BinaryPredicate pred);

	template<class MultiPassRange1, class ForwardIterator2>
	bool is_permutation(MultiPassRange1 range1, ForwardIterator2 first2);
	template<class MultiPassRange1, class ForwardIterator2, class BinaryPredicate>
	bool is_permutation(MultiPassRange1 range1, ForwardIterator2 first2, BinaryPredicate pred);
	template<class MultiPassRange1, class MultiPassRange2>
	bool is_permutation(MultiPassRange1 range1, MultiPassRange2 range2);
	template<class MultiPassRange1, class MultiPassRange2, class BinaryPredicate>
	bool is_permutation(MultiPassRange1 range1, MultiPassRange2 range2, BinaryPredicate pred);

	template<class ForwardIterator, class MultiPassRange>
	ForwardIterator search(iterator_range<ForwardIterator> range1, MultiPassRange range2);
	template<class ForwardIterator, class MultiPassRange, class BinaryPredicate>
	ForwardIterator search(iterator_range<ForwardIterator> range1, MultiPassRange range2, BinaryPredicate pred);
	template<class ForwardIterator, class Size, class T>
	ForwardIterator search_n(iterator_range<ForwardIterator> range, Size count, const T& value);
	template <class ForwardIterator, class Size, class T, class BinaryPredicate>
	ForwardIterator search_n(iterator_range<ForwardIterator> range, Size count, const T& value, BinaryPredicate pred);

	// 25.3, modifying sequence operations:
	// 25.3.1, copy:
	template<class SinglePassRange, class OutputIterator>
	OutputIterator copy(SinglePassRange range, OutputIterator result);
	template<class InputIterator, class Size, class OutputIterator>
	OutputIterator copy_n(InputIterator first, Size n, OutputIterator result);
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
	template<class ForwardIterator1, class ForwardIterator2>
	void iter_swap(ForwardIterator1 a, ForwardIterator2 b);

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
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value);

	template<class MultiPassRange, class Generator>
	void generate(MultiPassRange range, Generator gen);
	template<class OutputIterator, class Size, class Generator>
	OutputIterator generate_n(OutputIterator first, Size n, Generator gen);

	template<class MultiPassRange, class T>
	typename range_traits<MultiPassRange>::iterator remove(MultiPassRange range, const T& value);
	template<class MultiPassRange, class Predicate>
	typename range_traits<MultiPassRange>::iterator remove_if(MultiPassRange range, Predicate pred);
	template<class SinglePassRange, class OutputIterator, class T>
	OutputIterator remove_copy(SinglePassRange range, OutputIterator result, const T& value);
	template<class SinglePassRange, class OutputIterator, class Predicate>
	OutputIterator remove_copy_if(SinglePassRange range, OutputIterator result, Predicate pred);

	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::iterator unique(MultiPassRange range);
	template<class MultiPassRange, class BinaryPredicate>
	typename range_traits<MultiPassRange>::iterator unique(MultiPassRange range, BinaryPredicate pred);
	template<class SinglePassRange, class OutputIterator>
	OutputIterator unique_copy(SinglePassRange range, OutputIterator result);
	template<class SinglePassRange, class OutputIterator, class BinaryPredicate>
	OutputIterator unique_copy(SinglePassRange range, OutputIterator result, BinaryPredicate pred);

	template<class DoubleEndedRange>
	void reverse(DoubleEndedRange range);
	template<class DoubleEndedRange, class OutputIterator>
	OutputIterator reverse_copy(DoubleEndedRange range, OutputIterator result);

	template<class ForwardIterator>
	ForwardIterator rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last);
	template<class ForwardIterator, class OutputIterator>
	OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result);

	template<class RandomAccessIterator>
	void random_shuffle(RandomAccessIterator first, RandomAccessIterator last);
	template<class RandomAccessIterator, class RandomNumberGenerator>
	void random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator&& rand);
	template<class RandomAccessIterator, class UniformRandomNumberGenerator>
	void shuffle(RandomAccessIterator first, RandomAccessIterator last, UniformRandomNumberGenerator&& rand);

	// 25.3.13, partitions:
	template <class SinglePassRange, class Predicate>
	bool is_partitioned(SinglePassRange range, Predicate pred);

	template<class MultiPassRange, class Predicate>
	typename range_traits<MultiPassRange>::iterator partition(MultiPassRange range, Predicate pred);
	template<class DoubleEndedRange, class Predicate>
	typename range_traits<DoubleEndedRange>::iterator stable_partition(DoubleEndedRange range, Predicate pred);
	template <class SinglePassRange, class OutputIterator1, class OutputIterator2, class Predicate>
	std::pair<OutputIterator1, OutputIterator2> partition_copy(SinglePassRange range, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred);
	template<class MultiPassRange, class Predicate>
	typename range_traits<MultiPassRange>::iterator partition_point(MultiPassRange range, Predicate pred);

	// 25.4, sorting and related operations:
	// 25.4.1, sorting:
	template<class RandomAccessIterator>
	void sort(RandomAccessIterator first, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

	template<class RandomAccessIterator>
	void stable_sort(RandomAccessIterator first, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	void stable_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

	template<class RandomAccessIterator>
	void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Compare comp);
	template<class SinglePassRange, class RandomAccessIterator>
	RandomAccessIterator partial_sort_copy(SinglePassRange range, RandomAccessIterator result_first, RandomAccessIterator result_last);
	template<class SinglePassRange, class RandomAccessIterator, class Compare>
	RandomAccessIterator partial_sort_copy(SinglePassRange range, RandomAccessIterator result_first, RandomAccessIterator result_last, Compare comp);
	template<class MultiPassRange>
	bool is_sorted(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	bool is_sorted(MultiPassRange range, Compare comp);
	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::iterator is_sorted_until(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	typename range_traits<MultiPassRange>::iterator is_sorted_until(MultiPassRange range, Compare comp);

	template<class RandomAccessIterator>
	void nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	void nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare comp);

	// 25.4.3, binary search:
	template<class MultiPassRange, class T>
	typename range_traits<MultiPassRange>::iterator lower_bound(MultiPassRange range, const T& value);
	template<class MultiPassRange, class T, class Compare>
	typename range_traits<MultiPassRange>::iterator lower_bound(MultiPassRange range, const T& value, Compare comp);
	template<class MultiPassRange, class T>
	typename range_traits<MultiPassRange>::iterator upper_bound(MultiPassRange range, const T& value);
	template<class MultiPassRange, class T, class Compare>
	typename range_traits<MultiPassRange>::iterator upper_bound(MultiPassRange range, const T& value, Compare comp);

	template<class MultiPassRange, class T>
	MultiPassRange equal_range(MultiPassRange range, const T& value);
	template<class MultiPassRange, class T, class Compare>
	MultiPassRange equal_range(MultiPassRange range, const T& value, Compare comp);

	template<class MultiPassRange, class T>
	bool binary_search(MultiPassRange range, const T& value);
	template<class MultiPassRange, class T, class Compare>
	bool binary_search(MultiPassRange range, const T& value, Compare comp);

	// 25.4.4, merge:
	template<class SinglePassRange1, class InputIterator2, class OutputIterator>
	OutputIterator merge(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result);
	template<class SinglePassRange1, class InputIterator2, class OutputIterator, class Compare>
	OutputIterator merge(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp);

	template<class BidirectionalIterator>
	void inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last);
	template<class BidirectionalIterator, class Compare>
	void inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Compare comp);

	// 25.4.5, set operations:
	template<class SinglePassRange1, class InputIterator2>
	bool includes(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2);
	template<class SinglePassRange1, class InputIterator2, class Compare>
	bool includes(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, Compare comp);

	template<class SinglePassRange1, class InputIterator2, class OutputIterator>
	OutputIterator set_union(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result);
	template<class SinglePassRange1, class InputIterator2, class OutputIterator, class Compare>
	OutputIterator set_union(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp);

	template<class SinglePassRange1, class InputIterator2, class OutputIterator>
	OutputIterator set_intersection(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result);
	template<class SinglePassRange1, class InputIterator2, class OutputIterator, class Compare>
	OutputIterator set_intersection(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp);

	template<class SinglePassRange1, class InputIterator2, class OutputIterator>
	OutputIterator set_difference(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result);
	template<class SinglePassRange1, class InputIterator2, class OutputIterator, class Compare>
	OutputIterator set_difference(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp);

	template<class SinglePassRange1, class InputIterator2, class OutputIterator>
	OutputIterator set_symmetric_difference(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result);
	template<class SinglePassRange1, class InputIterator2, class OutputIterator, class Compare>
	OutputIterator set_symmetric_difference(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp);

	// 25.4.6, heap operations:
	template<class RandomAccessIterator>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

	template<class RandomAccessIterator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

	template<class RandomAccessIterator>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

	template<class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

	template<class RandomAccessIterator>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
	template<class RandomAccessIterator>
	RandomAccessIterator is_heap_until(RandomAccessIterator first, RandomAccessIterator last);
	template<class RandomAccessIterator, class Compare>
	RandomAccessIterator is_heap_until(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

	// 25.4.7, minimum and maximum:
	template<class T> const T& min(const T& a, const T& b);
	template<class T, class Compare>
	const T& min(const T& a, const T& b, Compare comp);
	template<class T>
	T min(std::initializer_list<T> t);
	template<class T, class Compare>
	T min(std::initializer_list<T> t, Compare comp);

	template<class T> const T& max(const T& a, const T& b);
	template<class T, class Compare>
	const T& max(const T& a, const T& b, Compare comp);
	template<class T>
	T max(std::initializer_list<T> t);
	template<class T, class Compare>
	T max(std::initializer_list<T> t, Compare comp);

	template<class T> std::pair<const T&, const T&> minmax(const T& a, const T& b);
	template<class T, class Compare>
	std::pair<const T&, const T&> minmax(const T& a, const T& b, Compare comp);
	template<class T>
	std::pair<T, T> minmax(std::initializer_list<T> t);
	template<class T, class Compare>
	std::pair<T, T> minmax(std::initializer_list<T> t, Compare comp);

	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::iterator min_element(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	typename range_traits<MultiPassRange>::iterator min_element(MultiPassRange range, Compare comp);
	template<class MultiPassRange>
	typename range_traits<MultiPassRange>::iterator max_element(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	typename range_traits<MultiPassRange>::iterator max_element(MultiPassRange range, Compare comp);
	template<class MultiPassRange>
	MultiPassRange minmax_element(MultiPassRange range);
	template<class MultiPassRange, class Compare>
	MultiPassRange minmax_element(MultiPassRange range, Compare comp);

	template<class SinglePassRange1, class InputIterator2>
	bool lexicographical_compare(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2);
	template<class SinglePassRange1, class InputIterator2, class Compare>
	bool lexicographical_compare(SinglePassRange1 range1, InputIterator2 first2, InputIterator2 last2, Compare comp);

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