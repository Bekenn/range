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
	template <class RangeCategory, class T, class SizeType = std::size_t, class Reference = T&> struct range;
	template <class Iterator> class iterator_range;
	template <class Range> class range_iterator;

	// Derived types
	template <class Range> class subrange;

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

	struct single_pass_range_tag { };
	struct multi_pass_range_tag : single_pass_range_tag { };
	struct double_ended_range_tag : multi_pass_range_tag { };
	struct random_access_range_tag : double_ended_range_tag { };

	template <class Range>
	struct range_traits
	{
		typedef typename Range::range_category range_category;
		typedef typename Range::value_type value_type;
		typedef typename Range::size_type size_type;
		typedef typename Range::reference reference;
	};

	template <class RangeCategory, class T, class Size, class Reference>
	struct range
	{
		typedef RangeCategory range_category;
		typedef T value_type;
		typedef Size size_type;
		typedef Reference reference;
	};

	template <class Range>
	struct is_random_access_range : std::is_base_of<random_access_range_tag, typename range_traits<Range>::range_category> { };
	template <class Range>
	struct is_double_ended_range : std::is_base_of<double_ended_range_tag, typename range_traits<Range>::range_category> { };
	template <class Range>
	struct is_multi_pass_range : std::is_base_of<multi_pass_range_tag, typename range_traits<Range>::range_category> { };
	template <class Range>
	struct is_single_pass_range : std::is_base_of<single_pass_range_tag, typename range_traits<Range>::range_category> { };
	template <class Range>
	struct is_range : is_single_pass_range<Range> { };

	namespace detail
	{
		template <class IteratorCategory> struct iterator_range_category;
		template <>
		struct iterator_range_category<std::random_access_iterator_tag>
		{
			typedef random_access_range_tag type;
		};
		template <>
		struct iterator_range_category<std::bidirectional_iterator_tag>
		{
			typedef double_ended_range_tag type;
		};
		template <>
		struct iterator_range_category<std::forward_iterator_tag>
		{
			typedef multi_pass_range_tag type;
		};
		template <>
		struct iterator_range_category<std::input_iterator_tag>
		{
			typedef single_pass_range_tag type;
		};

		template <class Range, class Iterator,
			class RangeCategory = typename iterator_range_category<typename std::iterator_traits<Iterator>::iterator_category>::type,
			class BaseCategory = RangeCategory>
		class iterator_range_base;

		template <class Range, class Iterator, class RangeCategory>
		class iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag> : public range<
			RangeCategory,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::make_unsigned<typename std::iterator_traits<Iterator>::difference_type>::type,
			typename std::iterator_traits<Iterator>::reference>
		{
		public:
			bool empty() const;
			reference front() const;
			void drop_first(size_type n = 1);
		};

		template <class Range, class Iterator, class RangeCategory>
		class iterator_range_base<Range, Iterator, RangeCategory, double_ended_range_tag> :
			public iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>
		{
		public:
			reference back() const;
			void drop_last(size_type n = 1);
		};

		template <class Range, class Iterator, class RangeCategory>
		class iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag> :
			public iterator_range_base<Range, Iterator, RangeCategory, double_ended_range_tag>
		{
		public:
			reference operator[](size_type n) const;
			size_type length() const;
		};
	}

	template <class Iterator>
	class iterator_range : public detail::iterator_range_base<iterator_range<Iterator>, Iterator>
	{
	public:
		typedef Iterator iterator;

	public:
		iterator_range();
		iterator_range(iterator first, iterator last);

	public:
		iterator begin() const;
		iterator end() const;

		void swap(iterator_range& other);

	private:
		iterator first, last;

		typedef typename detail::iterator_range_category<typename std::iterator_traits<Iterator>::iterator_category>::type _range_category;
		friend class detail::iterator_range_base<iterator_range, Iterator, _range_category, single_pass_range_tag>;
		friend class detail::iterator_range_base<iterator_range, Iterator, _range_category, double_ended_range_tag>;
		friend class detail::iterator_range_base<iterator_range, Iterator, _range_category, random_access_range_tag>;
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

	namespace detail
	{
		template <class Subrange, class Range, class BaseCategory = typename range_traits<Range>::range_category>
		class subrange_base;

		template <class Subrange, class Range>
		class subrange_base<Subrange, Range, single_pass_range_tag> : public range<
			typename range_traits<Range>::range_category,
			typename range_traits<Range>::value_type,
			typename range_traits<Range>::size_type,
			typename range_traits<Range>::reference>
		{
			bool empty() const;
			reference front() const;
			void drop_first(size_type n = 1);
		};

		template <class Subrange, class Range>
		class subrange_base<Subrange, Range, random_access_range_tag> :
			public subrange_base<Subrange, Range, single_pass_range_tag>
		{
		public:
			reference back() const;
			void drop_last(size_type n = 1);
			reference operator[](size_type n) const;
			size_type length() const;
		};
	}

	template <class MultiPassRange>
	class subrange : public detail::subrange_base<subrange<MultiPassRange>, MultiPassRange>
	{
	public:
		subrange(MultiPassRange r, typename range_traits<MultiPassRange>::size_type first, typename range_traits<MultiPassRange>::size_type last);

	private:
		MultiPassRange range;
		typename range_traits<MultiPassRange>::size_type length;

		friend class detail::subrange_base<subrange, MultiPassRange, single_pass_range_tag>;
		friend class detail::subrange_base<subrange, MultiPassRange, double_ended_range_tag>;
		friend class detail::subrange_base<subrange, MultiPassRange, random_access_range_tag>;
	};
}

#include "range.inl"

#endif