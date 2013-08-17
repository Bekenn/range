namespace stdext
{
	template <class Range, class Iterator, class RangeCategory>
	bool detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::empty() const
	{
		const Range& range = *static_cast<const Range*>(this);
		return range.first == range.last;
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::reference
		detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::front() const
	{
		const Range& range = *static_cast<const Range*>(this);
		return *range.first;
	}

	template <class Range, class Iterator, class RangeCategory>
	void detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::drop_first(size_type n)
	{
		Range& range = *static_cast<Range*>(this);
		std::advance(range.first, n);
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, double_ended_range_tag>::reference
		detail::iterator_range_base<Range, Iterator, RangeCategory, double_ended_range_tag>::back() const
	{
		const Range& range = *static_cast<const Range*>(this);
		return *std::reverse_iterator<Iterator>(range.last);
	}

	template <class Range, class Iterator, class RangeCategory>
	void detail::iterator_range_base<Range, Iterator, RangeCategory, double_ended_range_tag>::drop_last(size_type n)
	{
		Range& range = *static_cast<Range*>(this);
		typename std::make_signed<size_type>::type offset = n;
		std::advance(range.first, -offset);
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::reference
		detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::operator[](size_type n) const
	{
		const Range& range = *static_cast<const Range*>(this);
		return range.first[n];
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::size_type
		detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::length() const
	{
		const Range& range = *static_cast<const Range*>(this);
		return std::distance(range.first, range.last);
	}

	template <class Iterator>
	inline iterator_range<Iterator>::iterator_range() : first(), last()
	{
	}

	template <class Iterator>
	inline iterator_range<Iterator>::iterator_range(iterator first, iterator last) : first(first), last(last)
	{
	}

	template <class Iterator>
	inline typename iterator_range<Iterator>::iterator iterator_range<Iterator>::begin() const
	{
		return first;
	}

	template <class Iterator>
	inline typename iterator_range<Iterator>::iterator iterator_range<Iterator>::end() const
	{
		return last;
	}

	template <class Iterator>
	inline void iterator_range<Iterator>::swap(iterator_range& other)
	{
		using std::swap;
		swap(first, other.first);
		swap(last, other.last);
	}

	template <class Iterator>
	inline void swap(iterator_range<Iterator>& a, iterator_range<Iterator>& b)
	{
		a.swap(b);
	}

	namespace detail
	{
		template <class MultiPassRange>
		typename range_traits<MultiPassRange>::size_type length(MultiPassRange range, multi_pass_range_tag)
		{
			typename range_traits<MultiPassRange>::size_type n = 0;
			for (; !range.empty(); range.drop_first())
				++n;

			return n;
		}

		template <class RandomAccessRange>
		typename range_traits<RandomAccessRange>::size_type length(RandomAccessRange range, random_access_range_tag)
		{
			return range.length();
		}
	}

	template <class MultiPassRange>
	typename range_traits<MultiPassRange>::size_type length(MultiPassRange range)
	{
		return detail::length(range, typename range_traits<MultiPassRange>::range_category());
	}

	template <class Range>
	inline typename std::enable_if<is_multi_pass_range<Range>::value, Range>::type
		save(Range range)
	{
		return range;
	}

	namespace detail
	{
		using std::begin;
		using std::end;

		template <class RangeProvider>
		inline auto make_range(RangeProvider& r)->iterator_range<decltype(begin(r))>
		{
			return iterator_range<decltype(begin(r))>(begin(r), end(r));
		}
	}

	template <class RangeProvider>
	inline auto make_range(RangeProvider& r) -> decltype(detail::make_range(r))
	{
		return detail::make_range(r);
	}

	template <class Iterator>
	inline iterator_range<Iterator> make_range(Iterator first, Iterator last)
	{
		return iterator_range<Iterator>(std::move(first), std::move(last));
	}

	template <class MultiPassRange>
	subrange<MultiPassRange> make_subrange(MultiPassRange range, typename range_traits<MultiPassRange>::size_type first, typename range_traits<MultiPassRange>::size_type last)
	{
		return subrange<MultiPassRange>(std::move(range), std::move(first), std::move(last));
	}

	template <class Range>
	inline range_iterator<Range>::range_iterator() : range(nullptr)
	{
	}

	template <class Range>
	inline range_iterator<Range>::range_iterator(Range& r) : range(&r)
	{
		++*this;
	}

	template <class Range>
	inline typename range_iterator<Range>::reference range_iterator<Range>::operator*() const
	{
		return value;
	}

	template <class Range>
	inline typename range_iterator<Range>::pointer range_iterator<Range>::operator->() const
	{
		return &value;
	}

	template <class Range>
	inline range_iterator<Range>& range_iterator<Range>::operator++()
	{
		range->shrink_front();
		return *this;
	}

	template <class Range>
	inline range_iterator<Range> range_iterator<Range>::operator++(int)
	{
		range_iterator tmp = *this;
		++*this;
		return tmp;
	}

	template <class Range>
	inline void range_iterator<Range>::swap(range_iterator& other)
	{
		using std::swap;
		swap(range, other.range);
		swap(value, other.value);
	}

	template <class Range>
	inline void swap(range_iterator<Range>& a, range_iterator<Range>& b)
	{
		a.swap(b);
	}

	template <class Range>
	inline bool operator==(const range_iterator<Range>& lhs, const range_iterator<Range>& rhs)
	{
		return (lhs.range == rhs.range) && (lhs.value == rhs.value);
	}

	template <class Range> bool operator!=(const range_iterator<Range>& lhs, const range_iterator<Range>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Subrange, class Range>
	bool detail::subrange_base<Subrange, Range, single_pass_range_tag>::empty() const
	{
		const Subrange& subrange = *static_cast<const Subrange*>(this);
		return subrange.length == 0;
	}

	template <class Subrange, class Range>
	typename detail::subrange_base<Subrange, Range, single_pass_range_tag>::reference
		detail::subrange_base<Subrange, Range, single_pass_range_tag>::front() const
	{
		const Subrange& subrange = *static_cast<const Subrange*>(this);
		return subrange.range.front();
	}

	template <class Subrange, class Range>
	void detail::subrange_base<Subrange, Range, single_pass_range_tag>::drop_first(size_type n)
	{
		Subrange& subrange = *static_cast<Subrange*>(this);
		subrange.drop_first(n);
		length -= n;
	}

	template <class Subrange, class Range>
	typename detail::subrange_base<Subrange, Range, random_access_range_tag>::reference
		detail::subrange_base<Subrange, Range, random_access_range_tag>::back() const
	{
		const Subrange& subrange = *static_cast<const Subrange*>(this);
		return subrange.range.back();
	}

	template <class Subrange, class Range>
	void detail::subrange_base<Subrange, Range, random_access_range_tag>::drop_last(size_type n = 1)
	{
		Subrange& subrange = *static_cast<Subrange*>(this);
		subrange.length -= n;
	}

	template <class Subrange, class Range>
	typename detail::subrange_base<Subrange, Range, random_access_range_tag>::reference
		detail::subrange_base<Subrange, Range, random_access_range_tag>::operator[](size_type n) const
	{
		const Subrange& subrange = *static_cast<Subrange*>(this);
		return subrange[n];
	}

	template <class Subrange, class Range>
	typename detail::subrange_base<Subrange, Range, random_access_range_tag>::size_type
		detail::subrange_base<Subrange, Range, random_access_range_tag>::length() const
	{
		const Subrange& subrange = *static_cast<Subrange*>(this);
		return subrange.length;
	}

	namespace detail
	{
		template <class Range>
		void subrange_trim(Range& r, typename Range::size_type first, typename Range::size_type /* last */, single_pass_range_tag)
		{
			r.drop_first(first);
		}

		template <class Range>
		void subrange_trim(Range& r, typename Range::size_type first, typename Range::size_type last, random_access_range_tag)
		{
			r.drop_first(first);
			r.drop_last(r.length() - last - first);
		}
	}

	template <class MultiPassRange>
	subrange<MultiPassRange>::subrange(MultiPassRange r, typename range_traits<MultiPassRange>::size_type first, typename range_traits<MultiPassRange>::size_type last) :
		range(r), length(last - first)
	{
		detail::subrange_trim(range, first, last, typename range_traits<MultiPassRange>::range_category());
	}
}