//Inspired by:
//https://www.reddit.com/r/cpp_questions/comments/xqz60k/what_would_be_the_most_efficient_way_to_extract/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

const std::string file_contents{
R"HERE(3 FNAME MNAME LNAME
Clark S Kent
Lois L Lane

3 STREET CITY STATE ZIP
"1313 Mockingbird Lane" Smallville IN 00000
"221B Baker Street" Metropolis NY 00000
)HERE"
};

using Record = std::unordered_map<std::string, std::string>;
using Section = std::vector<Record>;
using File = std::vector<Section>;

Record read_record(const std::string line, const std::vector<std::string>& headers)
{
    Record record;
    std::vector<std::string> values;
    std::istringstream s{line};
    std::string value;
    while (s >> std::quoted(value)) values.push_back(value);
    std::transform(
        headers.begin(), headers.end(),
        values.begin(),
        std::inserter(record, record.end()),
        [](std::string_view key, std::string_view value){
            return std::pair<std::string, std::string>{key, value};
        });
    return record;
}

Section read_section(std::istream& s)
{
    Section section;
    std::string line;
    while (std::getline(s, line)) if (not line.empty()) break;
    if (line.empty()) return section;
    size_t n;
    std::istringstream header_line{line};
    header_line >> n;
    std::vector<std::string> headers;
    std::generate_n(
        std::back_inserter(headers),
        n,
        [&header_line](){
            std::string s;
            header_line >> std::quoted(s);
            return s;
        });
    while (std::getline(s, line)) {
        if (line.empty()) return section;
        section.push_back(read_record(line, headers));
    }
    return section;
}

File read_file(std::istream& s)
{
    File file;
    while (s) {
        file.push_back(read_section(s));
    }
    return file;
}

int main()
{
    std::istringstream input{file_contents};
    File file{read_file(input)};
    
    for (const auto& section: file) {
        std::cout << "SECTION BEGIN\n";
        for (const auto& record: section) {
            std::cout << "\tRECORD BEGIN\n";
            for (const auto& pair: record) {
                std::cout << "\t\t" << std::quoted(pair.first) << ": " << std::quoted(pair.second) << '\n';
            }
            std::cout << "\tRECORD END\n";
        }
        std::cout << "SECTION END\n";
    }
}

