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
	template <class RangeCategory, class T, class Position, class SizeType = std::size_t, class Reference = T&> struct range;
	template <class Iterator> class iterator_range;
	template <class Range> class range_iterator;

	// Derived types
	template <class DoubleEndedRange> class reverse_range;

	// Range categories
	struct output_range_tag;
	struct single_pass_range_tag;
	struct multi_pass_range_tag;
	struct double_ended_range_tag;
	struct random_access_range_tag;

	// Range type traits
	template <class Range> struct is_output_range;
	template <class Range> struct is_random_access_range;
	template <class Range> struct is_double_ended_range;
	template <class Range> struct is_multi_pass_range;
	template <class Range> struct is_single_pass_range;

	template <class Range> struct is_range;

	// Range properties
	template <class MultiPassRange>
	typename range_traits<MultiPassRange>::size_type range_length(MultiPassRange range);

	// Range operations
	template <class MultiPassRange>
	MultiPassRange range_before(MultiPassRange range, typename MultiPassRange::position_type pos);
	template <class MultiPassRange>
	MultiPassRange range_after(MultiPassRange range, typename MultiPassRange::position_type pos);

	// Range adapters
	namespace detail
	{
		using std::begin;

		template <class RangeProvider>
		auto make_range(RangeProvider& r) -> iterator_range<decltype(begin(r))>;
	}
	template <class RangeProvider> auto make_range(RangeProvider& r) -> decltype(detail::make_range(r));
	template <class Iterator> iterator_range<Iterator> make_range(Iterator first, Iterator last);

	template <class Range> range_iterator<Range> range_begin(Range range);
	template <class Range> range_iterator<Range> range_end(Range range);

	template <class DoubleEndedRange> reverse_range<DoubleEndedRange> make_reverse_range(DoubleEndedRange range);

	template <class Iterator> void swap(iterator_range<Iterator>& a, iterator_range<Iterator>& b);
	template <class Range> void swap(range_iterator<Range>& a, range_iterator<Range>& b);
	template <class Range> bool operator==(const range_iterator<Range>& lhs, const range_iterator<Range>& rhs);
	template <class Range> bool operator!=(const range_iterator<Range>& lhs, const range_iterator<Range>& rhs);
	template <class Range> void swap(reverse_range<Range>& a, reverse_range<Range>& b);

	struct output_range_tag { };
	struct single_pass_range_tag { };
	struct multi_pass_range_tag : single_pass_range_tag { };
	struct double_ended_range_tag : multi_pass_range_tag { };
	struct random_access_range_tag : double_ended_range_tag { };

	template <class Range>
	struct range_traits
	{
		typedef typename Range::range_category range_category;
		typedef typename Range::value_type value_type;
		typedef typename Range::position_type position_type;
		typedef typename Range::size_type size_type;
		typedef typename Range::reference reference;
	};

	template <class RangeCategory, class T, class Position, class Size, class Reference>
	struct range
	{
		typedef RangeCategory range_category;
		typedef T value_type;
		typedef Position position_type;
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
	struct is_output_range : std::is_base_of<output_range_tag, typename range_traits<Range>::range_category> { };
	template <class Range>
	struct is_range : std::conditional<is_single_pass_range<Range>::value || is_output_range<Range>::value,
		std::true_type, std::false_type>::type { };

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
		template <>
		struct iterator_range_category<std::output_iterator_tag>
		{
			typedef output_range_tag type;
		};

		template <class Range, class Iterator,
			class RangeCategory = typename iterator_range_category<typename std::iterator_traits<Iterator>::iterator_category>::type,
			class BaseCategory = RangeCategory>
		class iterator_range_base;

		template <class Range, class Iterator, class RangeCategory>
		class iterator_range_base<Range, Iterator, RangeCategory, output_range_tag> :
			public range<RangeCategory, void, Iterator, std::size_t, void>
		{
		public:
			bool empty() const;
			Range& front();
			void drop_first(size_type n = 1);

			Range& operator = (typename std::iterator_traits<Iterator>::value_type const& value);
		};

		template <class Range, class Iterator, class RangeCategory>
		class iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag> : public range<
			RangeCategory,
			typename std::iterator_traits<Iterator>::value_type,
			Iterator,
			typename std::make_unsigned<typename std::iterator_traits<Iterator>::difference_type>::type,
			typename std::iterator_traits<Iterator>::reference>
		{
		public:
			bool empty() const;
			reference front() const;
			void drop_first(size_type n = 1);
		};

		template <class Range, class Iterator, class RangeCategory>
		class iterator_range_base<Range, Iterator, RangeCategory, multi_pass_range_tag> :
			public iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>
		{
		public:
			reference at_pos(position_type pos) const;
			position_type begin_pos() const;
			position_type end_pos() const;
			void drop_before(position_type pos);
			void drop_after(position_type pos);
		};

		template <class Range, class Iterator, class RangeCategory>
		class iterator_range_base<Range, Iterator, RangeCategory, double_ended_range_tag> :
			public iterator_range_base<Range, Iterator, RangeCategory, multi_pass_range_tag>
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
			reference at(size_type n) const;
			position_type position_at(size_type n) const;
			size_type index_at(position_type pos) const;
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
		friend class detail::iterator_range_base<iterator_range, Iterator, _range_category, output_range_tag>;
		friend class detail::iterator_range_base<iterator_range, Iterator, _range_category, single_pass_range_tag>;
		friend class detail::iterator_range_base<iterator_range, Iterator, _range_category, multi_pass_range_tag>;
		friend class detail::iterator_range_base<iterator_range, Iterator, _range_category, double_ended_range_tag>;
		friend class detail::iterator_range_base<iterator_range, Iterator, _range_category, random_access_range_tag>;
	};

	namespace detail
	{
		template <class Iterator, class Range, class RangeCategory = typename range_traits<Range>::range_category>
		class range_iterator_base;

		template <class Iterator, class Range>
		class range_iterator_base<Iterator, Range, output_range_tag> : std::iterator<std::output_iterator_tag,
			void, void, void, void>
		{
		public:
			Iterator& operator*();
			Iterator& operator++();
			Iterator& operator++(int);

			Iterator& operator=(typename range_traits<Range>::value_type const& value);

			void swap(range_iterator_base& other);
		};

		template <class Iterator, class Range>
		class range_iterator_base<Iterator, Range, single_pass_range_tag> : std::iterator<std::input_iterator_tag,
			typename range_traits<Range>::value_type,
			typename std::make_signed<typename range_traits<Range>::size_type>::type,
			const typename range_traits<Range>::value_type*,
			const typename range_traits<Range>::value_type&
		>
		{
		public:
			reference operator*() const;
			pointer operator->() const;

			Iterator& operator++();
			Iterator operator++(int);

			void swap(range_iterator_base& other);

		private:
			value_type value;
		};
	}

	template <class Range>
	class range_iterator : public detail::range_iterator_base<range_iterator<Range>, Range>
	{
	public:
		range_iterator();
		range_iterator(Range r);
		range_iterator(Range r, typename range_traits<Range>::position_type pos);

	public:
		void swap(range_iterator& other);

	private:
		template <class Range>
		friend bool operator==(const range_iterator<Range>& lhs, const range_iterator<Range>& rhs);
		Range range;
	};

	namespace detail
	{
		template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Reference, class BaseCategory = RangeCategory>
		class reverse_range_base;

		template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Reference>
		class reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Reference, double_ended_range_tag> :
			public range<RangeCategory, T, Position, Size, Reference>
		{
		public:
			bool empty() const;

			reference front() const;
			reference back() const;

			void drop_first(size_type n = 1);
			void drop_last(size_type n = 1);

			reference at_pos(position_type pos) const;

			position_type begin_pos() const;
			position_type end_pos() const;

			void drop_before(position_type pos);
			void drop_after(position_type pos);
		};

		template <class RandomAccessRange, class RangeCategory, typename T, typename Position, typename Size, typename Reference>
		class reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Reference, random_access_range_tag> :
			public reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Reference, double_ended_range_tag>
		{
		public:
			reference operator[](size_type n) const;
			reference at(size_type n) const;
			position_type position_at(size_type n) const;
			size_type index_at(position_type pos) const;
			size_type length() const;
		};
	}

	template <class DoubleEndedRange>
	class reverse_range : public detail::reverse_range_base<reverse_range<DoubleEndedRange>,
		typename range_traits<DoubleEndedRange>::range_category,
		typename range_traits<DoubleEndedRange>::value_type,
		typename range_traits<DoubleEndedRange>::position_type,
		typename range_traits<DoubleEndedRange>::size_type,
		typename range_traits<DoubleEndedRange>::reference>
	{
	public:
		reverse_range(DoubleEndedRange range);

	public:
		void swap(reverse_range& other);

	private:
		DoubleEndedRange range;
	};
}

#include "range.inl"

#endif