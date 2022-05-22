//Convert the identifiers in a source file from camelCase to snake_case
//https://reddit.com/r/C_Programming/comments/usyufg/_/i9aq5cl/?context=1

//Performance is poor, but that isn't a surprise.

//thisIsATest <-- We don't handle this case well
//thisIsAnExclusion

#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <unordered_set>

std::unordered_set<std::string> exclusions{"thisIsAnExclusion"};

template <typename F>
void replace(const std::string& in, const std::regex& rx, std::ostream& out, F f)
{
    auto begin = std::sregex_iterator(in.begin(), in.end(), rx);
    auto end = std::sregex_iterator();
    std::string suffix{in};
    for (auto iter{begin}; iter != end; ++iter) {
        auto& match{*iter};
        out << match.prefix().str() << f(match);
        suffix = match.suffix().str();
    }
    out << suffix;
}

std::string convert(const std::smatch& m)
{
    //TODO: This is a mess!
    std::string out{m[1].str()};
    out += '_';
    auto uc{m[2].str()};
    out += static_cast<char>(std::tolower(uc[0]));
    return out;
}

std::string cc2sc(const std::smatch& m)
{
    std::string match{m[0].str()};
    if (exclusions.count(match) > 0) {
        return match;
    }
    std::ostringstream out;
    std::regex rx{"([a-z])([A-Z])"};
    replace(match, rx, out, convert);
    return out.str();
}

int main()
{
    std::regex identifier{"[a-zA-Z_][a-zA-Z_0-9]*"};
    std::string line;
    while (std::getline(std::cin, line)) {
        replace(line, identifier, std::cout, cc2sc);
        std::cout << '\n';
    }
}
