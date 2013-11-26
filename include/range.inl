namespace stdext
{
	template <class Range, class Iterator, class RangeCategory>
	bool detail::iterator_range_base<Range, Iterator, RangeCategory, output_range_tag>::empty() const
	{
		const Range& range = *static_cast<const Range*>(this);
		return first == last;
	}

	template <class Range, class Iterator, class RangeCategory>
	Range& detail::iterator_range_base<Range, Iterator, RangeCategory, output_range_tag>::front()
	{
		return static_cast<Range&>(*this);
	}

	template <class Range, class Iterator, class RangeCategory>
	void detail::iterator_range_base<Range, Iterator, RangeCategory, output_range_tag>::drop_first()
	{
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, output_range_tag>::position_type
		detail::iterator_range_base<Range, Iterator, RangeCategory, output_range_tag>::begin_pos() const
	{
		return *this;
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, output_range_tag>::position_type
		detail::iterator_range_base<Range, Iterator, RangeCategory, output_range_tag>::end_pos() const
	{
		return Range();
	}

	template <class Range, class Iterator, class RangeCategory>
	Range& detail::iterator_range_base<Range, Iterator, RangeCategory, output_range_tag>::at_pos(position_type pos)
	{
		return pos;
	}

	template <class Range, class Iterator, class RangeCategory>
	Range& detail::iterator_range_base<Range, Iterator, RangeCategory, output_range_tag>::operator =
		(typename std::iterator_traits<Iterator>::value_type const& value)
	{
		Range& range = static_cast<Range&>(*this);
		*range.first = value;
		return range;
	}

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
	void detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::drop_first()
	{
		Range& range = *static_cast<Range*>(this);
		std::advance(range.first, 1);
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::reference
		detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::at_pos(position_type pos) const
	{
		return *pos;
	}
	
	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::position_type
		detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::begin_pos() const
	{
		const Range& range = *static_cast<const Range*>(this);
		return range.first;
	}

	template <class Range, class Iterator, class RangeCategory>
	void detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::begin_pos(position_type pos)
	{
		Range& range = *static_cast<Range*>(this);
		range.first = pos;
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::position_type
		detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::end_pos() const
	{
		const Range& range = *static_cast<const Range*>(this);
		return range.last;
	}

	template <class Range, class Iterator, class RangeCategory>
	void detail::iterator_range_base<Range, Iterator, RangeCategory, single_pass_range_tag>::end_pos(position_type pos)
	{
		Range& range = *static_cast<Range*>(this);
		range.last = pos;
	}

	template <class Range, class Iterator, class RangeCategory>
	void detail::iterator_range_base<Range, Iterator, RangeCategory, multi_pass_range_tag>::advance_pos(position_type& p, difference_type n) const
	{
		std::advance(p, n);
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, multi_pass_range_tag>::difference_type
		detail::iterator_range_base<Range, Iterator, RangeCategory, multi_pass_range_tag>::distance(position_type first, position_type last) const
	{
		return std::distance(first, last);
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, double_ended_range_tag>::reference
		detail::iterator_range_base<Range, Iterator, RangeCategory, double_ended_range_tag>::back() const
	{
		const Range& range = *static_cast<const Range*>(this);
		return *std::reverse_iterator<Iterator>(range.last);
	}

	template <class Range, class Iterator, class RangeCategory>
	void detail::iterator_range_base<Range, Iterator, RangeCategory, double_ended_range_tag>::drop_last()
	{
		Range& range = *static_cast<Range*>(this);
		typename std::make_signed<size_type>::type offset = n;
		std::advance(range.first, -1);
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::reference
		detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::operator[](size_type n) const
	{
		const Range& range = *static_cast<const Range*>(this);
		return range.first[n];
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::reference
		detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::at(size_type n) const
	{
		// TODO: Range-check n
		const Range& range = *static_cast<const Range*>(this);
		return range.first[n];
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::position_type
		detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::position_at(size_type n) const
	{
		const Range& range = *static_cast<const Range*>(this);
		return range.first + n;
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::size_type
		detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::index_at(position_type pos) const
	{
		const Range& range = *static_cast<const Range*>(this);
		return size_type(pos - range.first);
	}

	template <class Range, class Iterator, class RangeCategory>
	typename detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::size_type
		detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::length() const
	{
		const Range& range = *static_cast<const Range*>(this);
		return std::distance(range.first, range.last);
	}

	template <class Range, class Iterator, class RangeCategory>
	void detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::drop_first(size_type n)
	{
		Range& range = *static_cast<Range*>(this);
		std::advance(range.first, n);
	}

	template <class Range, class Iterator, class RangeCategory>
	void detail::iterator_range_base<Range, Iterator, RangeCategory, random_access_range_tag>::drop_last(size_type n)
	{
		Range& range = *static_cast<Range*>(this);
		typename std::make_signed<size_type>::type offset = n;
		std::advance(range.first, -offset);
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
		typename range_traits<MultiPassRange>::size_type range_length(MultiPassRange range, multi_pass_range_tag)
		{
			typename range_traits<MultiPassRange>::size_type n = 0;
			for (; !range.empty(); range.drop_first())
				++n;

			return n;
		}

		template <class RandomAccessRange>
		typename range_traits<RandomAccessRange>::size_type range_length(RandomAccessRange range, random_access_range_tag)
		{
			return range.length();
		}
	}

	template <class MultiPassRange>
	typename range_traits<MultiPassRange>::size_type range_length(MultiPassRange range)
	{
		return detail::range_length(range, typename range_traits<MultiPassRange>::range_category());
	}

	template <class MultiPassRange>
	inline MultiPassRange range_before(MultiPassRange range, typename MultiPassRange::position_type pos)
	{
		range.end_pos(pos);
		return range;
	}

	template <class MultiPassRange>
	inline MultiPassRange range_after(MultiPassRange range, typename MultiPassRange::position_type pos)
	{
		range.begin_pos(pos);
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

	template <class Range>
	inline range_iterator<Range> range_begin(Range range)
	{
		return range_iterator<Range>(std::move(range));
	}

	template <class Range>
	inline range_iterator<Range> range_end(Range range)
	{
		return range_iterator<Range>();
	}

	template <class DoubleEndedRange>
	inline reverse_range<DoubleEndedRange> make_reverse_range(DoubleEndedRange range)
	{
		return reverse_range<DoubleEndedRange>(range);
	}

	template <class Iterator, class Range>
	Iterator& detail::range_iterator_base<Iterator, Range, output_range_tag>::operator*()
	{
		return static_cast<Iterator&>(*this);
	}

	template <class Iterator, class Range>
	Iterator& detail::range_iterator_base<Iterator, Range, output_range_tag>::operator++()
	{
		return static_cast<Iterator&>(*this);
	}

	template <class Iterator, class Range>
	Iterator& detail::range_iterator_base<Iterator, Range, output_range_tag>::operator++(int)
	{
		return static_cast<Iterator&>(*this);
	}

	template <class Iterator, class Range>
	Iterator& detail::range_iterator_base<Iterator, Range, output_range_tag>::operator=(typename range_traits<Range>::value_type const& value)
	{
		Iterator& i = static_cast<Iterator&>(*this);
		i.range.front() = value;
		i.range.drop_first();
		return i;
	}

	template <class Iterator, class Range>
	void detail::range_iterator_base<Iterator, Range, output_range_tag>::swap(range_iterator_base& other)
	{
	}

	template <class Iterator, class Range>
	inline typename detail::range_iterator_base<Iterator, Range, single_pass_range_tag>::reference
		detail::range_iterator_base<Iterator, Range, single_pass_range_tag>::operator*() const
	{
		return value;
	}

	template <class Iterator, class Range>
	inline typename detail::range_iterator_base<Iterator, Range, single_pass_range_tag>::pointer
		detail::range_iterator_base<Iterator, Range, single_pass_range_tag>::operator->() const
	{
		return &value;
	}

	template <class Iterator, class Range>
	inline Iterator& detail::range_iterator_base<Iterator, Range, single_pass_range_tag>::operator++()
	{
		Iterator& i = static_cast<Iterator&>(*this);
		i.range.drop_first();
		return i;
	}

	template <class Iterator, class Range>
	inline Iterator detail::range_iterator_base<Iterator, Range, single_pass_range_tag>::operator++(int)
	{
		Iterator& i = static_cast<Iterator&>(*this);
		Iterator tmp = i;
		++*this;
		return tmp;
	}

	template <class Iterator, class Range>
	inline void detail::range_iterator_base<Iterator, Range, single_pass_range_tag>::swap(range_iterator_base& other)
	{
		using std::swap;
		swap(value, other.value);
	}

	template <class Range>
	inline range_iterator<Range>::range_iterator() : range()
	{
	}

	template <class Range>
	inline range_iterator<Range>::range_iterator(Range r) : range(std::move(r))
	{
		++*this;
	}

	template <class Range>
	inline range_iterator<Range>::range_iterator(Range r, typename range_traits<Range>::position_type pos) : range(std::move(range))
	{
		range.begin_pos(pos);
	}

	template <class Range>
	inline void range_iterator<Range>::swap(range_iterator& other)
	{
		using std::swap;
		detail::range_iterator_base<range_iterator, Range>::swap(other);
		swap(range, other.range);
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

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline bool detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::empty() const
	{
		const DoubleEndedRange& r = *static_cast<const DoubleEndedRange*>(this);
		return r.range.empty();
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline typename detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::reference
		detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::front() const
	{
		const DoubleEndedRange& r = *static_cast<const DoubleEndedRange*>(this);
		return r.range.back();
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline typename detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::reference
		detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::back() const
	{
		const DoubleEndedRange& r = *static_cast<const DoubleEndedRange*>(this);
		return r.range.front();
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline void detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::drop_first()
	{
		DoubleEndedRange& r = *static_cast<DoubleEndedRange*>(this);
		r.range.drop_last();
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline void detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::drop_last()
	{
		DoubleEndedRange& r = *static_cast<DoubleEndedRange*>(this);
		r.range.drop_first();
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline typename detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::reference
		detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::at_pos(position_type pos) const
	{
		const DoubleEndedRange& r = *static_cast<const DoubleEndedRange*>(this);
		return range_before(r.range, pos).back();
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline typename detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::position_type
		detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::begin_pos() const
	{
		const DoubleEndedRange& r = *static_cast<const DoubleEndedRange*>(this);
		return r.range.end_pos();
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	void detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::begin_pos(position_type pos)
	{
		DoubleEndedRange& r = *static_cast<DoubleEndedRange*>(this);
		r.range.end_pos(pos);
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	typename detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::position_type
		detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::end_pos() const
	{
		const DoubleEndedRange& r = *static_cast<const DoubleEndedRange*>(this);
		return r.range.begin_pos();
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline void detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::end_pos(position_type pos)
	{
		DoubleEndedRange& r = *static_cast<DoubleEndedRange*>(this);
		r.range.begin_pos(pos);
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	void detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::advance_pos(position_type& p, difference_type n) const
	{
		const DoubleEndedRange& r = *static_cast<const DoubleEndedRange*>(this);
		r.range.advance_pos(p, -n);
	}

	template <class DoubleEndedRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	typename detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::difference_type
		detail::reverse_range_base<DoubleEndedRange, RangeCategory, T, Position, Size, Difference, Reference, double_ended_range_tag>::distance(position_type first, position_type last) const
	{
		const DoubleEndedRange& r = *static_cast<const DoubleEndedRange*>(this);
		return r.range.difference(last, first);
	}

	template <class RandomAccessRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline typename detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::reference
		detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::operator[](size_type n) const
	{
		const RandomAccessRange& r = *static_cast<const RandomAccessRange*>(this);
		return r.range[r.range.length() - n - 1];
	}

	template <class RandomAccessRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline typename detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::reference
		detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::at(size_type n) const
	{
		const RandomAccessRange& r = *static_cast<const RandomAccessRange*>(this);
		return r.range[r.range.length() - n - 1];
	}

	template <class RandomAccessRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline typename detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::position_type
		detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::position_at(size_type n) const
	{
		const RandomAccessRange& r = *static_cast<const RandomAccessRange*>(this);
		return r.range.position_at(r.range.length() - n);
	}

	template <class RandomAccessRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	typename detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::size_type
		detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::index_at(position_type pos) const
	{
		const RandomAccessRange& r = *static_cast<const RandomAccessRange*>(this);
		return r.range.length() - r.range.index_at(pos);
	}

	template <class RandomAccessRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline typename detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::size_type
		detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::length() const
	{
		const RandomAccessRange& r = *static_cast<const RandomAccessRange*>(this);
		return r.range.length();
	}

	template <class RandomAccessRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline void detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::drop_first(size_type n)
	{
		RandomAccessRange& r = *static_cast<RandomAccessRange*>(this);
		r.range.drop_last(n);
	}

	template <class RandomAccessRange, class RangeCategory, typename T, typename Position, typename Size, typename Difference, typename Reference>
	inline void detail::reverse_range_base<RandomAccessRange, RangeCategory, T, Position, Size, Difference, Reference, random_access_range_tag>::drop_last(size_type n)
	{
		RandomAccessRange& r = *static_cast<RandomAccessRange*>(this);
		r.range.drop_first(n);
	}

	template <class DoubleEndedRange>
	inline reverse_range<DoubleEndedRange>::reverse_range(DoubleEndedRange range) : range(range)
	{
	}

	template <class DoubleEndedRange>
	inline void reverse_range<DoubleEndedRange>::swap(reverse_range& other)
	{
		using std::swap;
		swap(range, other.range);
	}

	template <class Range>
	inline void swap(reverse_range<Range>& a, reverse_range<Range>& b)
	{
		a.swap(b);
	}
}