//https://www.reddit.com/r/cpp_questions/comments/yfiryu/reading_3_words_in_a_row/
//Read words from the input and output 3 words per line

#include <iostream>
#include <iterator>
#include <string>

//I wish all the *_n algorithms could optionally take a sentinel.
template<typename InputIt, typename Sentinel, typename Size, typename OutputIt>
auto copy_n(InputIt first, Sentinel last, Size count, OutputIt result)
{
    for (Size i{0}; (first != last) and (i < count); ++i) {
        *result++ = *++first;
    }
    return std::make_pair(first, result);
}

int main()
{
    std::istream_iterator<std::string> first{std::cin};
    std::istream_iterator<std::string> last{};
    std::ostream_iterator<std::string> out{std::cout, " "};
    while (first != last) {
        first = copy_n(first, last, 3, out).first;
        std::cout << '\n';
    }
}
