//https://reddit.com/r/cpp_questions/comments/o7hwk0/max_char_occurence_in_string/
//Find which character occurs most in a string.

#include <string_view>
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>
#include <numeric>

auto max_char(std::string_view s)
{
    std::string cs{s};
    std::sort(cs.begin(), cs.end());
    auto last{std::unique(cs.begin(), cs.end())};
    cs.erase(last, cs.end());
    auto result{std::make_pair('\0', static_cast<size_t>(0))};
    for (char c: cs) {
        auto count{std::count(s.begin(), s.end(), c)};
        if (count > result.second) {
            result.first = c;
            result.second = count;
        }
    }
    return result;
}

auto max_char2(std::string_view s)
{
    std::string cs{s};
    std::sort(cs.begin(), cs.end());
    cs.erase(std::unique(cs.begin(), cs.end()), cs.end());
    auto result{
        std::accumulate(
                cs.begin(), cs.end(), 
                std::make_pair('\0', static_cast<size_t>(0)),
                [s](auto result, char c){
                    auto count{std::count(s.begin(), s.end(), c)};
                    if (count > result.second) {
                        return std::make_pair(c, static_cast<size_t>(count));
                    } else {
                        return result;
                    }
                })};
    return result;
}

int main()
{
    auto result{max_char("binit")};
    std::cout << result.first << ", " << result.second << '\n';
    result = max_char2("binit");
    std::cout << result.first << ", " << result.second << '\n';
}
