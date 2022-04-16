//https://reddit.com/r/cpp_questions/comments/r0kmts/concurrency_in_c/
/******************************************************************************
 * For your project, you will demonstrate an understanding of the various
 * concepts discussed in each module. For the second part of your Portfolio
 * Project, you will create a Java application that will exhibit concurrency
 * concepts. Your application should create two threads that will act as
 * counters. One thread should count up to 20. Once thread one reaches 20,
 * then a second thread should be used to count down to 0. For your created
 * code, please be provide a detailed analysis of appropriate concepts that
 * could impact your application.
 ******************************************************************************/
#include <iostream>
#include <future>

    int count_up()
    {
        std::cout << __func__ << " thread ID: " << std::this_thread::get_id() << '\n';
        int i{0};
        while (i < 20) ++i;
        return i;
    }

    int count_down(std::future<int> f)
    {
        std::cout << __func__ << " thread ID: " << std::this_thread::get_id() << '\n';
        int i{f.get()};
        std::cout << __func__ << " i = " << i << '\n';
        while (i > 0) --i;
        return i;
    }

    int main()
    {
#if 1
        std::future<int> f1 { std::async(std::launch::async, count_up) };
        std::future<int> f2 { std::async(std::launch::async, count_down, std::move(f1)) };
        std::cout << f2.get() << '\n';
#else
        std::cout << __func__ << " thread ID: " << std::this_thread::get_id() << '\n';
        std::future<int> f {
            std::async(
                    std::launch::async,
                    count_down,
                    std::async(std::launch::async, count_up))
        };
        std::cout << f.get() << '\n';
#endif
    }

