namespace stdext
{
	// 25.2, non-modifying sequence operations:
	template <class SinglePassRange, class Predicate>
	bool all_of(SinglePassRange range, Predicate pred)
	{
		while (!range.empty())
		{
			if (!pred(range.front()))
				return false;
			range.shrink_front();
		}

		return true;
	}

	template <class SinglePassRange, class Predicate>
	bool any_of(SinglePassRange range, Predicate pred)
	{
		while (!range.empty())
		{
			if (pred(range.front()))
				return true;
			range.shrink_front();
		}

		return false;
	}

	template <class SinglePassRange, class Predicate>
	bool none_of(SinglePassRange range, Predicate pred)
	{
		return !any_of(range, pred);
	}

	template<class SinglePassRange, class Function>
	Function for_each(SinglePassRange range, Function f)
	{
		while (!range.empty())
		{
			f(range.front());
			range.shrink_front();
		}
	}

	template<class SinglePassRange, class T>
	decltype(std::declval(SinglePassRange).begin()) find(SinglePassRange range, const T& value)
	{
		while (!range.empty())
		{
			if (range.front() == value)
				return range.begin();
			range.shrink_front();
		}

		return range.end();
	}

	template<class SinglePassRange, class Predicate>
	decltype(std::declval(SinglePassRange).begin()) find_if(SinglePassRange range, Predicate pred)
	{
		while (!range.empty())
		{
			if (pred(range.front()))
				return range.begin();
			range.shrink_front();
		}

		return range.end();
	}

	template<class SinglePassRange, class Predicate>
	decltype(std::declval(SinglePassRange).begin()) find_if_not(SinglePassRange range, Predicate pred)
	{
		while (!range.empty())
		{
			if (!pred(range.front()))
				return range.begin();
			range.shrink_front();
		}

		return range.end();
	}

	template<class MultiPassRange1, class MultiPassRange2>
	decltype(std::declval(MultiPassRange1).begin()) find_end(MultiPassRange1 range1, MultiPassRange2 range2)
	{
		return find_end(range1, range2, [](typename range_traits<MultiPassRange1>::reference a, typename range_traits<MultiPassRange2>::reference b) { return a == b; });
	}

	template<class MultiPassRange1, class MultiPassRange2, class BinaryPredicate>
	decltype(std::declval(MultiPassRange1).begin()) find_end(MultiPassRange1 range1, MultiPassRange2 range2, BinaryPredicate pred)
	{
		auto p = range1.end();

		while (true)
		{
			MultiPassRange1 r1 = range1.save();
			MultiPassRange2 r2 = range2.save();
			while (!r2.empty() && !r1.empty())
			{
				if (!pred(r1.front(), r2.front()))
					break;

				r1.shrink_front();
				r2.shrink_front();
			}

			if (r2.empty())
				p = r1.begin();

			if (r1.empty())
				break;

			range1.shrink_front();
		}

		return p;
	}
}