namespace stdext { namespace range
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

	// iterator_range
	template <class Range, class Iterator, class Category>
	typename detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::position_type
		detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::begin_pos() const noexcept
	{
		const auto& r = *static_cast<const Range*>(this);
		return r.first;
	}

	template <class Range, class Iterator, class Category>
	void detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::begin_pos(position_type p) noexcept
	{
		auto& r = *static_cast<Range*>(this);
		r.first = p;
	}

	template <class Range, class Iterator, class Category>
	typename detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::position_type
		detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::end_pos() const noexcept
	{
		const auto& r = *static_cast<const Range*>(this);
		return r.last;
	}

	template <class Range, class Iterator, class Category>
	void detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::end_pos(position_type p) noexcept
	{
		auto& r = *static_cast<Range*>(this);
		r.last = p;
	}

	template <class Range, class Iterator, class Category>
	typename detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::reference
		detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::at_pos(const position_type& p) const
	{
		return *p;
	}

	template <class Range, class Iterator, class Category>
	typename detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::position_type&
		detail::iterator_range_base<Range, Iterator, Category, input_range_tag>::increment_pos(position_type& p) const
	{
		return ++p;
	}

	template <class Range, class Iterator, class Category>
	typename detail::iterator_range_base<Range, Iterator, Category, forward_range_tag>::difference_type
		detail::iterator_range_base<Range, Iterator, Category, forward_range_tag>::distance_pos(position_type p1, position_type p2) const noexcept
	{
		return std::distance(p1, p2);
	}

	template <class Range, class Iterator, class Category>
	typename detail::iterator_range_base<Range, Iterator, Category, bidirectional_range_tag>::position_type&
		detail::iterator_range_base<Range, Iterator, Category, bidirectional_range_tag>::decrement_pos(position_type& p) const
	{
		--p;
	}

	template <class Range, class Iterator, class Category>
	typename detail::iterator_range_base<Range, Iterator, Category, random_access_range_tag>::position_type&
		detail::iterator_range_base<Range, Iterator, Category, random_access_range_tag>::advance_pos(position_type& p, difference_type n) const
	{
		std::advance(p, n);
		return p;
	}

	template <class Iterator>
	iterator_range<Iterator>::iterator_range(Iterator first, Iterator last) : first(first), last(last)
	{
	}

	template <class Iterator>
	Iterator iterator_range<Iterator>::begin() const noexcept
	{
		return first;
	}

	template <class Iterator>
	Iterator iterator_range<Iterator>::end() const noexcept
	{
		return last;
	}

	// range iterator
	template <class Iterator, class Range, class Category>
	typename detail::range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>::reference
		detail::range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>::operator * () const
	{
		const auto& i = *static_cast<const Iterator*>(this);
		return i.range->at_pos(i.p);
	}

	template <class Iterator, class Range, class Category>
	typename detail::range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>::pointer
		detail::range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>::operator -> () const
	{
		const auto& i = *static_cast<const Iterator*>(this);
		return &i.range->at_pos(i.p);
	}

	template <class Iterator, class Range, class Category>
	Iterator& detail::range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>::operator ++ ()
	{
		auto& i = *static_cast<Iterator*>(this);
		i.range->increment_pos(i.p);
		return i;
	}

	template <class Iterator, class Range, class Category>
	Iterator detail::range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>::operator ++ (int)
	{
		auto& i = *static_cast<Iterator*>(this);
		auto r = i;
		i.range->increment_pos(i.p);
		return r;
	}

	template <class Iterator, class Range, class Category>
	inline bool detail::operator == (const range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>& a,
									 const range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>& b)
	{
		const auto& ai = static_cast<const Iterator&>(a);
		const auto& bi = static_cast<const Iterator&>(b);
		return ai.range == bi.range
			&& ai.p == bi.p;
	}

	template <class Iterator, class Range, class Category>
	inline bool detail::operator != (const range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>& a,
									 const range_iterator_base<Iterator, Range, Category, std::input_iterator_tag>& b)
	{
		return !(a == b);
	}

	template <class Iterator, class Range, class Category>
	Iterator& detail::range_iterator_base<Iterator, Range, Category, std::bidirectional_iterator_tag>::operator -- ()
	{
		auto& i = *static_cast<Iterator*>(this);
		i.range->decrement_pos(i.p);
		return i;
	}

	template <class Iterator, class Range, class Category>
	Iterator detail::range_iterator_base<Iterator, Range, Category, std::bidirectional_iterator_tag>::operator -- (int)
	{
		auto& i = *static_cast<Iterator*>(this);
		auto r = i;
		i.range->decrement_pos(i.p);
		return r;
	}

	template <class Iterator, class Range, class Category>
	Iterator& detail::range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>::operator += (difference_type n)
	{
		auto& i = *static_cast<Iterator*>(this);
		i.range->advance_pos(i.p, n);
		return i;
	}

	template <class Iterator, class Range, class Category>
	Iterator& detail::range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>::operator -= (difference_type n)
	{
		auto& i = *static_cast<Iterator*>(this);
		i.range->advance_pos(i.p, -n);
		return i;
	}

	template <class Iterator, class Range, class Category>
	typename detail::range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>::reference
		detail::range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>::operator [] (difference_type n) const
	{
		const auto& i = *static_cast<const Iterator*>(this);
		auto p = i.p;
		i.range->advance_pos(p, n);
		return i.range->at_pos(p);
	}

	template <class Iterator, class Range, class Category>
	inline Iterator detail::operator + (const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& a,
										typename range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>::difference_type n)
	{
		auto i = static_cast<const Iterator&>(a);
		return i += n;
	}

	template <class Iterator, class Range, class Category>
	inline Iterator detail::operator + (typename range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>::difference_type n,
										const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& a)
	{
		return a + i;
	}

	template <class Iterator, class Range, class Category>
	inline typename detail::range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>::difference_type
		detail::operator - (const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& a,
		const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& b)
	{
		const auto& ai = static_cast<const Iterator&>(a);
		const auto& bi = static_cast<const Iterator&>(b);
		return ai.range->distance_pos(bi.pos(), ai.pos());
	}

	template <class Iterator, class Range, class Category>
	inline Iterator detail::operator - (const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& a,
										typename range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>::difference_type n)
	{
		auto i = static_cast<const Iterator&>(a);
		return i -= n;
	}

	template <class Iterator, class Range, class Category>
	inline bool detail::operator < (const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& a,
									const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& b)
	{
		const auto& ai = static_cast<Iterator>(a);
		const auto& bi = static_cast<Iterator>(b);
		return ai.pos() < bi.pos();
	}

	template <class Iterator, class Range, class Category>
	inline bool detail::operator > (const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& a,
									const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& b)
	{
		return b < a;
	}

	template <class Iterator, class Range, class Category>
	inline bool detail::operator <= (const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& a,
									 const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& b)
	{
		return !(b < a);
	}

	template <class Iterator, class Range, class Category>
	inline bool detail::operator >= (const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& a,
									 const range_iterator_base<Iterator, Range, Category, std::random_access_iterator_tag>& b)
	{
		return !(a < b);
	}

	template <class Range>
	range_iterator<Range>::range_iterator() : r(), p()
	{
	}

	template <class Range>
	range_iterator<Range>::range_iterator(const range_type& range) : range(&range), p()
	{
	}

	template <class Range>
	range_iterator<Range>::range_iterator(const range_type& range, position_type p) : range(&range), p(p)
	{
	}

	template <class Range>
	typename range_iterator<Range>::position_type range_iterator<Range>::pos() const
	{
		return p;
	}

	// range_iterator<iterator_range<T>>
	template <class Iterator, class Category>
	typename detail::iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>::reference
		detail::iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>::operator * () const
	{
		const auto& i = *static_cast<const Iterator*>(this);
		return *i.p;
	}

	template <class Iterator, class Category>
	typename detail::iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>::pointer
		detail::iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>::operator -> () const
	{
		const auto& i = *static_cast<const Iterator*>(this);
		return &*i.p;
	}

	template <class Iterator, class Category>
	Iterator& detail::iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>::operator ++ ()
	{
		auto& i = *static_cast<Iterator*>(this);
		++i.p;
		return i;
	}

	template <class Iterator, class Category>
	Iterator detail::iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>::operator ++ (int)
	{
		auto& i = *static_cast<Iterator*>(this);
		auto r = i;
		++i.p;
		return r;
	}

	template <class Iterator, class Category>
	inline bool detail::operator == (const iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>& a,
									 const iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>& b)
	{
		const auto& ai = static_cast<const Iterator&>(a);
		const auto& bi = static_cast<const Iterator&>(b);
		return ai.p == bi.p;
	}

	template <class Iterator, class Category>
	inline bool detail::operator != (const iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>& a,
									 const iterator_range_iterator_base<Iterator, Category, std::input_iterator_tag>& b)
	{
		return !(a == b);
	}

	template <class Iterator, class Category>
	Iterator& detail::iterator_range_iterator_base<Iterator, Category, std::bidirectional_iterator_tag>::operator -- ()
	{
		auto& i = *static_cast<Iterator*>(this);
		--i.p;
		return i;
	}

	template <class Iterator, class Category>
	Iterator detail::iterator_range_iterator_base<Iterator, Category, std::bidirectional_iterator_tag>::operator -- (int)
	{
		auto& i = *static_cast<Iterator*>(this);
		auto r = i;
		--i.p;
		return r;
	}

	template <class Iterator, class Category>
	Iterator& detail::iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>::operator += (difference_type n)
	{
		auto& i = *static_cast<Iterator*>(this);
		i.p += n;
		return i;
	}

	template <class Iterator, class Category>
	Iterator& detail::iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>::operator -= (difference_type n)
	{
		auto& i = *static_cast<Iterator*>(this);
		i.p -= n;
		return i;
	}

	template <class Iterator, class Category>
	typename detail::iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>::reference
		detail::iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>::operator [] (difference_type n) const
	{
		const auto& i = *static_cast<const Iterator*>(this);
		return i.p[n];
	}

	template <class Iterator, class Category>
	inline Iterator detail::operator + (const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& a,
										typename iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>::difference_type n)
	{
		auto i = static_cast<const Iterator&>(a);
		return i += n;
	}

	template <class Iterator, class Category>
	inline Iterator detail::operator + (typename iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>::difference_type n,
										const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& a)
	{
		return a + i;
	}

	template <class Iterator, class Category>
	inline typename detail::iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>::difference_type
		detail::operator - (const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& a,
		const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& b)
	{
		const auto& ai = static_cast<const Iterator&>(a);
		const auto& bi = static_cast<const Iterator&>(b);
		bi.pos() - ai.pos();
	}

	template <class Iterator, class Category>
	inline Iterator detail::operator - (const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& a,
										typename iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>::difference_type n)
	{
		auto i = static_cast<const Iterator&>(a);
		return i -= n;
	}

	template <class Iterator, class Category>
	inline bool detail::operator < (const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& a,
									const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& b)
	{
		const auto& ai = static_cast<Iterator>(a);
		const auto& bi = static_cast<Iterator>(b);
		return ai.pos() < bi.pos();
	}

	template <class Iterator, class Category>
	inline bool detail::operator > (const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& a,
									const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& b)
	{
		return b < a;
	}

	template <class Iterator, class Category>
	inline bool detail::operator <= (const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& a,
									 const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& b)
	{
		return !(b < a);
	}

	template <class Iterator, class Category>
	inline bool detail::operator >= (const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& a,
									 const iterator_range_iterator_base<Iterator, Category, std::random_access_iterator_tag>& b)
	{
		return !(a < b);
	}

	template <class Iterator>
	range_iterator<iterator_range<Iterator>>::range_iterator() : p()
	{
	}

	template <class Iterator>
	range_iterator<iterator_range<Iterator>>::range_iterator(const range_type& range) : p()
	{
	}

	template <class Iterator>
	range_iterator<iterator_range<Iterator>>::range_iterator(const range_type& range, position_type p) : p(p)
	{
	}

	template <class Iterator>
	typename range_iterator<iterator_range<Iterator>>::position_type range_iterator<iterator_range<Iterator>>::pos() const
	{
		return p;
	}
} } // stdext::range