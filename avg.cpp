//https://reddit.com/r/cpp_questions/comments/kygtxq/i_need_help_with_something/
//I need to create a programme with a function that counts the average of (it can be an infinite amount of numbers), and shows the result after the input is = -1 can anyone help?

#include <iostream>

int main()
{
    int count{0};
    double sum{0};
    double n;
    while (std::cin >> n) {
        if (-1 == n) break;
        ++count;
        sum += n;
    }
    std::cout << (sum / count) << '\n';
}
