namespace stdext
{
	template <class Range>
	inline typename std::enable_if<is_multi_pass_range<Range>::value, Range>::type
		save(Range range)
	{
		return range;
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
	inline bool iterator_range<Iterator>::empty() const
	{
		return first == last;
	}

	template <class Iterator>
	inline typename iterator_range<Iterator>::reference iterator_range<Iterator>::front() const
	{
		return *first;
	}

	template <class Iterator>
	inline void iterator_range<Iterator>::shrink_front()
	{
		++first;
	}

	// Requires bidirectional_iterator_tag
	template <class Iterator>
	inline typename iterator_range<Iterator>::reference iterator_range<Iterator>::back() const
	{
		return *std::reverse_iterator<Iterator>(last);
	}

	template <class Iterator>
	inline void iterator_range<Iterator>::shrink_back()
	{
		--last;
	}

	// Requires random_access_iterator_tag
	template <class Iterator>
	inline typename iterator_range<Iterator>::reference iterator_range<Iterator>::operator[](size_type n)
	{
		return *(first + n);
	}

	template <class Iterator>
	inline typename iterator_range<Iterator>::size_type iterator_range<Iterator>::length()
	{
		return std::distance(first, last);
	}

	// RangeProvider via begin/end
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

	// Swap
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
}