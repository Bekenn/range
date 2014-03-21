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
		template <class T> struct range_gather_t;
		template <class Predicate> struct range_gather_if_t;
	}

	template <class Range>     detail::range_prepend_t<Range>       prepend(Range&& r);
	template <class Range>     detail::range_append_t<Range>        append(Range&& r);
	                           detail::range_trim_front_t           trim_front(::std::size_t n);
							   detail::range_trim_back_t            trim_back(::std::size_t n);
							   detail::range_subrange_t             subrange(::std::size_t n1, ::std::size_t n2);
	template <class T>         detail::range_remove_t<T>            remove(T&& value);
	template <class Predicate> detail::range_remove_if_t<Predicate> remove_if(Predicate&& pred);
	template <class Predicate> detail::range_select_t<Predicate>    select(Predicate&& pred);
	template <class Operation> detail::range_transform_t<Operation> transform(Operation&& op);
	template <class T>         detail::range_replace_t<T>           replace(T&& old_value, T&& new_value);
	template <class Predicate, class T> detail::range_replace_if_t<Predicate, T> replace(Predicate&& pred, T&& new_value);
	                           detail::range_unique_t               unique();
	template <class Predicate> detail::range_unique_if_t<Predicate> unique(Predicate&& pred);
	                           detail::range_reverse_t              reverse();
	                           detail::range_rotate_t               rotate(::std::ptrdiff_t n);
	template <class T>         detail::range_gather_t<T>            gather(T&& value);
	template <class Predicate> detail::range_gather_if_t<Predicate> gather_if(Predicate&& pred);

	namespace detail
	{
		template <class Range> struct range_prepend_t { Range r; };
		template <class Range> struct range_append_t { Range r; };
		struct range_trim_front_t;
		struct range_trim_back_t;
		struct range_subrange_t;
		template <class T> struct range_remove_t;
		template <class Predicate> struct range_remove_if_t;
		template <class T> struct range_select_t;
		template <class Predicate> struct range_select_if_t;
		template <class Operation> struct range_transform_t;

		template <class T> struct range_replace_t { T old_value, new_value; };
		template <class T> struct range_replace_op
		{
			range_replace_op(const range_replace_t<T>& replace) : replace(replace) { }
			range_replace_op(range_replace_t<T>&& replace) : replace(::std::move(replace)) { }
			T operator () (const T& value) { return value == replace.old_value ? replace.new_value : value; }
			range_replace_t<T> replace;
		};

		template <class Predicate, class T> struct range_replace_if_t { Predicate pred; T new_value; };
		template <class Predicate, class T> struct range_replace_if_op
		{
			range_replace_if_op(const range_replace_if_t<Predicate, T>& replace) : replace(replace) { }
			range_replace_if_op(range_replace_if_t<Predicate, T>&& replace) : replace(::std::move(replace)) { }
			T operator () (const T& value) { return replace.pred(value) ? replace.new_value : value; }
			range_replace_if_t<Predicate, T> replace;
		};

		struct range_unique_t;
		template <class Predicate> struct range_unique_if_t;
		struct range_reverse_t;
		struct range_rotate_t;
		template <class T> struct range_gather_t;
		template <class Predicate> struct range_gather_if_t;
	}

	template <class Range1, class Range2>
	concatenated_range<Range2, Range1> operator >> (Range1&& range1, detail::range_prepend_t<Range2>&& prepend);
	template <class Range1, class Range2>
	concatenated_range<Range1, Range2> operator >> (Range1&& range1, detail::range_append_t<Range2>&& append);
	template <class Range>
	Range operator >> (Range&& range, detail::range_trim_front_t&& trim_front);
	template <class Range>
	Range operator >> (Range&& range, detail::range_trim_back_t&& trim_back);
	template <class Range>
	Range operator >> (Range&& range, detail::range_subrange_t&& subrange);
	template <class Range, class T>
	filtered_range<Range, decltype(::std::bind(::std::not_equal_to<typename range_traits<Range>::value_type>(), ::std::placeholders::_1, ::std::declval<T>()))>
		operator >> (Range&& range, detail::range_remove_t<T>&& remove);
	template <class Range, class Predicate>
	filtered_range<Range, ::std::unary_negate<Predicate>> operator >> (Range&& range, detail::range_remove_if_t<Predicate>&& remove);
	template <class Range, class T>
	filtered_range<Range, decltype(::std::bind(::std::equal_to<typename range_traits<Range>::value_type>(), ::std::declval<T>()))>
		operator >> (Range&& range, detail::range_select_t<T>&& select);
	template <class Range, class Predicate>
	filtered_range<Range, Predicate> operator >> (Range&& range, detail::range_select_if_t<Predicate>&& select);
	template <class Range, class Operation>
	transformed_range<Range, Operation> operator >> (Range&& range, detail::range_transform_t<Operation>&& op);
	template <class Range, class T>
	transformed_range<Range, detail::range_replace_op<T>> operator >> (Range&& range, detail::range_replace_t<T>&& replace);
	template <class Range, class Predicate, class T>
	transformed_range<Range, detail::range_replace_if_op<Predicate, T>> operator >> (Range&& range, detail::range_replace_if_t<Predicate, T>&& replace);
	template <class Range>
	unique_range<Range, ::std::equal_to<typename range_traits<Range>::value_type>> operator >> (Range&& range, detail::range_unique_t&& unique);
	template <class Range, class Predicate>
	unique_range<Range, Predicate> operator >> (Range&& range, detail::range_unique_if_t<Predicate>&& unique);
	template <class Range>
	reversed_range<Range> operator >> (Range&& range, detail::range_reverse_t&& reverse);
	template <class Range>
	rotated_range<Range> operator >> (Range&& range, detail::range_rotate_t&& rotate);
	template <class Range, class T>
	partitioned_range<Range, ::std::equal_to<typename range_traits<Range>::value_type>> operator >> (Range&& range, detail::range_gather_t<T> gather);
	template <class Range, class Predicate>
	partitioned_range<Range, Predicate> operator >> (Range&& range, detail::range_gather_if_t<Predicate> gather);

	namespace detail
	{
		template <class Range, class InputRange1, class InputRange2, class Category, class BaseCategory = Category>
		class concatenated_range_base;

		template <class Range, class InputRange1, class InputRange2, class Category>
		class concatenated_range_base<Range, InputRange1, InputRange2, Category, input_range_tag>
			: public range<Category,
				typename range_traits<InputRange1>::value_type,
				::std::pair<typename range_traits<InputRange1>::position_type, typename range_traits<InputRange2>::position_type>,
				::std::ptrdiff_t,
				typename ::std::conditional<::std::is_const<typename ::std::remove_reference<typename range_traits<InputRange1>::reference>::type>::value,
					typename range_traits<InputRange1>::reference, typename range_traits<InputRange2>::reference>::type>
		{
		public:
			typedef typename range_traits<concatenated_range_base>::position_type position_type;
			typedef typename range_traits<concatenated_range_base>::reference reference;

			position_type begin_pos() const noexcept { return self().first; }
			position_type end_pos() const noexcept   { return self().last; }
			void begin_pos(const position_type& pos) { self().first = pos; }
			void end_pos(const position_type& pos)   { self().last = pos; }

			position_type& increment_pos(position_type& pos)
			{
				if (pos.first != self().range1.end_pos())
					self().range1.increment_pos(pos.first);
				else
					self().range2.increment_pos(pos.second);

				return pos;
			}

			position_type& decrement_pos(position_type& pos)
			{
				if (pos.second != self().range2.begin_pos())
					self().range2.decrement_pos(pos.second);
				else
					self().range1.decrement_pos(pos.first);

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
		class concatenated_range_base<Range, InputRange1, InputRange2, Category, forward_range_tag>
			: public concatenated_range_base<Range, InputRange1, InputRange2, Category, input_range_tag>
		{
		};

		template <class Range, class InputRange1, class InputRange2, class Category>
		class concatenated_range_base<Range, InputRange1, InputRange2, Category, bidirectional_range_tag>
			: public concatenated_range_base<Range, InputRange1, InputRange2, Category, forward_range_tag>
		{
		};

		template <class Range, class InputRange1, class InputRange2, class Category>
		class concatenated_range_base<Range, InputRange1, InputRange2, Category, random_access_range_tag>
			: public concatenated_range_base<Range, InputRange1, InputRange2, Category, bidirectional_range_tag>
		{
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
		friend class detail::concatenated_range_base<concatenated_range, InputRange1, InputRange2, range_category, input_range_tag>;

		InputRange1 range1;
		InputRange2 range2;
		position_type first, last;
	};
}

#include "adapter.inl"

#endif