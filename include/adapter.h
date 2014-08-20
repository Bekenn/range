#ifndef STDEXT_ADAPTER_INCLUDED
#define STDEXT_ADAPTER_INCLUDED
#pragma once

#include <range.h>
#include <functional>
#include <tuple>
#include <cstddef>

namespace stdext
{
	template <class Range1, class Range2> class concatenated_range;
	template <class Range, class Predicate> class filtered_range;
	template <class Range, class Operation> class transformed_range;
	template <class Range, class Predicate> class unique_range;
	template <class Range> class reversed_range;
	template <class Range> class rotated_range;
	template <class Range, class Predicate> class partitioned_range;

	namespace detail
	{
		template <class Range> struct range_prepend_t;
		template <class Range> struct range_append_t;
		struct range_trim_front_t;
		struct range_trim_back_t;
		struct range_subrange_t;
		template <class T> struct range_remove_t;
		template <class Predicate> struct range_remove_if_t;
		template <class T> struct range_select_t;
		template <class Predicate> struct range_select_if_t;
		template <class Operation> struct range_transform_t;
		template <class T> struct range_replace_t;
		template <class Predicate, class T> struct range_replace_if_t;
		struct range_unique_t;
		template <class Predicate> struct range_unique_if_t;
		struct range_reverse_t;
		struct range_rotate_t;
		template <class T> struct range_partition_t;
		template <class Predicate> struct range_partition_if_t;
	}

	template <class Range>     detail::range_prepend_t<Range>       prepend(Range&& r);
	template <class Range>     detail::range_append_t<Range>        append(Range&& r);
	                           detail::range_trim_front_t           trim_front(::std::size_t n);
							   detail::range_trim_back_t            trim_back(::std::size_t n);
							   detail::range_subrange_t             subrange(::std::size_t n1, ::std::size_t n2);
	template <class T>         detail::range_remove_t<T>            remove(T&& value);
	template <class Predicate> detail::range_remove_if_t<Predicate> remove_if(Predicate&& pred);
	template <class T>         detail::range_select_t<T>            select(T&& value);
	template <class Predicate> detail::range_select_if_t<Predicate> select_if(Predicate&& pred);
	template <class Operation> detail::range_transform_t<Operation> transform(Operation&& op);
	template <class T>         detail::range_replace_t<T>           replace(T&& old_value, T&& new_value);
	template <class Predicate, class T> detail::range_replace_if_t<Predicate, T> replace_if(Predicate&& pred, T&& new_value);
	                           detail::range_unique_t               unique();
	template <class Predicate> detail::range_unique_if_t<Predicate> unique_if(Predicate&& pred);
	                           detail::range_reverse_t              reverse();
	                           detail::range_rotate_t               rotate(::std::ptrdiff_t n);
	template <class T>         detail::range_partition_t<T>         partition(T&& value);
	template <class Predicate> detail::range_partition_if_t<Predicate> partition_if(Predicate&& pred);

	namespace detail
	{
		template <class Range> struct range_prepend_t { Range r; };
		template <class Range> struct range_append_t { Range r; };
		struct range_trim_front_t { ::std::size_t n; };
		struct range_trim_back_t { ::std::size_t n; };
		struct range_subrange_t { ::std::size_t n1, n2; };

		template <class T> struct range_remove_t { T v; };
		template <class T> struct range_remove_op
		{
			bool operator () (const T& value) const { return value != remove; }
			T remove;
		};

		template <class Predicate> struct range_remove_if_t { Predicate p; };
		template <class Predicate, class T> struct range_remove_if_op
		{
			bool operator () (const T& value) const { return !p(value); }
			Predicate p;
		};

		template <class T> struct range_select_t { T v; };
		template <class T> struct range_select_op
		{
			bool operator () (const T& value) const { return value == select; }
			T select;
		};

		template <class Predicate> struct range_select_if_t { Predicate p; };
		template <class Operation> struct range_transform_t { Operation op; };

		template <class T> struct range_replace_t { T old_value, new_value; };
		template <class T> struct range_replace_op
		{
			range_replace_op(const range_replace_t<T>& replace) : replace(replace) { }
			range_replace_op(range_replace_t<T>&& replace) : replace(::std::move(replace)) { }
			T operator () (const T& value) const { return value == replace.old_value ? replace.new_value : value; }
			range_replace_t<T> replace;
		};

		template <class Predicate, class T> struct range_replace_if_t { Predicate pred; T new_value; };
		template <class Predicate, class T> struct range_replace_if_op
		{
			range_replace_if_op(const range_replace_if_t<Predicate, T>& replace) : replace(replace) { }
			range_replace_if_op(range_replace_if_t<Predicate, T>&& replace) : replace(::std::move(replace)) { }
			T operator () (const T& value) const { return replace.pred(value) ? replace.new_value : value; }
			range_replace_if_t<Predicate, T> replace;
		};

		struct range_unique_t { };
		template <class Predicate> struct range_unique_if_t { Predicate pred; };
		struct range_reverse_t { };
		struct range_rotate_t { ::std::ptrdiff_t n; };

		template <class T> struct range_partition_t { T value; };
		template <class T> struct range_partition_op
		{
			range_partition_op(const typename ::std::remove_reference<T>::type& partition) : partition(partition) { }
			range_partition_op(typename ::std::remove_reference<T>::type&& partition) : partition(::std::move(partition)) { }
			bool operator () (const T& value) const { return value == partition; }
			T partition;
		};

		template <class Predicate> struct range_partition_if_t { Predicate pred; };
	}

	template <class Range1, class Range2>
	concatenated_range<Range2, Range1> operator >> (Range1&& range1, detail::range_prepend_t<Range2>&& prepend);
	template <class Range1, class Range2>
	concatenated_range<Range1, Range2> operator >> (Range1&& range1, detail::range_append_t<Range2>&& append);
	template <class Range>
	Range operator >> (Range&& range, const detail::range_trim_front_t& trim_front);
	template <class Range>
	Range operator >> (Range&& range, const detail::range_trim_back_t& trim_back);
	template <class Range>
	Range operator >> (Range&& range, const detail::range_subrange_t& subrange);
	template <class Range, class T>
	filtered_range<Range, detail::range_remove_op<T>> operator >> (Range&& range, detail::range_remove_t<T>&& remove);
	template <class Range, class Predicate>
	filtered_range<Range, detail::range_remove_if_op<Predicate, typename range_traits<Range>::value_type>>
		operator >> (Range&& range, detail::range_remove_if_t<Predicate>&& remove);
	template <class Range, class T>
	filtered_range<Range, detail::range_select_op<T>> operator >> (Range&& range, detail::range_select_t<T>&& select);
	template <class Range, class Predicate>
	filtered_range<Range, Predicate> operator >> (Range&& range, detail::range_select_if_t<Predicate>&& select);
	template <class Range, class Operation>
	transformed_range<Range, Operation> operator >> (Range&& range, detail::range_transform_t<Operation>&& transform);
	template <class Range, class T>
	transformed_range<Range, detail::range_replace_op<T>> operator >> (Range&& range, detail::range_replace_t<T>&& replace);
	template <class Range, class Predicate, class T>
	transformed_range<Range, detail::range_replace_if_op<Predicate, T>> operator >> (Range&& range, detail::range_replace_if_t<Predicate, T>&& replace);
	template <class Range>
	unique_range<Range, ::std::equal_to<>> operator >> (Range&& range, const detail::range_unique_t& unique);
	template <class Range, class Predicate>
	unique_range<Range, Predicate> operator >> (Range&& range, detail::range_unique_if_t<Predicate>&& unique);
	template <class Range>
	reversed_range<Range> operator >> (Range&& range, detail::range_reverse_t&& reverse);
	template <class Range>
	rotated_range<Range> operator >> (Range&& range, detail::range_rotate_t&& rotate);
	template <class Range, class T>
	partitioned_range<Range, detail::range_partition_op<T>> operator >> (Range&& range, detail::range_partition_t<T>&& partition);
	template <class Range, class Predicate>
	partitioned_range<Range, Predicate> operator >> (Range&& range, detail::range_partition_if_t<Predicate>&& partition);

	////////////////////////////////////////////////////////////////
	// concatenated_range
	////////////////////////////////////////////////////////////////
	namespace detail
	{
		template <class Range1, class Range2>
		struct common_reference
		{
			typedef
				typename ::std::conditional<!::std::is_reference<typename range_traits<Range1>::reference>::value,
					typename range_traits<Range1>::reference,
					typename ::std::conditional<!::std::is_reference<typename range_traits<Range2>::reference>::value,
						typename range_traits<Range2>::reference,
						typename ::std::conditional<::std::is_const<typename ::std::remove_reference<typename range_traits<Range1>::reference>::type>::value,
							typename range_traits<Range1>::reference,
							typename range_traits<Range2>::reference
						>::type
					>::type
				>::type type;
		};

		template <class Range, class InputRange1, class InputRange2, class Category, class BaseCategory = Category>
		struct concatenated_range_base;

		template <class Range, class InputRange1, class InputRange2, class Category>
		struct concatenated_range_base<Range, InputRange1, InputRange2, Category, input_range_tag>
			: range<Category,
				typename range_traits<InputRange1>::value_type,
				::std::pair<typename range_traits<InputRange1>::position_type, typename range_traits<InputRange2>::position_type>,
				::std::ptrdiff_t,
				typename common_reference<InputRange1, InputRange2>::type>
		{
			typedef typename range_traits<concatenated_range_base>::position_type position_type;
			typedef typename range_traits<concatenated_range_base>::reference reference;

			position_type begin_pos() const noexcept { return self().first; }
			position_type end_pos() const noexcept   { return self().last; }
			void begin_pos(const position_type& pos) { self().first = pos; }

			position_type& increment_pos(position_type& pos)
			{
				if (pos.first != self().range1.end_pos())
					self().range1.increment_pos(pos.first);
				else
					self().range2.increment_pos(pos.second);

				return pos;
			}

			reference at_pos(const position_type& pos)
			{
				if (pos.first != self().range1.end_pos())
					return self().range1.at_pos(pos.first);
				return self().range2.at_pos(pos.second);
			}

		protected:
			Range& self() noexcept { return static_cast<Range&>(*this); }
			const Range& self() const noexcept { return static_cast<const Range&>(*this); }
		};

		template <class Range, class InputRange1, class InputRange2, class Category>
		struct concatenated_range_base<Range, InputRange1, InputRange2, Category, forward_range_tag>
			: concatenated_range_base<Range, InputRange1, InputRange2, Category, input_range_tag>
		{
			typedef typename range_traits<concatenated_range_base>::position_type position_type;
			typedef typename range_traits<concatenated_range_base>::difference_type difference_type;

			using concatenated_range_base<Range, InputRange1, InputRange2, Category, input_range_tag>::end_pos;
			void end_pos(const position_type& pos)   { this->self().last = pos; }
			difference_type distance_pos(position_type p1, position_type p2) const noexcept
			{
				if (p1.first != this->self().range1.end_pos())
				{
					if  (p2.first != this->self().range1.end_pos())
						return this->self().range1.distance_pos(p1.first, p2.first);
					return this->self().range1.distance_pos(p1.first, this->self().range1.end_pos())
						+ this->self().range2.distance_pos(this->self().range2.begin_pos(), p2.second);
				}

				return this->self().range2.distance_pos(p1.second, p2.second);
			}
		};

		template <class Range, class InputRange1, class InputRange2, class Category>
		struct concatenated_range_base<Range, InputRange1, InputRange2, Category, bidirectional_range_tag>
			: concatenated_range_base<Range, InputRange1, InputRange2, Category, forward_range_tag>
		{
			typedef typename range_traits<concatenated_range_base>::position_type position_type;
			position_type& decrement_pos(position_type& pos)
			{
				if (pos.second != this->self().range2.begin_pos())
					this->self().range2.decrement_pos(pos.second);
				else
					this->self().range1.decrement_pos(pos.first);

				return pos;
			}
		};

		template <class Range, class InputRange1, class InputRange2, class Category>
		struct concatenated_range_base<Range, InputRange1, InputRange2, Category, random_access_range_tag>
			: concatenated_range_base<Range, InputRange1, InputRange2, Category, bidirectional_range_tag>
		{
			typedef typename range_traits<concatenated_range_base>::position_type position_type;
			typedef typename range_traits<concatenated_range_base>::difference_type difference_type;
			position_type& advance_pos(position_type& p, difference_type n) const
			{
				if (p.first != this->self().range1.end_pos())
				{
					auto d1 = this->self().range1.distance_pos(p.first, this->self().range1.end_pos());
					if (n < d1)
					{
						this->self().range1.advance_pos(p.first, n);
						return p;
					}

					n -= d1;
					p.first = this->self().range1.end_pos();
				}

				this->self().range2.advance_pos(p.second, n);
				return p;
			}
		};
	}

	template <class InputRange1, class InputRange2>
	class concatenated_range : public detail::concatenated_range_base<
		typename ::std::enable_if<::std::is_same<
			typename range_traits<InputRange1>::value_type,
			typename range_traits<InputRange2>::value_type>::value,
			concatenated_range<InputRange1, InputRange2>>::type,
		InputRange1,
		InputRange2,
		typename ::std::common_type<typename range_traits<InputRange1>::range_category, typename range_traits<InputRange2>::range_category>::type>
	{
	public:
		concatenated_range(InputRange1 range1, InputRange2 range2)
			: range1(::std::move(range1)), range2(::std::move(range2))
			, first(this->range1.begin_pos(), this->range2.begin_pos())
			, last(this->range1.end_pos(), this->range2.end_pos())
		{
		}

	private:
		typedef typename range_traits<concatenated_range>::range_category range_category;
		typedef typename range_traits<concatenated_range>::position_type position_type;
		friend struct detail::concatenated_range_base<concatenated_range, InputRange1, InputRange2, range_category, input_range_tag>;

		InputRange1 range1;
		InputRange2 range2;
		position_type first, last;
	};

	////////////////////////////////////////////////////////////////
	// filtered_range
	////////////////////////////////////////////////////////////////
	namespace detail
	{
		template <class Range, class InputRange, class Predicate, class Category, class BaseCategory = Category>
		struct filtered_range_base;

		template <class Range, class InputRange, class Predicate, class Category>
		struct filtered_range_base<Range, InputRange, Predicate, Category, input_range_tag>
			: range<Category,
				typename range_traits<InputRange>::value_type,
				typename range_traits<InputRange>::position_type,
				typename range_traits<InputRange>::difference_type,
				typename range_traits<InputRange>::reference>
		{
			typedef typename range_traits<filtered_range_base>::position_type position_type;
			typedef typename range_traits<filtered_range_base>::reference reference;

			// range requirements
			position_type  begin_pos() const                     { return self().range.begin_pos(); }
			void           begin_pos(position_type p)            { self().range.begin_pos(::std::move(p)); }
			position_type  end_pos() const                       { return self().range.end_pos(); }
			reference      at_pos(const position_type& p) const  { return self().range.at_pos(p); }
			position_type& increment_pos(position_type& p) const
			{
				do {
					self().range.increment_pos(p);
				} while (p != self().range.end_pos() && !self().pred(self().range.at_pos(p)));
				return p;
			}

		protected:
			Range& self() { return static_cast<Range&>(*this); }
			const Range& self() const { return static_cast<const Range&>(*this); }
		};

		template <class Range, class InputRange, class Predicate, class Category>
		struct filtered_range_base<Range, InputRange, Predicate, Category, forward_range_tag>
			: filtered_range_base<Range, InputRange, Predicate, Category, input_range_tag>
		{
			typedef typename range_traits<filtered_range_base>::position_type position_type;
			typedef typename range_traits<filtered_range_base>::difference_type difference_type;

			using filtered_range_base<Range, InputRange, Predicate, Category, input_range_tag>::end_pos;
			void end_pos(position_type p) { this->self().range.end_pos(::std::move(p)); }
			difference_type distance_pos(position_type p1, position_type p2)
			{
				difference_type d = 0;
				while (p1 != p2)
				{
					increment_pos(p1);
					++d;
				}

				return d;
			}
		};

		template <class Range, class InputRange, class Predicate, class Category>
		struct filtered_range_base<Range, InputRange, Predicate, Category, bidirectional_range_tag>
			: filtered_range_base<Range, InputRange, Predicate, Category, forward_range_tag>
		{
			typedef typename range_traits<filtered_range_base>::position_type position_type;
			position_type& decrement_pos(position_type& pos)
			{
				do {
					this->self().range.decrement_pos(pos);
				} while (pos != this->self().range.begin_pos() && !this->self().pred(this->self().range.at_pos(pos)));
			}
		};
	}

	template <class InputRange, class Predicate>
	class filtered_range : public detail::filtered_range_base<filtered_range<InputRange, Predicate>, InputRange, Predicate, typename ::std::common_type<typename range_traits<InputRange>::range_category, bidirectional_range_tag>::type>
	{
	public:
		filtered_range(InputRange range, Predicate pred) : range(::std::move(range)), pred(::std::move(pred))
		{
			while (!empty(this->range) && !pred(front(this->range)))
				drop_first(this->range);
		}

	private:
		friend struct detail::filtered_range_base<filtered_range<InputRange, Predicate>, InputRange, Predicate, typename ::std::common_type<typename range_traits<InputRange>::range_category, bidirectional_range_tag>::type, input_range_tag>;
		friend struct detail::filtered_range_base<filtered_range<InputRange, Predicate>, InputRange, Predicate, typename ::std::common_type<typename range_traits<InputRange>::range_category, bidirectional_range_tag>::type, forward_range_tag>;
		friend struct detail::filtered_range_base<filtered_range<InputRange, Predicate>, InputRange, Predicate, typename ::std::common_type<typename range_traits<InputRange>::range_category, bidirectional_range_tag>::type, bidirectional_range_tag>;

		InputRange range;
		Predicate pred;
	};

	////////////////////////////////////////////////////////////////
	// filtered_range
	////////////////////////////////////////////////////////////////
	namespace detail
	{
		template <class Range, class InputRange, class Operation, class Category, class BaseCategory = Category>
		struct transformed_range_base;

		template <class Range, class InputRange, class Operation, class Category>
		struct transformed_range_base<Range, InputRange, Operation, Category, input_range_tag>
			: range<Category,
			typename range_traits<InputRange>::value_type,
			typename range_traits<InputRange>::position_type,
			typename range_traits<InputRange>::difference_type,
			typename range_traits<InputRange>::value_type>
		{
			typedef typename range_traits<transformed_range_base>::position_type position_type;
			typedef typename range_traits<transformed_range_base>::reference reference;

			// range requirements
			position_type  begin_pos() const                     { return self().range.begin_pos(); }
			void           begin_pos(position_type p)            { self().range.begin_pos(::std::move(p)); }
			position_type  end_pos() const			             { return self().range.end_pos(); }
			reference      at_pos(const position_type& p) const  { return self().op(self().range.at_pos(p)); }
			position_type& increment_pos(position_type& p) const { return self().range.increment_pos(p); }

		protected:
			Range& self() { return static_cast<Range&>(*this); }
			const Range& self() const { return static_cast<const Range&>(*this); }
		};

		template <class Range, class InputRange, class Operation, class Category>
		struct transformed_range_base<Range, InputRange, Operation, Category, forward_range_tag>
			: transformed_range_base<Range, InputRange, Operation, Category, input_range_tag>
		{
			typedef typename range_traits<transformed_range_base>::position_type position_type;
			typedef typename range_traits<transformed_range_base>::difference_type difference_type;

			using transformed_range_base<Range, InputRange, Operation, Category, input_range_tag>::end_pos;
			void end_pos(position_type p) { this->self().range.end_pos(::std::move(p)); }
			difference_type distance_pos(position_type p1, position_type p2) { return this->self().range.distance_pos(p1, p2); }
		};

		template <class Range, class InputRange, class Operation, class Category>
		struct transformed_range_base<Range, InputRange, Operation, Category, bidirectional_range_tag>
			: transformed_range_base<Range, InputRange, Operation, Category, forward_range_tag>
		{
			typedef typename range_traits<transformed_range_base>::position_type position_type;
			position_type& decrement_pos(position_type& p) { return this->self().range.decrement_pos(p); }
		};

		template <class Range, class InputRange, class Operation, class Category>
		struct transformed_range_base<Range, InputRange, Operation, Category, random_access_range_tag>
			: transformed_range_base<Range, InputRange, Operation, Category, bidirectional_range_tag>
		{
			typedef typename range_traits<transformed_range_base>::position_type position_type;
			typedef typename range_traits<transformed_range_base>::difference_type difference_type;
			position_type& advance_pos(position_type& p, difference_type n) const
			{
				return this->self().range.advance_pos(p, n);
			}
		};
	}

	template <class InputRange, class Operation>
	class transformed_range : public detail::transformed_range_base<transformed_range<InputRange, Operation>, InputRange, Operation, typename ::std::common_type<typename range_traits<InputRange>::range_category, random_access_range_tag>::type>
	{
	public:
		transformed_range(InputRange range, Operation op) : range(::std::move(range)), op(::std::move(op))
		{
		}

	private:
		friend struct detail::transformed_range_base<transformed_range<InputRange, Operation>, InputRange, Operation, typename ::std::common_type<typename range_traits<InputRange>::range_category, random_access_range_tag>::type, input_range_tag>;
		friend struct detail::transformed_range_base<transformed_range<InputRange, Operation>, InputRange, Operation, typename ::std::common_type<typename range_traits<InputRange>::range_category, random_access_range_tag>::type, forward_range_tag>;
		friend struct detail::transformed_range_base<transformed_range<InputRange, Operation>, InputRange, Operation, typename ::std::common_type<typename range_traits<InputRange>::range_category, random_access_range_tag>::type, bidirectional_range_tag>;
		friend struct detail::transformed_range_base<transformed_range<InputRange, Operation>, InputRange, Operation, typename ::std::common_type<typename range_traits<InputRange>::range_category, random_access_range_tag>::type, random_access_range_tag>;

		InputRange range;
		Operation op;
	};

	namespace detail
	{
		template <class Range, class InputRange, class Predicate, class Category, class BaseCategory = Category>
		struct unique_range_base;

		template <class Range, class InputRange, class Predicate, class Category>
		struct unique_range_base<Range, InputRange, Predicate, Category, input_range_tag>
			: range<Category,
				typename range_traits<InputRange>::value_type,
				typename range_traits<InputRange>::position_type,
				typename range_traits<InputRange>::difference_type,
				typename range_traits<InputRange>::reference>
		{
			typedef typename range_traits<unique_range_base>::position_type position_type;
			typedef typename range_traits<unique_range_base>::reference reference;

			// range requirements
			position_type  begin_pos() const                     { return self().range.begin_pos(); }
			void           begin_pos(position_type p)            { self().range.begin_pos(::std::move(p)); }
			position_type  end_pos() const			             { return self().range.end_pos(); }
			reference      at_pos(const position_type& p) const  { return self().range.at_pos(p); }
			position_type& increment_pos(position_type& p) const
			{
				auto current = p;
				do {
					self().range.increment_pos(p);
				} while (p != self().range.end_pos() && self().pred(self().range.at_pos(current), self().range.at_pos(p)));
				return p;
			}

		protected:
			Range& self() { return static_cast<Range&>(*this); }
			const Range& self() const { return static_cast<const Range&>(*this); }
		};

		template <class Range, class InputRange, class Predicate, class Category>
		struct unique_range_base<Range, InputRange, Predicate, Category, forward_range_tag>
			: unique_range_base<Range, InputRange, Predicate, Category, input_range_tag>
		{
			typedef typename range_traits<unique_range_base>::position_type position_type;
			typedef typename range_traits<unique_range_base>::difference_type difference_type;

			using unique_range_base<Range, InputRange, Predicate, Category, input_range_tag>::end_pos;
			void end_pos(position_type p) { this->self().range.end_pos(::std::move(p)); }
			difference_type distance_pos(position_type p1, position_type p2)
			{
				difference_type distance = 0;
				while (p1 != p2)
				{
					increment_pos(p1);
					++distance;
				}
				return distance;
			}
		};

		template <class Range, class InputRange, class Predicate, class Category>
		struct unique_range_base<Range, InputRange, Predicate, Category, bidirectional_range_tag>
			: unique_range_base<Range, InputRange, Predicate, Category, forward_range_tag>
		{
			typedef typename range_traits<unique_range_base>::position_type position_type;
			position_type& decrement_pos(position_type& p)
			{
				this->self().range.decrement_pos(p);
				auto current = p;
				while (p != this->self().range.begin_pos())
				{
					this->self().range.decrement_pos(current);
					if (!this->self().pred(this->self().range.at_pos(current), this->self().range.at_pos(p)))
						break;
					p = current;
				}

				return p;
			}
		};
	}

	template <class InputRange, class Predicate>
	class unique_range : public detail::unique_range_base<unique_range<InputRange, Predicate>, InputRange, Predicate, typename ::std::common_type<typename range_traits<InputRange>::range_category, bidirectional_range_tag>::type>
	{
	public:
		unique_range(InputRange range, Predicate pred) : range(::std::move(range)), pred(::std::move(pred))
		{
		}

	private:
		friend struct detail::unique_range_base<unique_range, InputRange, Predicate, typename ::std::common_type<typename range_traits<InputRange>::range_category, bidirectional_range_tag>::type, input_range_tag>;
		friend struct detail::unique_range_base<unique_range, InputRange, Predicate, typename ::std::common_type<typename range_traits<InputRange>::range_category, bidirectional_range_tag>::type, forward_range_tag>;
		friend struct detail::unique_range_base<unique_range, InputRange, Predicate, typename ::std::common_type<typename range_traits<InputRange>::range_category, bidirectional_range_tag>::type, bidirectional_range_tag>;

		InputRange range;
		Predicate pred;
	};

	namespace detail
	{
		template <class Range, class BidirectionalRange, class Category, class BaseCategory = Category>
		struct reversed_range_base;

		template <class Range, class BidirectionalRange, class Category>
		struct reversed_range_base<Range, BidirectionalRange, Category, bidirectional_range_tag>
			: range<Category,
				typename range_traits<BidirectionalRange>::value_type,
				typename range_traits<BidirectionalRange>::position_type,
				typename range_traits<BidirectionalRange>::difference_type,
				typename range_traits<BidirectionalRange>::reference>
		{
			typedef typename range_traits<reversed_range_base>::position_type position_type;
			typedef typename range_traits<reversed_range_base>::reference reference;
			typedef typename range_traits<reversed_range_base>::difference_type difference_type;

			position_type  begin_pos() const                     { return self().range.end_pos(); }
			void           begin_pos(position_type p)            { self().range.end_pos(::std::move(p)); }
			position_type  end_pos() const			             { return self().range.begin_pos(); }
			void           end_pos(position_type p)              { self().range.begin_pos(::std::move(p)); }
			reference      at_pos(const position_type& p) const
			{
				auto prev = p;
				self().range.decrement_pos(prev);
				return self().range.at_pos(prev);
			}
			position_type& increment_pos(position_type& p) const { return self().range.decrement_pos(p); }
			position_type& decrement_pos(position_type& p) const { return self().range.increment_pos(p); }
			difference_type distance_pos(position_type p1, position_type p2) const { return self().range.distance_pos(::std::move(p2), ::std::move(p1)); }

		protected:
			Range& self() { return static_cast<Range&>(*this); }
			const Range& self() const { return static_cast<const Range&>(*this); }
		};

		template <class Range, class BidirectionalRange, class Category>
		struct reversed_range_base<Range, BidirectionalRange, Category, random_access_range_tag>
			: reversed_range_base<Range, BidirectionalRange, Category, bidirectional_range_tag>
		{
			typedef typename range_traits<reversed_range_base>::position_type position_type;
			typedef typename range_traits<reversed_range_base>::reference reference;

			position_type  begin_pos() const                     { return this->self().range.end_pos(); }
			void           begin_pos(position_type p)            { this->self().range.end_pos(::std::move(p)); }
			position_type  end_pos() const			             { return this->self().range.begin_pos(); }
			void           end_pos(position_type p)              { this->self().range.begin_pos(::std::move(p)); }
			reference      at_pos(const position_type& p) const
			{
				auto prev = p;
				this->self().range.decrement_pos(prev);
				return this->self().range.at_pos(prev);
			}
			position_type& increment_pos(position_type& p) const { return this->self().range.decrement_pos(p); }
			position_type& decrement_pos(position_type& p) const { return this->self().range.increment_pos(p); }
		};
	}

	template <class BidirectionalRange>
	class reversed_range : public detail::reversed_range_base<reversed_range<BidirectionalRange>, BidirectionalRange, typename ::std::common_type<typename range_traits<BidirectionalRange>::range_category, random_access_range_tag>::type>
	{
	public:
		reversed_range(BidirectionalRange range) : range(range) { }

	private:
		friend struct detail::reversed_range_base<reversed_range, BidirectionalRange, typename ::std::common_type<typename range_traits<BidirectionalRange>::range_category, random_access_range_tag>::type, bidirectional_range_tag>;
		friend struct detail::reversed_range_base<reversed_range, BidirectionalRange, typename ::std::common_type<typename range_traits<BidirectionalRange>::range_category, random_access_range_tag>::type, random_access_range_tag>;

		BidirectionalRange range;
	};

	namespace detail
	{
		template <class Range, class ForwardRange, class Category, class BaseCategory = Category>
		struct rotated_range_base;

		template <class Range, class ForwardRange, class Category>
		struct rotated_range_base<Range, ForwardRange, Category, forward_range_tag>
			: range<Category,
				typename range_traits<ForwardRange>::value_type,
				typename range_traits<ForwardRange>::position_type,
				typename range_traits<ForwardRange>::difference_type,
				typename range_traits<ForwardRange>::reference>
		{
			typedef typename range_traits<rotated_range_base>::position_type position_type;
			typedef typename range_traits<rotated_range_base>::reference reference;
			typedef typename range_traits<rotated_range_base>::difference_type difference_type;

			position_type  begin_pos() const                     { return self().first; }
			void           begin_pos(position_type p)            { self().first = ::std::move(p); }
			position_type  end_pos() const			             { return self().last; }
			void           end_pos(position_type p)              { self().last = ::std::move(p); }
			reference      at_pos(const position_type& p) const  { return self().range.at_pos(p); }
			position_type& increment_pos(position_type& p) const
			{
				self().range.increment_pos(p);
				if (p == self().range.end_pos())
					p = self().range.begin_pos();
				if (p == self().first)
					p = self().range.end_pos();
				return p;
			}
			difference_type distance_pos(position_type p1, position_type p2) const
			{
				difference_type distance = 0;
				while (p1 != p2)
				{
					increment_pos(p1);
					++distance;
				}

				return distance;
			}

		protected:
			Range& self() { return static_cast<Range&>(*this); }
			const Range& self() const { return static_cast<const Range&>(*this); }
		};

		template <class Range, class ForwardRange, class Category>
		struct rotated_range_base<Range, ForwardRange, Category, bidirectional_range_tag>
			: rotated_range_base<Range, ForwardRange, Category, forward_range_tag>
		{
			typedef typename range_traits<rotated_range_base>::position_type position_type;

			position_type& decrement_pos(position_type& p) const
			{
				if (p == this->self().range.end_pos())
					p = this->self().first;
				if (p == this->self().range.begin_pos())
					p = this->self().range.end_pos();
				this->self().range.decrement_pos(p);
				return p;
			}
		};

		template <class Range, class ForwardRange, class Category>
		struct rotated_range_base<Range, ForwardRange, Category, random_access_range_tag>
			: rotated_range_base<Range, ForwardRange, Category, bidirectional_range_tag>
		{
			typedef typename range_traits<rotated_range_base>::position_type position_type;
			typedef typename range_traits<rotated_range_base>::difference_type difference_type;

			difference_type distance_pos(position_type p1, position_type p2) const
			{
				difference_type d1 = this->self().range.distance_pos(this->self().range.begin_pos(), p1);
				difference_type d2 = this->self().range.distance_pos(this->self().range.begin_pos(), p2);

				if (d1 > d2)
					return this->self().range.distance_pos(p1, this->self().range.end_pos()) + d2;

				return d2 - d1;
			}

			position_type& advance_pos(position_type& p, difference_type n)
			{
				difference_type d = this->self().range.distance_pos(this->self().range.end_pos());
				if (d < n)
				{
					p = this->self().range.begin_pos();
					n -= d;
				}

				return this->self().range.advance_pos(p, n);
			}
		};
	}

	template <class ForwardRange>
	class rotated_range : public detail::rotated_range_base<rotated_range<ForwardRange>, ForwardRange, typename ::std::common_type<typename range_traits<ForwardRange>::range_category, random_access_range_tag>::type>
	{
	public:
		typedef typename range_traits<rotated_range>::position_type position_type;

	public:
		rotated_range(ForwardRange range, ::std::ptrdiff_t n) : range(range)
		{
			first = this->range.begin_pos();
			last = this->range.end_pos();
			::stdext::advance_pos(this->range, first, n);
		}

	private:
		friend struct detail::rotated_range_base<rotated_range, ForwardRange, typename ::std::common_type<typename range_traits<ForwardRange>::range_category, random_access_range_tag>::type, forward_range_tag>;
		friend struct detail::rotated_range_base<rotated_range, ForwardRange, typename ::std::common_type<typename range_traits<ForwardRange>::range_category, random_access_range_tag>::type, bidirectional_range_tag>;
		friend struct detail::rotated_range_base<rotated_range, ForwardRange, typename ::std::common_type<typename range_traits<ForwardRange>::range_category, random_access_range_tag>::type, random_access_range_tag>;

		ForwardRange range;
		position_type first, last;
	};

	namespace detail
	{
		template <class Range, class ForwardRange, class Category, class BaseCategory = Category>
		struct partitioned_range_base;

		template <class Range, class ForwardRange, class Category>
		struct partitioned_range_base<Range, ForwardRange, Category, forward_range_tag>
			: range<Category,
				typename range_traits<ForwardRange>::value_type,
				typename range_traits<ForwardRange>::position_type,
				typename range_traits<ForwardRange>::difference_type,
				typename range_traits<ForwardRange>::reference>
		{
			typedef typename range_traits<partitioned_range_base>::position_type position_type;
			typedef typename range_traits<partitioned_range_base>::reference reference;
			typedef typename range_traits<partitioned_range_base>::difference_type difference_type;

			position_type  begin_pos() const                     { return self().first; }
			void           begin_pos(position_type p)            { self().first = ::std::move(p); }
			position_type  end_pos() const			             { return self().last; }
			void           end_pos(position_type p)              { self().last = ::std::move(p); }
			reference      at_pos(const position_type& p) const  { return self().range.at_pos(p); }
			position_type& increment_pos(position_type& p) const
			{
				bool select = self().pred(self().range.at_pos(p));
				position_type p_last = self().range.end_pos();
				do {
					self().range.increment_pos(p);
				} while (p != p_last && self().pred(self().range.at_pos(p)) != select);

				if (select && p == p_last)
				{
					p = self().range.begin_pos();
					while (p != p_last && self().pred(self().range.at_pos(p)) == select)
						self().range.increment_pos(p);
				}

				return p;
			}
			difference_type distance_pos(position_type p1, position_type p2) const
			{
				difference_type distance = 0;
				while (p1 != p2)
				{
					increment_pos(p1);
					++distance;
				}

				return distance;
			}

		protected:
			Range& self() { return static_cast<Range&>(*this); }
			const Range& self() const { return static_cast<const Range&>(*this); }
		};

		template <class Range, class ForwardRange, class Category>
		struct partitioned_range_base<Range, ForwardRange, Category, bidirectional_range_tag>
			: partitioned_range_base<Range, ForwardRange, Category, forward_range_tag>
		{
			typedef typename range_traits<partitioned_range_base>::position_type position_type;

			position_type& decrement_pos(position_type& p) const
			{
				position_type p_first = this->self().range.begin_pos();
				bool select = p != this->self().range.end_pos() && this->self().pred(this->self().range.at_pos(p));
				do {
					this->self().range.decrement_pos(p);
				} while (p != p_first && this->self().pred(this->self().range.at_pos(p)) != select);

				if ((p == p_first) && this->self().pred(this->self().range.at_pos(p)) != select)
				{
					p = this->self().range.end_pos();
					do {
						this->self().range.decrement_pos(p);
					} while (this->self().pred(this->self().range.at_pos(p)) == select);
				}

				return p;
			}
		};
	}

	template <class ForwardRange, class Predicate>
	class partitioned_range : public detail::partitioned_range_base<partitioned_range<ForwardRange, Predicate>, ForwardRange, typename ::std::common_type<typename range_traits<ForwardRange>::range_category, bidirectional_range_tag>::type>
	{
	public:
		typedef typename range_traits<partitioned_range>::position_type position_type;

	public:
		partitioned_range(ForwardRange range, Predicate pred) : range(::std::move(range)), pred(::std::move(pred))
		{
			first = this->range.begin_pos();
			last = this->range.end_pos();
			while (first != last && !this->pred(this->range.at_pos(first)))
				this->range.increment_pos(first);
			if (first == last)
				first = this->range.begin_pos();
		}

	private:
		friend struct detail::partitioned_range_base<partitioned_range<ForwardRange, Predicate>, ForwardRange, typename ::std::common_type<typename range_traits<ForwardRange>::range_category, bidirectional_range_tag>::type, forward_range_tag>;
		friend struct detail::partitioned_range_base<partitioned_range<ForwardRange, Predicate>, ForwardRange, typename ::std::common_type<typename range_traits<ForwardRange>::range_category, bidirectional_range_tag>::type, bidirectional_range_tag>;

		ForwardRange range;
		Predicate pred;
		position_type first, last;
	};
}

#include "adapter.inl"

#endif