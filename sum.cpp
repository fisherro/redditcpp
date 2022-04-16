//https://reddit.com/r/cpp_questions/comments/k0bo1a/reading_numbers_from_a_file_and_find_the_sum/
//"I'm assigned to read the console input and create a file.txt, close the file after I have created it, then open the file in read mode and print out the sum of numbers in the file."
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>

int main()
{
    {
        std::ofstream out("file.txt");
        out << std::cin.rdbuf();
    }
    std::ifstream in("file.txt");
    std::cout << std::accumulate(std::istream_iterator<int>(in), std::istream_iterator<int>(), 0) << '\n';
}
