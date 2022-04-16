//https://reddit.com/r/cpp_questions/comments/myce30/removing_duplicates_in_an_unsorted_array/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <unordered_set>

//I don't know why std::size isn't being found.
namespace std {
    template <class T, std::size_t N>
    constexpr std::size_t size(const T (&array)[N]) noexcept
    {
        return N;
    }
}

const int ns[] = {3, 5, 3, 2, 7, 10, 15, 15, 2, 5, 1};

template <typename Begin, typename End, typename Out>
auto unique_unsorted(Begin begin, End end, Out out)
{
    using Value = std::remove_const_t<std::remove_reference_t<decltype(*begin)>>;
    std::unordered_set<Value> set;

    auto f = [&set, &out](const auto& v){
        if (set.count(v) == 0) {
            *out++ = v;
            set.insert(v);
        }
    };

    std::for_each(begin, end, f);
    return out;
}

int main()
{
    std::copy(std::begin(ns), std::end(ns), std::ostream_iterator<int>(std::cout, ","));
    std::cout << '\n';

    std::unordered_set<int> set(std::begin(ns), std::end(ns));
    std::copy(set.begin(), set.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << '\n';

    int copy[std::size<int>(ns)];
    std::copy(std::begin(ns), std::end(ns), std::begin(copy));
    std::sort(std::begin(copy), std::end(copy));
    auto end { std::unique(std::begin(copy), std::end(copy)) };
    std::copy(std::begin(copy), end, std::ostream_iterator<int>(std::cout, ","));
    std::cout << '\n';

    //What if we want to keep the original order?
    int stable_copy[std::size<int>(ns)];
    auto stable_end { unique_unsorted(std::begin(ns), std::end(ns), std::begin(stable_copy)) };
    std::copy(std::begin(stable_copy), stable_end, std::ostream_iterator<int>(std::cout, ","));
    std::cout << '\n';
}
