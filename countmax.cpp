//https://reddit.com/r/cpp_questions/comments/w9d0hm/in_exercise_i_have_to_find_largest_number_in/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main()
{
    std::istream_iterator<int> in_first(std::cin);
    std::istream_iterator<int> in_last{};
    std::vector<int> ns;
    std::copy(in_first, in_last, std::back_inserter(ns));
    auto max { std::max_element(ns.begin(), ns.end()) };
    std::cout << std::count(ns.begin(), ns.end(), *max) << '\n';
}
