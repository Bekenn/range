#ifndef STDEXT_RANGE_INCLUDED
#define STDEXT_RANGE_INCLUDED
#pragma once

#include <iterator>
#include <type_traits>
#include <utility>

namespace stdext
{
	namespace detail
	{
		using ::std::begin;
		using ::std::end;
	}

	struct single_pass_range_tag { };
	struct forward_range_tag : single_pass_range_tag { };
	struct double_ended_range_tag : forward_range_tag { };
	struct random_access_range_tag : double_ended_range_tag { };

	template <class Range> struct range_traits;
	template <class Iterator> class iterator_range;
	template <class Range> class range_iterator;

	namespace detail
	{
		template <class RangeProvider> auto make_range(RangeProvider& r) -> iterator_range<decltype(begin(r))>;
	}
	template <class RangeProvider> auto make_range(RangeProvider& r) -> decltype(detail::make_range(r));
	template <class Iterator> iterator_range<Iterator> make_range(Iterator first, Iterator last);

	template <class Range> range_iterator<Range> begin();
	template <class Range> range_iterator<Range> end();

	namespace detail
	{
#define IS_VALID(expr) decltype(std::declval<Range>()expr) = std::declval<decltype(std::declval<Range>()expr)>()
		template <class Range>
		std::false_type is_random_access_range(...);
		template <class Range>
		std::true_type is_random_access_range(IS_VALID([0]), IS_VALID(.length()));
		template <class Range>
		std::false_type is_double_ended_range(...);
		template <class Range>
		std::true_type is_double_ended_range(IS_VALID(.back()), IS_VALID(.shrink_back()));
		template <class Range>
		std::false_type is_multi_pass_range(...);
		template <class Range>
		std::true_type is_multi_pass_range(IS_VALID(.save()));
		template <class Range>
		std::false_type is_single_pass_range(...);
		template <class Range>
		std::true_type is_single_pass_range(IS_VALID(.front()), IS_VALID(.shrink_front()), IS_VALID(.empty()));

		template <class Range>
		std::false_type has_begin_end(...);
		template <class Range>
		std::true_type has_begin_end(IS_VALID(.begin()), IS_VALID(.end()));
#undef IS_VALID

		template <class T>
		struct same_type { typedef typename std::remove_reference<typename std::remove_cv<T>::type>::type type; };

		template <class Range>
		std::conditional<same_type<decltype(is_random_access_range<Range>())>::type::value, random_access_range_tag,
			std::conditional<same_type<decltype(is_double_ended_range<Range>())>::type::value, double_ended_range_tag,
				std::conditional<same_type<decltype(is_multi_pass_range<Range>())>::type::value, forward_range_tag,
					std::enable_if<same_type<decltype(is_single_pass_range<Range>())>::type::value, single_pass_range_tag>
				>
			>
		> range_type();

		template <class T>
		typename T::size_type embedded_size_type(T&);
		size_t embedded_size_type(...);
	}
	template <class Range>
	struct range_traits
	{
		typedef decltype(detail::range_type<Range>()) range_category;
		typedef decltype(std::declval<Range>().front()) reference;
		typedef decltype(std::declval<Range>().begin()) iterator;
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
		//typedef typename std::iterator_traits<iterator>::value_type value_type;

	public:
		iterator_range() : first(), last() { }
		iterator_range(iterator first, iterator last) : first(first), last(last) { }

	public:
		bool empty() const { return first == last; }

		reference front() const { return *first; }
		void shrink_front() { ++first; }

		iterator_range save() const { return *this; }

		// Requires bidirectional_iterator_tag
		reference back() const { return *std::reverse_iterator<iterator>(last); }
		void shrink_back() { --back; }

		// Requires random_access_iterator_tag
		reference operator[](size_type n) { return first[n]; }
		size_type length() { return last - first; }

		// RangeProvider via begin/end
		iterator begin() const { return first; }
		iterator end() const { return last; }

	private:
		iterator first, last;
	};

	namespace detail
	{
		template <class RangeCategory> struct to_iterator_category;
		template <class IteratorCategory> struct to_range_category;
#if 0
		template <> struct to_iterator_category<random_access_range_tag> { typedef std::random_access_iterator_tag type; };
		template <> struct to_iterator_category<double_ended_range_tag> { typedef std::bidirectional_iterator_tag type; };
#endif
		template <> struct to_iterator_category<forward_range_tag> { typedef std::forward_iterator_tag type; };
		template <> struct to_iterator_category<single_pass_range_tag> { typedef std::input_iterator_tag type; };

		template <> struct to_range_category<std::random_access_iterator_tag> { typedef random_access_range_tag type; };
		template <> struct to_range_category<std::bidirectional_iterator_tag> { typedef double_ended_range_tag type; };
		template <> struct to_range_category<std::forward_iterator_tag> { typedef forward_range_tag type; };
		template <> struct to_range_category<std::input_iterator_tag> { typedef single_pass_range_tag type; };
		template <> struct to_range_category<std::output_iterator_tag> { typedef single_pass_range_tag type; };
	}

	template <class Range>
	class range_iterator : std::iterator<typename detail::to_iterator_category<typename range_traits<Range>::range_category>::type,
		typename range_traits<Range>::value_type> //, difference_type, pointer, reference>
	{
	public:
		range_iterator() { }
		range_iterator(Range r) : range(r) { }

	public:
		reference operator*() { return range.front(); }
		pointer operator->() { return &range.front(); }

		range_iterator& operator++() { range.shrink_front(); return *this; }
		range_iterator operator++(int) { range_iterator t = *this; ++this; return t; }

	private:
		template <class Range>
		friend bool operator==(range_iterator<Range> lhs, range_iterator<Range> rhs);
		Range range;
	};

	template <class Range>
	bool operator==(range_iterator<Range> lhs, range_iterator<Range> rhs)
	{
		return (lhs.range == rhs.range) || (lhs.empty() && rhs.empty());
	}

	template <class Range>
	struct is_range : std::conditional<detail::same_type<decltype(detail::is_single_pass_range<Range>())>::type::value, std::true_type, std::false_type>::type { };

	namespace detail
	{
		template <class RangeProvider>
		auto make_range(RangeProvider& r) -> iterator_range<decltype(begin(r))>
		{
			return iterator_range<decltype(begin(r))>(begin(r), end(r));
		}
	}

	template <class RangeProvider>
	auto make_range(RangeProvider& r) -> decltype(detail::make_range(r))
	{
		return detail::make_range(r);
	}

	template <class Iterator>
	iterator_range<Iterator> make_range(Iterator first, Iterator last)
	{
		return iterator_range<Iterator>(first, last);
	}

	template <class Range>
	std::enable_if<is_range<Range>::value && !detail::same_type<decltype(detail::has_begin_end<Range>())>::type::value, range_iterator<Range>>
		begin(Range r)
	{
		return range_iterator<Range>(r);
	}

	template <class Range>
	std::enable_if<is_range<Range>::value && !detail::same_type<decltype(detail::has_begin_end<Range>())>::type::value, range_iterator<Range>>
		end(Range r)
	{
		return range_iterator<Range>();
	}
}

#endif