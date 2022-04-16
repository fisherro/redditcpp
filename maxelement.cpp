//https://reddit.com/r/cpp_questions/comments/u4z7bp/need_help_reversing_my_code/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <cxxabi.h>

int main()
{
	std::cout << "Input 15 integers\n";
	std::vector<int> ns;
	std::copy_n(std::istream_iterator<int>(std::cin), 15, std::back_inserter(ns));
#if 0
	auto iter { std::min_element(ns.begin(), ns.end()) };
#else
	auto iter { std::max_element(ns.begin(), ns.end()) };
#endif
	std::cout << "Index " << std::distance(ns.begin(), iter) << ": " << *iter << '\n';
}
