#ifndef FIXTURE_INCLUDED
#define FIXTURE_INCLUDED
#pragma once

#include <iterator>
#include <numeric>

#include <forward_list>
#include <list>
#include <vector>


using namespace std;

template <typename T>
class memory_input_iterator : public iterator<input_iterator_tag, T, ptrdiff_t, T*, T>
{
public:
	typedef typename memory_input_iterator::value_type value_type;
	typedef typename memory_input_iterator::pointer pointer;
	typedef typename memory_input_iterator::reference reference;

public:
	memory_input_iterator() : p(nullptr), length(0) { }
	memory_input_iterator(pointer p, size_t length) : p(p), length(length)
	{
		if (length == 0)
			p = nullptr;
		else
			v = *p;
	}

public:
	reference operator * () const { return v; }
	memory_input_iterator& operator ++ ()
	{
		++p;
		if (--length == 0)
			p = nullptr;
		else
			v = *p;
		return *this;
	}
	memory_input_iterator operator ++ (int)
	{
		auto i = *this;
		++*this;
		return i;
	}

private:
	friend bool operator == (const memory_input_iterator& a, const memory_input_iterator& b) { return a.p == b.p && a.length == b.length; }
	pointer p;
	size_t length;
	value_type v;
};

template <typename T>
bool operator != (const memory_input_iterator<T>& a, const memory_input_iterator<T>& b) { return !(a == b); }

struct input_iterator_range_fixture
{
private:
	std::vector<int> numbers;
public:
	memory_input_iterator<int> first, last;

	input_iterator_range_fixture() : numbers(10), first(numbers.data(), numbers.size()), last()
	{
		std::iota(numbers.begin(), numbers.end(), 0);
	}
};

struct forward_iterator_range_fixture
{
private:
	std::forward_list<int> numbers;
public:
	std::forward_list<int>::iterator first, last;

	forward_iterator_range_fixture() : numbers(10), first(numbers.begin()), last(numbers.end())
	{
		std::iota(numbers.begin(), numbers.end(), 0);
	}
};

struct bidirectional_iterator_range_fixture
{
private:
	std::list<int> numbers;
public:
	std::list<int>::iterator first, last;

	bidirectional_iterator_range_fixture() : numbers(10), first(numbers.begin()), last(numbers.end())
	{
		std::iota(numbers.begin(), numbers.end(), 0);
	}
};

struct random_access_iterator_range_fixture
{
private:
	std::vector<int> numbers;
public:
	std::vector<int>::iterator first, last;

	random_access_iterator_range_fixture() : numbers(10), first(numbers.begin()), last(numbers.end())
	{
		std::iota(numbers.begin(), numbers.end(), 0);
	}
};

#endif
