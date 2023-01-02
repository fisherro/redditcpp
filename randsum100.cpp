//INCOMPLETE
//Generate a list of unique random integers that sum to 100

#include <vector>
#include <numeric>
#include <random>
#include <iostream>
#include <iterator>
#include <string_view>

int r(std::default_random_engine& engine, int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine);
}

void print(std::string_view name, std::ostream& out, const std::vector<int>& v)
{
    out << name << ":";
    std::copy(v.begin(), v.end(),
            std::ostream_iterator<int>(out, ","));
    out << '\n';
}

int main()
{
    std::vector<int> ns(100, 0);
    std::iota(ns.begin(), ns.end(), 1);
    std::random_device device;
    std::default_random_engine engine(device());
    std::vector<int> results;
    while (true) {
        //We can get into a situation where the number we need has already been picked
        print("ns", std::cerr, ns);
        print("results", std::cerr, results);
        int index = r(engine, 0, ns.size() - 1);
        results.push_back(ns.at(index));
        int sum = std::accumulate(results.begin(), results.end(), 0);
        if (100 == sum) break;
        //Could remove all numbers > (100 - sum)
        ns.erase(ns.begin() + index);
        if (sum < 100) continue;
        results.pop_back();
    }
    print("Results", std::cout, results);
    std::cout << '\n';
}
