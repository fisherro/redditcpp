//https://reddit.com/r/cpp_questions/comments/w9d0hm/in_exercise_i_have_to_find_largest_number_in/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> ns(
            std::istream_iterator<int>{std::cin},
            std::istream_iterator<int>{});
    auto max { std::max_element(ns.begin(), ns.end()) };
    std::cout << std::count(ns.begin(), ns.end(), *max) << '\n';
}
