//https://reddit.com/r/cpp_questions/comments/u7oqro/how_to_make_an_array_that_would_output_this/
/*
how to make an array that would output this:

Enter the array length: 4
First array: 1 2 3 4
Second array: 3 4 1 2
Shift by 2

Enter the array length: 3
First array: 12 16 20
Second array: 16 12 20
Not a shift!

Enter the array length: 6
First array: 12 16 15 13 0 9
Second array: 16 15 13 0 9 12
Shift by 5
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string_view>
#include <optional>

std::vector<int> parse(const std::string& line)
{
    std::istringstream in{line};
    //Avoid the most vexing parse...
    auto out{std::vector<int>(
            std::istream_iterator<int>(in),
            std::istream_iterator<int>())};
    return out;
}

std::optional<std::vector<int>> ask_for_array(std::string_view prompt)
{
    std::cout << prompt << std::flush;
    std::string line;
    std::getline(std::cin, line);
    if (not std::cin) return std::nullopt;
    return parse(line);
}

int main()
{
    //We'll skip asking the length. We won't need it.

    while (true) {
        auto one{ask_for_array("\nFirst array: ")};
        if (not one) break;
        auto two{ask_for_array("Second array: ")};
        if (not two) break;
        if (one->size() != two->size()) {
            std::cout << "Not a shift!\n";
            continue;
        }
        auto first = two->begin();
        while (true) {
            first = std::find(first, two->end(), one->front());
            if (two->end() == first) {
                std::cout << "Not a shift!\n";
                break;		
            }
            bool end_equal { std::equal(first, two->end(), one->begin()) };
            auto end_size { std::distance(first, two->end()) };
            auto skip { one->begin() += end_size };
            bool start_equal { std::equal(two->begin(), first, skip) };
            if (end_equal and start_equal) {
                std::cout
                    << "Shift by "
                    << std::distance(two->begin(), first)
                    << '\n';
                break;
            }
            ++first;
            if (two->end() == first) {
                std::cout << "Not a shift!\n";
                break;		
            }
        }
    }
    std::cout << '\n';
}
