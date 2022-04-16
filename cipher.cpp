/*
https://reddit.com/r/cpp_questions/comments/kvgmct/c_substitution_cipher/

C++ Substitution Cipher

Can someone suggest a way i would go about implementing a substitution cipher where a = 1, b = 2, c = 3, etc. The goal is to take names of animals and have them be displayed as the cipher so pig would be 1697 for example.
The idea is that i need to pass a string of plain text through a cipher to “encrypt” it to its numeric format.
Any help or guidance will be appreciated.

-----

Doing math on chars is fine (`int n = c - 'b';`) if you know that the code will run on machine where the charset has the alphabetic characters contiguous and in the proper order. There is a good chance that will indeed be the case, but you should be aware of the issue.

Another—more portable—alternative is to use something like `std::unordered_map<char, int>` that has the characters as keys and their int value as values.

Another good exercise is to instead use a sorted `std::vector<std::pair<char, int>>` and use the binary search algorithms from the standard library.
*/
#include <vector>
#include <string_view>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <string>
#include <iostream>

// First method
// This method assumes that the lowercase alphabetic characters in the charset are continguous and in alphabetical order.
// While this is a safe assumption on the majority of the systems in use today, it is not guaranteed.

std::vector<int> encipher1(std::string_view in)
{
    std::vector<int> out;
    out.reserve(in.size());
    std::transform(in.begin(), in.end(), std::back_inserter(out), [](char c){ return std::isalpha(c)? (std::tolower(c) - 'a') + 1: 0; });
    return out;
}

// Second method
// This method will work even on a system that uses EBCDIC or another charset where the assumptions of the first method don't hold.

std::unordered_map<char, int> encipher2_map_init()
{
    std::string alphabet{"abcdefghijklmnopqrstuvwxyz"};
    std::unordered_map<char, int> map;
    int n{0};
    for (const char c: alphabet) {
        map[c] = ++n;
    }
    return map;
}

std::vector<int> encipher2(std::string_view in)
{
    static const std::unordered_map<char, int> map{encipher2_map_init()};
    std::vector<int> out;
    out.reserve(in.size());
    auto lookup{
        [](const char c){
            auto i{map.find(c)};
            if (map.end() == i) return 0;
            return i->second;
        }
    };
    std::transform(in.begin(), in.end(), std::back_inserter(out), lookup);
    return out;
}

// Third method
// The second method used a hash-table (a.k.a. std::unordered_map), but a hash_table can often be out-performed by using binary searches on a sorted vector.
// See also Boost's flat_map.

std::vector<std::pair<char, int>> encipher3_map_init()
{
    std::string alphabet{"abcdefghijklmnopqrstuvwxyz"};
    std::vector<std::pair<char, int>> map;
    map.reserve(alphabet.size());
    int n{0};
    for (const char c: alphabet) {
        map.push_back(std::make_pair(c, ++n));
    }
    std::sort(map.begin(), map.end());
    return map;
}

std::vector<int> encipher3(std::string_view in)
{
    static const auto map{encipher3_map_init()};
    std::vector<int> out;
    out.reserve(in.size());
    auto lookup{
        [](const char c){
            auto i{std::lower_bound(map.begin(), map.end(), std::make_pair(c, 10), [](const auto& a, const auto& b){ return a.first < b.first; })};
            if (map.end() == i) return 0;
            return i->second;
        }
    };
    std::transform(in.begin(), in.end(), std::back_inserter(out), lookup);
    return out;
}

int main(int argc, const char** argv)
{
    auto test{
        [](auto f, std::string_view arg){
            const auto cipher_text { f(arg) };
            std::cout << arg << ": ";
            std::copy(cipher_text.begin(), cipher_text.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << '\n';
        }
    };

    std::vector<std::string> args(argv + 1, argv + argc);
    for (std::string_view arg: args) {
        test(encipher1, arg);
        test(encipher2, arg);
        test(encipher3, arg);
    }
}
