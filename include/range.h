#ifndef STDEXT_RANGE_INCLUDED
#define STDEXT_RANGE_INCLUDED
#pragma once

#include <iterator>
#include <type_traits>
#include <utility>

namespace stdext
{
	// Basic types
	template <class Range> struct range_traits;
	template <class Iterator> class iterator_range;
	template <class Range> class range_iterator;

	// Range categories
	struct single_pass_range_tag;
	struct multi_pass_range_tag;
	struct double_ended_range_tag;
	struct random_access_range_tag;

	// Range type traits
	template <class Range> struct is_random_access_range;
	template <class Range> struct is_double_ended_range;
	template <class Range> struct is_multi_pass_range;
	template <class Range> struct is_single_pass_range;

	template <class Range> struct is_range;

	// Range operations
	template <class Range>
	typename std::enable_if<is_multi_pass_range<Range>::value, Range>::type
		save(Range range);

	// Range adapters
	namespace detail
	{
		using std::begin;

		template <class RangeProvider>
		auto make_range(RangeProvider& r) -> iterator_range<decltype(begin(r))>;
	}
	template <class RangeProvider> auto make_range(RangeProvider& r) -> decltype(detail::make_range(r));
	template <class Iterator> iterator_range<Iterator> make_range(Iterator first, Iterator last);

	template <class Iterator> void swap(iterator_range<Iterator>& a, iterator_range<Iterator>& b);
	template <class Range> void swap(range_iterator<Range>& a, range_iterator<Range>& b);
	template <class Range> bool operator==(const range_iterator<Range>& lhs, const range_iterator<Range>& rhs);
	template <class Range> bool operator!=(const range_iterator<Range>& lhs, const range_iterator<Range>& rhs);

	namespace detail
	{
#define IS_VALID(expr) decltype(std::declval<Range>()expr)* = nullptr
		template <class Range>
		std::false_type is_random_access_range_checker(...);
		template <class Range>
		std::true_type is_random_access_range_checker(IS_VALID([0]), IS_VALID(.length()));
		template <class Range>
		std::false_type is_double_ended_range_checker(...);
		template <class Range>
		std::true_type is_double_ended_range_checker(IS_VALID(.back()), IS_VALID(.shrink_back()));
		template <class Range>
		std::false_type is_multi_pass_range_checker(...);
		template <class Range>
		std::true_type is_multi_pass_range_checker(IS_VALID(.save()));
		template <class Range>
		std::false_type is_single_pass_range_checker(...);
		template <class Range>
		std::true_type is_single_pass_range_checker(IS_VALID(.front()), IS_VALID(.shrink_front()), IS_VALID(.empty()));
#undef IS_VALID

		template <class T>
		typename T::size_type embedded_size_type(T&);
		size_t embedded_size_type(...);
	}

	template <class Range>
	struct is_random_access_range : decltype(detail::is_random_access_range_checker<Range>()) { };
	template <class Range>
	struct is_double_ended_range : decltype(detail::is_double_ended_range_checker<Range>()) { };
	template <class Range>
	struct is_multi_pass_range : decltype(detail::is_multi_pass_range_checker<Range>()) { };
	template <class Range>
	struct is_single_pass_range : decltype(detail::is_single_pass_range_checker<Range>()) { };

	template <class Range>
	struct is_range : is_single_pass_range<Range>::type { };

	struct single_pass_range_tag { };
	struct multi_pass_range_tag : single_pass_range_tag { };
	struct double_ended_range_tag : multi_pass_range_tag { };
	struct random_access_range_tag : double_ended_range_tag { };

	template <class Range>
	struct range_traits
	{
	private:
		template <class Range>
		struct range_category_of
		{
			typedef
				typename std::conditional<is_random_access_range<Range>::value, random_access_range_tag,
					typename std::conditional<is_double_ended_range<Range>::value, double_ended_range_tag,
						typename std::conditional<is_multi_pass_range<Range>::value, multi_pass_range_tag,
							typename std::enable_if<is_single_pass_range<Range>::value, single_pass_range_tag>::type
						>::type
					>::type
				>::type type;
		};

	public:
		typedef typename range_category_of<Range>::type range_category;
		typedef decltype(std::declval<Range>().front()) reference;
		typedef typename std::remove_cv<typename std::remove_reference<reference>::type>::type value_type;
		typedef decltype(detail::embedded_size_type(std::declval<Range>())) size_type;
	};

	template <class Iterator>
	class iterator_range
	{
	public:
		typedef Iterator iterator;
		typedef typename std::iterator_traits<iterator>::reference reference;
		typedef typename std::make_unsigned<typename std::iterator_traits<iterator>::difference_type>::type size_type;
		typedef typename std::iterator_traits<iterator>::value_type value_type;

	public:
		iterator_range();
		iterator_range(iterator first, iterator last);

	public:
		bool empty() const;

		reference front() const;
		void shrink_front();

		// Requires bidirectional_iterator_tag
		reference back() const;
		void shrink_back();

		// Requires random_access_iterator_tag
		reference operator[](size_type n);
		size_type length();

		// RangeProvider via begin/end
		iterator begin() const;
		iterator end() const;

		// Swap
		void swap(iterator_range& other);

	private:
		iterator first, last;
	};

	template <class Range>
	class range_iterator : std::iterator<std::input_iterator_tag,
		typename range_traits<Range>::value_type,
		typename std::make_signed<typename range_traits<Range>::size_type>::type,
		const typename range_traits<Range>::value_type*,
		const typename range_traits<Range>::value_type&
	>
	{
	public:
		range_iterator();
		range_iterator(Range& r);

	public:
		reference operator*() const;
		pointer operator->() const;

		range_iterator& operator++();
		range_iterator operator++(int);

		void swap(range_iterator& other);

	private:
		template <class Range>
		friend bool operator==(const range_iterator<Range>& lhs, const range_iterator<Range>& rhs);
		Range* range;
		value_type value;
	};
}

#include "range.inl"

#endif