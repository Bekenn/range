namespace stdext
{
	// make_range
	template <class Iterator>
	iterator_range<Iterator> make_range(Iterator first, Iterator last)
	{
		return iterator_range<Iterator>(first, last);
	}

	// Operations on ranges
	template <class Range>
	bool empty(const Range& r)
	{
		static_assert(is_range<Range>::value, __FUNCTION__ ": argument is not a range");
		return r.begin_pos() == r.end_pos();
	}

	template <class Range>
	range_iterator<Range> begin(const Range& r)
	{
		return range_iterator<Range>(&r, r.begin_pos());
	}

	template <class Range>
	range_iterator<Range> end(const Range& r)
	{
		return range_iterator<Range>(&r, r.end_pos());
	}

	template <class Range>
	typename range_traits<Range>::reference front(const Range& r)
	{
		static_assert(is_range<Range>::value, __FUNCTION__ ": argument is not a range");
		return r.at_pos(r.begin_pos());
	}

	template <class BidirectionalRange>
	typename range_traits<BidirectionalRange>::reference back(const BidirectionalRange& r)
	{
		static_assert(is_bidirectional_range<BidirectionalRange>::value, __FUNCTION__ ": argument is not a bidirectional range");
		auto p = r.end_pos();
		r.decrement_pos(p);
		return r.at_pos(p);
	}

	template <class Range>
	void drop_first(Range& r, typename range_traits<Range>::difference_type n)
	{
		static_assert(is_range<Range>::value, __FUNCTION__ ": argument is not a range");
		auto p = r.begin_pos();
		advance_pos(r, p, n);
		r.begin_pos(p);
	}

	template <class BidirectionalRange>
	void drop_last(BidirectionalRange& r, typename range_traits<BidirectionalRange>::difference_type n)
	{
		static_assert(is_bidirectional_range<BidirectionalRange>::value, __FUNCTION__ ": argument is not a bidirectional range");
		auto p = r.end_pos();
		advance(r, p, -n);
		r.end_pos(p);
	}

	namespace detail
	{
		template <class Range>
		typename range_traits<Range>::position_type& advance_pos_neg(const Range& r, typename range_traits<Range>::position_type& p, typename range_traits<Range>::difference_type n, std::false_type /* is_bidirectional_range */)
		{
			// throw something
		}

		template <class Range>
		typename range_traits<Range>::position_type& advance_pos_neg(const Range& r, typename range_traits<Range>::position_type& p, typename range_traits<Range>::difference_type n, std::true_type /* is_bidirectional_range */)
		{
			while (n-- > 0)
				r.decrement_pos(p);
		}

		template <class Range>
		typename range_traits<Range>::position_type& advance_pos(const Range& r, typename range_traits<Range>::position_type& p, typename range_traits<Range>::difference_type n, std::false_type /* is_random_access_range */)
		{
			if (n < 0)
				return advance_pos_neg(r, p, -n, is_bidirectional_range<Range>);

			while (n-- > 0)
				r.increment_pos(p);
		}

		template <class Range>
		typename range_traits<Range>::position_type& advance_pos(const Range& r, typename range_traits<Range>::position_type& p, typename range_traits<Range>::difference_type n, std::true_type /* is_random_access_range */)
		{
			return r.advance_pos(p, n);
		}
	}

	template <class Range>
	typename range_traits<Range>::position_type& advance_pos(const Range& r, typename range_traits<Range>::position_type& p, typename range_traits<Range>::difference_type n)
	{
		return detail::advance_pos(r, p, n, is_random_access_range<Range>());
	}

	template <class ForwardRange>
	typename range_traits<ForwardRange>::difference_type length(const ForwardRange& r)
	{
		return r.distance(r.begin_pos(), r.end_pos());
	}

	// iterator_range
	template <class C>
	iterator_range<typename detail::iterator_type<C>::type> make_range(C& c)
	{
		using std::begin;
		using std::end;
		return make_range(begin(c), end(c));
	}

	template <class C>
	iterator_range<typename detail::iterator_type<const C>::type> make_range(const C& c)
	{
		using std::begin;
		using std::end;
		return make_range(begin(c), end(c));
	}

	template <class Range>
	Range range_before(Range range, typename range_traits<Range>::position_type p)
	{
		range.end_pos(p);
		return range;
	}

	template <class Range>
	Range range_after(Range range, typename range_traits<Range>::position_type p)
	{
		range.begin_pos(p);
		return range;
	}

	template <class Range>
	Range subrange(Range range, typename range_traits<Range>::position_type first, typename range_traits<Range>::position_type last)
	{
		range.begin_pos(first);
		range.end_pos(last);
		return range;
	}
} // stdext