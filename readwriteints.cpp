//https://reddit.com/r/cpp_questions/comments/jyf4ub/reading_from_standard_input/
/*
 *  My purpose is to read space separated numbers from std input,
 *  and I don't know how I go about doing it since most beginner
 *  c++ resources use cout to ask for a prompt and then store the
 *  subsequent cin value into a variable to work with. I, however,
 *  need my program to work like:
 *
 *  ./program arguments
 *  < set of numbers >
 */
#ifdef USE_VECTOR
#include <vector>
#endif
#include <iterator>
#include <iostream>

int main()
{
#ifdef USE_VECTOR
    //Read whitespace separated numbers into ns.
    std::vector<int> ns(
            std::istream_iterator<int>(std::cin),
            std::istream_iterator<int>());

    //Write each number on a new line.
    for (int n: ns) std::cout << n << '\n';
#else
    std::copy(
            std::istream_iterator<int>(std::cin),
            std::istream_iterator<int>(),
            std::ostream_iterator<int>(std::cout, "\n"));
#endif
}
