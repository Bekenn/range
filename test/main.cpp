#include <range.h>

#include <iostream>
#include <fstream>

using namespace stdext;
using namespace std;

int main()
{
	ifstream stream("hello.txt");
	istream_iterator<char> streamit(stream);
	//string message = "Hello, world!";
	auto r = make_range(streamit, istream_iterator<char>());
	while (!r.empty())
	{
		cout << r.front();
		r.pop_front();
	}
}