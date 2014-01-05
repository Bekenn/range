#ifndef STDEXT_RANGE_INCLUDED
#define STDEXT_RANGE_INCLUDED
#pragma once

// Ranges are an abstraction over a pair of positions in an underlying sequence.  Ranges allow
// for iteration over the elements of the sequence from the first position to the second position.
// Ranges do not contain the iterated elements, but merely refer to them via the positions at the
// beginning and end of the referred-to sequence.
//
// Positions are similar to (but weaker than) iterators, as understood by the C++ standard library.
// Like iterators, positions can be used (in conjunction with a sequence) to reference a particular
// element in a sequence.  Unlike iterators, positions do not generally reference an element absent
// some form of reference to the sequence as a whole.  In operational terms, here are some key
// differences between positions and iterators:
//
// Positions                             Iterators
// -----------------                     -----------------
// Cannot be directly dereferenced       Can be directly dereferenced (*i)
// Cannot be directly incremented        Can be directly incremented (++i)
// Can be compared for equality only     Can always be compared for equality (i == j, i != j)
//  in the context of a given sequence

// Positions are DefaultConstructible, CopyConstructible, MoveConstructible, and EqualityComparable.
// These additional constraints are placed on position operations:
// p == q:
//    If p and q are positions referencing elements of the same sequence, then p == q iff p and q
//    reference the same element.  If p and q are positions referencing elements of different
//    sequences, then p == q has noinherent meaning.
// p != q:
//    !(p == q)

// A position only has meaning when it is associated with a particular sequence.  A range contains
// two positions, first_pos and last_pos, and associates them with an underlying sequence.  Ranges
// allow for many more operations involving positions.  Each range must support the following
// operations:
// R::position_type:
//    The type of p.
// r.begin_pos():
//    Returns first_pos.
// r.end_pos():
//    Returns last_pos.
// r.begin_pos(p):
//    first_pos = p
// r.at_pos(p):
//    Returns a reference to the sequence element identified by p.
// r.increment_pos(p):
//    post: p refers to the next element in the underlying sequence.

// Optionally, ranges may support the following operations:
// r.end_pos(p):
//    last_pos = p
// r.decrement_pos(p):
//    post: p refers to the previous element in the underlying sequence.
// r.advance_pos(p, n):
//    post: p > 0: p refers to the element n positions later in the sequence.
//          p == 0: p is unchanged
//          p < 0: p refers to the element -n positions earlier in the sequence. (optional)
// r.distance_pos(p, q):
//    requires: p can be transformed into q by repeated invocations of r.increment_pos(p).
//    Returns the number of such invocations required to transform p into q.
//    Optionally, if p can be transformed into q by repeated invocations of r.decrement_pos(p),
//    returns the signed complement of the number of such invocations required to transform p into q.
//    If p cannot be transformed into q as described above, the result is unspecified.

// For each range operation, if p is or could become an invalid position for the underlying sequence,
// the behavior of the operation is undefined.  Note that the bounds of the sequence are not defined
// by the range, which may refer only to a subsequence.  Thus, it is possible to increase the size of
// a range by calling begin_pos(p) or end_pos(p) with a position that lies outside the range denoted
// by [first_pos, last_pos) as long as p still refers to an element in the underlying sequence (or,
// in the case of end_pos(p), one element beyond the last element in the underlying sequence).

#include <iterator>
#include <utility>

#ifdef _MSC_VER
#if _MSC_FULL_VER < 180021114
#define noexcept throw()
#endif
#endif

#define Range_DeclareHasMember(name) \
namespace has_ ## name ## _detail { \
	template <typename T> char has_ ## name ## _helper(...); \
	template <typename T> char(&has_ ## name ## _helper(decltype(T::name) T::*))[2]; \
} \
	template <typename T> \
struct has_ ## name : std::conditional<sizeof(has_ ## name ## _detail::has_ ## name ## _helper<T>(nullptr)) - 1, std::true_type, std::false_type>::type{}

#define Range_DeclareHasMethod(name) \
namespace has_ ## name ## _detail { \
	template <typename T, typename... Args> char has_ ## name ## _helper(...); \
	template <typename T, typename... Args> char(&has_ ## name ## _helper(decltype(std::declval<T>().name(std::declval<Args>()...))*))[2]; \
} \
	template <typename T, typename... Args> \
struct has_ ## name : std::conditional<sizeof(has_ ## name ## _detail::has_ ## name ## _helper<T, Args...>(nullptr)) - 1, std::true_type, std::false_type>::type{}

namespace stdext
{
	// type traits
	template <class Range>
	struct range_traits;
	// basic range
	template <class Category, class T, class Position, class Distance = std::ptrdiff_t, class Reference = T&>
	struct range;

	// range categories
	struct output_range_tag;
	struct input_range_tag;
	struct forward_range_tag;
	struct bidirectional_range_tag;
	struct random_access_range_tag;

	template <typename T> struct is_range;
	template <typename T> struct is_forward_range;
	template <typename T> struct is_bidirectional_range;
	template <typename T> struct is_random_access_range;

	template <typename R, typename V> struct is_output_range;
	template <typename R, typename V> struct is_input_range;

	// Range classes
	template <class Iterator>
	class iterator_range;

	// Range iterators
	template <class Range>
	class range_iterator;

	namespace detail
	{
		Range_DeclareHasMethod(begin);
		Range_DeclareHasMethod(end);
	}

	// Operations on ranges
	template <class Range>
	bool empty(const Range& r);
	template <class Range>
	range_iterator<Range> begin(const Range& r);
	template <class Range>
	range_iterator<Range> end(const Range& r);
	template <class Range>
	typename range_traits<Range>::reference front(const Range& r);
	template <class BidirectionalRange>
	typename range_traits<BidirectionalRange>::reference back(const BidirectionalRange& r);
	template <class Range>
	void drop_first(Range& r, typename range_traits<Range>::difference_type n = 1);
	template <class Range>
	void drop_last(Range& r, typename range_traits<Range>::difference_type n = 1);
	template <class Range>
	typename range_traits<Range>::position_type& advance_pos(const Range& r,
															 typename range_traits<Range>::position_type& p,
															 typename range_traits<Range>::difference_type n);
	template <class ForwardRange>
	typename range_traits<ForwardRange>::difference_type length(const ForwardRange& r);


	// make_range
	namespace detail
	{
		using std::begin;

		template <class C>
		struct iterator_type
		{
			typedef decltype(begin(std::declval<C&>())) type;
		};

		Range_DeclareHasMethod(begin_pos);
		Range_DeclareHasMethod(end_pos);
		Range_DeclareHasMethod(at_pos);
		Range_DeclareHasMethod(increment_pos);
		Range_DeclareHasMethod(distance_pos);
		Range_DeclareHasMethod(decrement_pos);
		Range_DeclareHasMethod(advance_pos);
	}
	template <class Iterator>
	iterator_range<Iterator> make_range(Iterator first, Iterator last);
	template <class C>
	iterator_range<typename detail::iterator_type<C>::type> make_range(C& c);
	template <class C>
	iterator_range<typename detail::iterator_type<const C>::type> make_range(const C& c);

	template <class Range>
	Range range_before(Range range, typename range_traits<Range>::position_type p);
	template <class Range>
	Range range_after(Range range, typename range_traits<Range>::position_type p);
	template <class Range>
	Range subrange(Range range, typename range_traits<Range>::position_type first, typename range_traits<Range>::position_type last);


	// range traits
	template <class Range>
	struct range_traits
	{
		typedef typename Range::difference_type difference_type;
		typedef typename Range::value_type      value_type;
		typedef typename Range::position_type   position_type;
		typedef typename Range::reference       reference;
		typedef typename Range::range_category  range_category;
	};

	// basic range typedefs, for easier range definitions
	template <class Category, class T, class Position, class Distance, class Reference>
	struct range
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Position  position_type;
		typedef Reference reference;
		typedef Category  range_category;
	};

	// range categories
	struct output_range_tag { };
	struct input_range_tag { };
	struct forward_range_tag : input_range_tag { };
	struct bidirectional_range_tag : forward_range_tag { };
	struct random_access_range_tag : bidirectional_range_tag { };

	template <typename T>
	struct is_range : std::conditional<
		detail::has_begin_pos<T>::value
		&& detail::has_begin_pos<T, typename range_traits<T>::position_type>::value
		&& detail::has_end_pos<T>::value
		&& detail::has_at_pos<T, typename range_traits<T>::position_type>::value
		&& detail::has_increment_pos<T, typename range_traits<T>::position_type&>::value
		, std::true_type, std::false_type>::type
	{
	};

	template <typename R, typename V>
	struct is_output_range : std::conditional<
		is_range<R>::value
		&& std::is_assignable<decltype(std::declval<R>().at_pos(std::declval<typename range_traits<R>::position_type>())), V>::value
		, std::true_type, std::false_type>::type
	{
	};

	template <typename R, typename V>
	struct is_input_range : std::conditional<
		is_range<R>::value
		&& std::is_assignable<V, decltype(std::declval<R>().at_pos(std::declval<typename range_traits<R>::position_type>()))>::value
		, std::true_type, std::false_type>::type
	{
	};

	template <typename T>
	struct is_forward_range : std::conditional<
		is_range<T>::value
		&& detail::has_end_pos<T, typename range_traits<T>::position_type>::value
		&& detail::has_distance_pos<T, typename range_traits<T>::position_type, typename range_traits<T>::position_type>::value
		, std::true_type, std::false_type>::type
	{
	};

	template <typename T>
	struct is_bidirectional_range : std::conditional<
		is_forward_range<T>::value
		&& detail::has_decrement_pos<T, typename range_traits<T>::position_type&>::value
		, std::true_type, std::false_type>::type
	{
	};

	template <typename T>
	struct is_random_access_range : std::conditional<
		is_bidirectional_range<T>::value
		&& detail::has_advance_pos<T, typename range_traits<T>::position_type&, typename range_traits<T>::difference_type>::value
		, std::true_type, std::false_type>::type
	{
	};

	namespace detail
	{
		output_range_tag        to_range_category(std::output_iterator_tag);
		input_range_tag         to_range_category(std::input_iterator_tag);
		forward_range_tag       to_range_category(std::forward_iterator_tag);
		bidirectional_range_tag to_range_category(std::bidirectional_iterator_tag);
		random_access_range_tag to_range_category(std::random_access_iterator_tag);
		
		template <class Range, class Iterator, class Category = decltype(to_range_category(std::declval<typename std::iterator_traits<Iterator>::iterator_category>())), class = Category>
		struct iterator_range_base;

		template <class Range, class Iterator, class Category>
		struct iterator_range_base<Range, Iterator, Category, input_range_tag>
			: range<Category, typename std::iterator_traits<Iterator>::value_type, Iterator, typename std::iterator_traits<Iterator>::difference_type, typename std::iterator_traits<Iterator>::reference>
		{
			// Clang needs these, but Visual Studio is fine without them.
			typedef typename range_traits<iterator_range_base>::position_type position_type;
			typedef typename range_traits<iterator_range_base>::reference reference;

			// range requirements
			position_type  begin_pos() const noexcept            { return self().first; }
			void           begin_pos(position_type p) noexcept   { self().first = std::move(p); }
			position_type  end_pos() const noexcept              { return self().last; }
			reference      at_pos(const position_type& p) const  { return *p; }
			position_type& increment_pos(position_type& p) const { return ++p; }

			// not contractual
		protected:
			Range& self() noexcept             { return static_cast<Range&>(*this); }
			const Range& self() const noexcept { return static_cast<const Range&>(*this); }
		};

		template <class Range, class Iterator, class Category>
		struct iterator_range_base<Range, Iterator, Category, forward_range_tag>
			: iterator_range_base<Range, Iterator, Category, input_range_tag>
		{
			typedef typename range_traits<iterator_range_base>::position_type position_type;
			typedef typename range_traits<iterator_range_base>::difference_type difference_type;

			using iterator_range_base<Range, Iterator, Category, input_range_tag>::end_pos;
			void            end_pos(position_type p) noexcept{ this->self().last() = std::move(p); }
			difference_type distance_pos(position_type p1, position_type p2) const noexcept{ return std::distance(p1, p2); }
		};

		template <class Range, class Iterator, class Category>
		struct iterator_range_base<Range, Iterator, Category, bidirectional_range_tag>
			: iterator_range_base<Range, Iterator, Category, forward_range_tag>
		{
			typedef typename range_traits<iterator_range_base>::position_type position_type;
			position_type& decrement_pos(position_type& p) const { return --p; }
		};

		template <class Range, class Iterator, class Category>
		struct iterator_range_base<Range, Iterator, Category, random_access_range_tag>
			: iterator_range_base<Range, Iterator, Category, bidirectional_range_tag>
		{
			typedef typename range_traits<iterator_range_base>::position_type position_type;
			typedef typename range_traits<iterator_range_base>::difference_type difference_type;
			position_type& advance_pos(position_type& p, difference_type n) const { std::advance(p, n); return p; }
		};
	}

	template <class Iterator>
	class iterator_range : public detail::iterator_range_base<iterator_range<Iterator>, Iterator>
	{
	public:
		iterator_range() = default;
		iterator_range(Iterator first, Iterator last) : first(first), last(last) { }

	public:
		// iterator access
		Iterator begin() const noexcept { return first; }
		Iterator end() const noexcept { return last; }

	private:
		typedef decltype(detail::to_range_category(std::declval<typename std::iterator_traits<Iterator>::iterator_category>())) category;
		friend struct detail::iterator_range_base<iterator_range<Iterator>, Iterator, category, random_access_range_tag>;
		friend struct detail::iterator_range_base<iterator_range<Iterator>, Iterator, category, bidirectional_range_tag>;
		friend struct detail::iterator_range_base<iterator_range<Iterator>, Iterator, category, forward_range_tag>;
		friend struct detail::iterator_range_base<iterator_range<Iterator>, Iterator, category, input_range_tag>;
		Iterator first, last;
	};

	namespace detail
	{
		std::output_iterator_tag        to_iterator_category(output_range_tag);
		std::input_iterator_tag         to_iterator_category(input_range_tag);
		std::forward_iterator_tag       to_iterator_category(forward_range_tag);
		std::bidirectional_iterator_tag to_iterator_category(bidirectional_range_tag);
		std::random_access_iterator_tag to_iterator_category(random_access_range_tag);

		template <class Iterator, class Range, class IteratorCategory = decltype(to_iterator_category(std::declval<typename range_traits<Range>::range_category>())), class = IteratorCategory>
		struct range_iterator_base;

		template <class Iterator, class Range, class IteratorCategory>
		struct range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>
			: std::iterator<
			IteratorCategory,
			typename range_traits<Range>::value_type,
			typename range_traits<Range>::difference_type,
			typename std::remove_reference<typename range_traits<Range>::reference>::type*,
			typename range_traits<Range>::reference>
		{
			typedef typename std::iterator_traits<range_iterator_base>::reference reference;
			typedef typename std::iterator_traits<range_iterator_base>::pointer pointer;

			reference operator * () const { return self().range->at_pos(self().p); }
			pointer operator -> () const  { return &*this; }
			Iterator& operator ++ ()      { self().range->increment_pos(self().p); return self(); }
			Iterator operator ++ (int)    { auto r = self(); ++*this; return r; }

			// not contractual
		protected:
			Iterator& self() noexcept             { return static_cast<Iterator&>(*this); }
			const Iterator& self() const noexcept { return static_cast<const Iterator&>(*this); }
		};

		template <class Iterator, class Range, class IteratorCategory>
		bool operator == (const range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>& a,
						  const range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>& b)
		{
			const auto& ai = static_cast<const Iterator&>(a);
			const auto& bi = static_cast<const Iterator&>(b);
			return ai.range == bi.range
				&& ai.p == bi.p;
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator != (const range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>& a,
						  const range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>& b)
		{
			return !(a == b);
		}

		template <class Iterator, class Range, class IteratorCategory>
		struct range_iterator_base<Iterator, Range, IteratorCategory, std::forward_iterator_tag>
			: range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>
		{
		};

		template <class Iterator, class Range, class IteratorCategory>
		struct range_iterator_base<Iterator, Range, IteratorCategory, std::bidirectional_iterator_tag>
			: range_iterator_base<Iterator, Range, IteratorCategory, std::forward_iterator_tag>
		{
			Iterator& operator -- ()   { this->self().range->decrement_pos(this->self().p); return this->self(); }
			Iterator operator -- (int) { auto r = this->self(); --*this; return r; }
		};

		template <class Iterator, class Range, class IteratorCategory>
		struct range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>
			: range_iterator_base<Iterator, Range, IteratorCategory, std::bidirectional_iterator_tag>
		{
			typedef typename std::iterator_traits<range_iterator_base>::difference_type difference_type;
			typedef typename std::iterator_traits<range_iterator_base>::reference reference;

			Iterator& operator += (difference_type n)       { this->self().range->advance_pos(this->self().p, n); return this->self(); }
			Iterator& operator -= (difference_type n)       { this->self().range->advance_pos(this->self().p, -n); return this->self(); }
			reference operator [] (difference_type n) const { auto p = this->self().p; this->self().range->advance_pos(p, n); return this->self().range->at_pos(p); }
		};

		template <class Iterator, class Range, class IteratorCategory>
		Iterator operator + (const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
							 typename range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>::difference_type n)
		{
			auto i = static_cast<const Iterator&>(a);
			return i += n;
		}

		template <class Iterator, class Range, class IteratorCategory>
		Iterator operator + (typename range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>::difference_type n,
							 const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a)
		{
			return a + n;
		}

		template <class Iterator, class Range, class IteratorCategory>
		typename range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>::difference_type
			operator - (const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
			            const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			const auto& ai = static_cast<const Iterator&>(a);
			const auto& bi = static_cast<const Iterator&>(b);
			return ai.range->distance_pos(bi.pos(), ai.pos());
		}

		template <class Iterator, class Range, class IteratorCategory>
		Iterator operator - (const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
							 typename range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>::difference_type n)
		{
			auto i = static_cast<const Iterator&>(a);
			return i -= n;
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator < (const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
						 const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			const auto& ai = static_cast<Iterator>(a);
			const auto& bi = static_cast<Iterator>(b);
			return ai.pos() < bi.pos();
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator > (const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
						 const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			return b < a;
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator <= (const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
						  const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			return !(b < a);
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator >= (const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
						  const range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			return !(a < b);
		}
	}

	template <class Range>
	class range_iterator
		: public detail::range_iterator_base<range_iterator<Range>, Range>
	{
	public:
		typedef Range range_type;
		typedef typename range_traits<Range>::position_type position_type;
		typedef decltype(detail::to_iterator_category(std::declval<typename range_traits<Range>::range_category>())) iterator_category;

	public:
		range_iterator() : range(), p() { }
		range_iterator(const range_type& range) : range(&range), p() { }
		range_iterator(const range_type& range, position_type p) : range(&range), p(p) { }

	public:
		//const Range& range() const; // specifically not provided to keep the interface the same as for range_iterator<iterator_range<I>>.
		position_type pos() const { return p; }

	private:
		friend bool detail::operator == <range_iterator, Range, iterator_category>
		(const detail::range_iterator_base<range_iterator, Range, iterator_category, std::input_iterator_tag>& a,
		 const detail::range_iterator_base<range_iterator, Range, iterator_category, std::input_iterator_tag>& b);
		friend bool detail::operator < <range_iterator, Range, iterator_category>
		(const detail::range_iterator_base<range_iterator, Range, iterator_category, std::random_access_iterator_tag>& a,
		 const detail::range_iterator_base<range_iterator, Range, iterator_category, std::random_access_iterator_tag>& b);
		friend struct detail::range_iterator_base<range_iterator, Range, iterator_category, std::input_iterator_tag>;
		const range_type* range;
		position_type p;
	};

	namespace detail
	{
		template <class Iterator, class Range, class IteratorCategory = decltype(to_iterator_category(std::declval<typename range_traits<Range>::range_category>())), class = IteratorCategory>
		struct iterator_range_iterator_base;

		template <class Iterator, class Range, class IteratorCategory>
		struct iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>
			: std::iterator<
			IteratorCategory,
			typename range_traits<Range>::value_type,
			typename range_traits<Range>::difference_type,
			typename range_traits<Range>::reference>
		{
			typedef typename std::iterator_traits<iterator_range_iterator_base>::reference reference;
			typedef typename std::iterator_traits<iterator_range_iterator_base>::pointer pointer;

			reference operator * () const { return *self().p; }
			pointer operator -> () const  { return &*this; }
			Iterator& operator ++ ()      { ++self().p; return self; }
			Iterator operator ++ (int)    { auto r = self(); ++*this; return r; }

			// not contractual
		protected:
			Iterator& self() noexcept             { return static_cast<Iterator&>(*this); }
			const Iterator& self() const noexcept { return static_cast<const Iterator&>(*this); }
		};

		template <class Iterator, class Range, class IteratorCategory>
		bool operator == (const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>& a,
						  const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>& b)
		{
			const auto& ai = static_cast<const Iterator&>(a);
			const auto& bi = static_cast<const Iterator&>(b);
			return ai.p == bi.p;
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator != (const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>& a,
						  const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>& b)
		{
			return !(a == b);
		}

		template <class Iterator, class Range, class IteratorCategory>
		struct iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::forward_iterator_tag>
			: iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::input_iterator_tag>
		{
		};

		template <class Iterator, class Range, class IteratorCategory>
		struct iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::bidirectional_iterator_tag>
			: iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::forward_iterator_tag>
		{
			Iterator& operator -- ()   { --this->self().p; return this->self(); }
			Iterator operator -- (int) { auto r = this->self(); --*this; return r; }
		};

		template <class Iterator, class Range, class IteratorCategory>
		struct iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>
			: iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::bidirectional_iterator_tag>
		{
			typedef typename std::iterator_traits<iterator_range_iterator_base>::difference_type difference_type;
			typedef typename std::iterator_traits<iterator_range_iterator_base>::reference reference;

			Iterator& operator += (difference_type n)       { this->self().p += n; return this->self(); }
			Iterator& operator -= (difference_type n)       { this->self().p -= n; return this->self(); }
			reference operator [] (difference_type n) const { return this->self().p[n]; }
		};

		template <class Iterator, class Range, class IteratorCategory>
		Iterator operator + (const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
							 typename iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>::difference_type n)
		{
			auto i = static_cast<const Iterator&>(a);
			return i += n;
		}

		template <class Iterator, class Range, class IteratorCategory>
		Iterator operator + (typename iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>::difference_type n,
							 const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a)
		{
			return a + n;
		}

		template <class Iterator, class Range, class IteratorCategory>
		typename iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>::difference_type
			operator - (const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
			const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			const auto& ai = static_cast<const Iterator&>(a);
			const auto& bi = static_cast<const Iterator&>(b);
			bi.pos() - ai.pos();
		}

		template <class Iterator, class Range, class IteratorCategory>
		Iterator operator - (const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
							 typename iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>::difference_type n)
		{
			auto i = static_cast<const Iterator&>(a);
			return i -= n;
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator < (const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
						 const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			const auto& ai = static_cast<Iterator>(a);
			const auto& bi = static_cast<Iterator>(b);
			return ai.pos() < bi.pos();
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator > (const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
						 const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			return b < a;
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator <= (const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
						  const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			return !(b < a);
		}

		template <class Iterator, class Range, class IteratorCategory>
		bool operator >= (const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& a,
						  const iterator_range_iterator_base<Iterator, Range, IteratorCategory, std::random_access_iterator_tag>& b)
		{
			return !(a < b);
		}
	}

	template <class Iterator>
	class range_iterator<iterator_range<Iterator>>
		: detail::iterator_range_iterator_base<range_iterator<iterator_range<Iterator>>, iterator_range<Iterator>>
	{
	public:
		typedef iterator_range<Iterator> range_type;
		typedef Iterator position_type;

	public:
		range_iterator() : p() { }
		range_iterator(const range_type&) : p() { }
		range_iterator(const range_type&, position_type p) : p(p) { }

	public:
		position_type pos() const { return p; }

	private:
		position_type p;
	};
} // namespace stdext

#include "range.inl"

#endif