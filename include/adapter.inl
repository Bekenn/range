namespace stdext
{
	template <class Range>
	detail::range_prepend_t<Range> prepend(Range&& r)
	{
		return { ::std::forward<Range>(r) };
	}

	template <class Range>
	detail::range_append_t<Range> append(Range&& r)
	{
		return { ::std::forward<Range>(r) };
	}

	template <class Range1, class Range2>
	concatenated_range<Range2, Range1> operator >> (Range1&& range1, detail::range_prepend_t<Range2>&& prepend)
	{
		return concatenated_range<Range2, Range1>(prepend.r, range1);
	}

	template <class Range1, class Range2>
	concatenated_range<Range1, Range2> operator >> (Range1&& range1, detail::range_append_t<Range2>&& append)
	{
		return concatenated_range<Range1, Range2>(range1, append.r);
	}

	inline detail::range_trim_front_t trim_front(::std::size_t n)
	{
		return { n };
	}

	inline detail::range_trim_back_t trim_back(::std::size_t n)
	{
		return { n };
	}

	inline detail::range_subrange_t subrange(::std::size_t n1, ::std::size_t n2)
	{
		return { n1, n2 };
	}

	template <class Range>
	Range operator >> (Range&& range, const detail::range_trim_front_t& trim_front)
	{
		auto r = ::std::forward<Range>(range);
		drop_first(r, trim_front.n);
		return r;
	}

	template <class Range>
	Range operator >> (Range&& range, const detail::range_trim_back_t& trim_back)
	{
		auto r = ::std::forward<Range>(range);
		drop_last(r, trim_back.n);
		return r;
	}

	template <class Range>
	Range operator >> (Range&& range, const detail::range_subrange_t& subrange)
	{
		auto r = ::std::forward<Range>(range);
		drop_last(r, length(r) - subrange.n2);
		drop_first(r, subrange.n1);
		return r;
	}

	template <class T>
	detail::range_remove_t<T> remove(T&& value)
	{
		return { ::std::forward<T>(value) };
	}

	template <class Predicate>
	detail::range_remove_if_t<Predicate> remove_if(Predicate&& pred)
	{
		return { ::std::forward<Predicate>(pred) };
	}

	template <class T>
	detail::range_select_t<T> select(T&& value)
	{
		return { ::std::forward<T>(value) };
	}

	template <class Predicate>
	detail::range_select_if_t<Predicate> select_if(Predicate&& pred)
	{
		return { ::std::forward<Predicate>(pred) };
	}

	template <class Range, class T>
	filtered_range<Range, detail::range_remove_op<T>> operator >> (Range&& range, detail::range_remove_t<T>&& remove)
	{
		return filtered_range<Range, detail::range_remove_op<T>>(::std::forward<Range>(range), { ::std::forward<T>(remove.v) });
	}

	template <class Range, class Predicate>
	filtered_range<Range, detail::range_remove_if_op<Predicate, typename range_traits<Range>::value_type>>
		operator >> (Range&& range, detail::range_remove_if_t<Predicate>&& remove)
	{
		return filtered_range<Range, detail::range_remove_if_op<Predicate, typename range_traits<Range>::value_type>>(::std::forward<Range>(range),
			{ ::std::forward<Predicate>(remove.p) });
	}

	template <class Range, class T>
	filtered_range<Range, detail::range_select_op<T>> operator >> (Range&& range, detail::range_select_t<T>&& select)
	{
		return filtered_range<Range, detail::range_select_op<T>>(::std::forward<Range>(range), { ::std::forward<T>(select.v) });
	}

	template <class Range, class Predicate>
	filtered_range<Range, Predicate> operator >> (Range&& range, detail::range_select_if_t<Predicate>&& select)
	{
		return filtered_range<Range, Predicate>(::std::forward<Range>(range), ::std::forward<Predicate>(select.p));
	}

	template <class Operation>
	detail::range_transform_t<Operation> transform(Operation&& op)
	{
		return { ::std::forward<Operation>(op) };
	}

	template <class Range, class Operation>
	transformed_range<Range, Operation> operator >> (Range&& range, detail::range_transform_t<Operation>&& transform)
	{
		return transformed_range<Range, Operation>(::std::forward<Range>(range), ::std::forward<Operation>(transform.op));
	}

	template <class T>
	detail::range_replace_t<T> replace(T&& old_value, T&& new_value)
	{
		return { ::std::forward<T>(old_value), ::std::forward<T>(new_value) };
	}

	template <class Range, class T>
	transformed_range<Range, detail::range_replace_op<T>> operator >> (Range&& range, detail::range_replace_t<T>&& replace)
	{
		return transformed_range<Range, detail::range_replace_op<T>>(::std::forward<Range>(range), ::std::forward<detail::range_replace_t<T>>(replace));
	}

	template <class Predicate, class T>
	detail::range_replace_if_t<Predicate, T> replace_if(Predicate&& pred, T&& new_value)
	{
		return { ::std::forward<Predicate>(pred), ::std::forward<T>(new_value) };
	}

	template <class Range, class Predicate, class T>
	transformed_range<Range, detail::range_replace_if_op<Predicate, T>> operator >> (Range&& range, detail::range_replace_if_t<Predicate, T>&& replace)
	{
		return transformed_range<Range, detail::range_replace_if_op<Predicate, T>>(::std::forward<Range>(range), ::std::forward<detail::range_replace_if_t<Predicate, T>>(replace));
	}

	detail::range_unique_t unique()
	{
		return { };
	}

	template <class Range>
	unique_range<Range, ::std::equal_to<>> operator >> (Range&& range, const detail::range_unique_t& unique)
	{
		return unique_range<Range, ::std::equal_to<>>(::std::forward<Range>(range), ::std::equal_to<>());
	}

	template <class Predicate>
	detail::range_unique_if_t<Predicate> unique_if(Predicate&& pred)
	{
		return { ::std::forward<Predicate>(pred) };
	}

	template <class Range, class Predicate>
	unique_range<Range, Predicate> operator >> (Range&& range, detail::range_unique_if_t<Predicate>&& unique)
	{
		return unique_range<Range, Predicate>(::std::forward<Range>(range), ::std::forward<Predicate>(unique.pred));
	}

	inline detail::range_reverse_t reverse()
	{
		return { };
	}

	template <class Range>
	reversed_range<Range> operator >> (Range&& range, detail::range_reverse_t&& reverse)
	{
		return reversed_range<Range>(::std::forward<Range>(range));
	}

	inline detail::range_rotate_t rotate(::std::ptrdiff_t n)
	{
		return { n };
	}

	template <class Range>
	rotated_range<Range> operator >> (Range&& range, detail::range_rotate_t&& rotate)
	{
		return rotated_range<Range>(::std::forward<Range>(range), ::std::forward<::std::ptrdiff_t>(rotate.n));
	}

	template <class T>
	detail::range_partition_t<T> partition(T&& value)
	{
		return { ::std::forward<T>(value) };
	}

	template <class Predicate>
	detail::range_partition_if_t<Predicate> partition_if(Predicate&& pred)
	{
		return { ::std::forward<Predicate>(pred) };
	}

	template <class Range, class T>
	partitioned_range<Range, detail::range_partition_op<T>> operator >> (Range&& range, detail::range_partition_t<T>&& partition)
	{
		return partitioned_range<Range, detail::range_partition_op<T>>(::std::forward<Range>(range), ::std::forward<T>(partition.value));
	}

	template <class Range, class Predicate>
	partitioned_range<Range, Predicate> operator >> (Range&& range, detail::range_partition_if_t<Predicate>&& partition)
	{
		return partitioned_range<Range, Predicate>(::std::forward<Range>(range), ::std::forward<Predicate>(partition.pred));
	}
}