#include <range.h>

#include <iostream>
#include <fstream>

using namespace stdext;
using namespace std;

int main()
{
#if 0
	ifstream stream("hello.txt");
	istream_iterator<char> streamit(stream);
#endif
	string message = "Hello, world!";
	auto r = make_range(message);
#if 1
	for (; !r.empty(); r.drop_first())
		cout << r.front();
#else
	for (auto i = r.begin_pos(), last = r.end_pos(); i != last; ++i)
		cout << *i;
#endif

	cout << endl;
	system("pause");
}