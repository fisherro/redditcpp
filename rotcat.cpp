#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename C, typename T>
auto at(const C& c, size_t i, /*decltype(std::declval<C>[0])*/T v)
{
    return (i >= std::size(c))? v: c[i];
}

int main()
{
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(std::cin, line)) lines.push_back(line);
    //This could be better in C++20
    auto longest { std::max_element(lines.begin(), lines.end(), [](const auto& a, const auto& b){ return a.size() < b.size(); }) };
    size_t max { lines.end() != longest? longest->size(): 0 };
    for (size_t i{0}; i < max; ++i) {
        for (const auto& line: lines) {
            std::cout << at(line, i, ' ');
        }
        std::cout << '\n';
    }
}
