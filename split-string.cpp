//https://reddit.com/r/cpp_questions/comments/lse6dg/split_c_string_by_spaces_unless_enclosed_by/
/*
 * I am trying to split a c++ string by spaces unless it is enclosed by quotes. Then it should be dealt with as its own string. I also can not use vectors. If anyone could give me a hint or point me in the right direction it would be greatly appreciated!
 */
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

int main()
{
#if 1
    std::cout << "__cplusplus = " << __cplusplus << '\n';
    std::cout << "__VERSION__ = " << __VERSION__ << '\n';

    std::cout << __GNUC__ << '.' << __GNUC_MINOR__ << '.' << __GNUC_PATCHLEVEL__ << '\n';
#endif
    std::string s{"This is \"a test\""};
    std::istringstream i{s};
    std::string part;
    while (i >> std::quoted(part)) {
        std::cout << part << '\n';
    }
}
