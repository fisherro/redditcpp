//https://reddit.com/r/cpp_questions/comments/k6fdbq/how_do_i_store_a_value_solved_in_a_void_function/
    #include <algorithm>
    #include <iostream>
    #include <iterator>

    struct ratio {
        int num = 0;
        int den = 1;
    };

    ratio lowest_term(ratio r)
    {
        for (int i = r.den; i >= 2; --i) {
            if ((r.num % i) == 0 and (r.den % i) == 0) {
                r.num /= i;
                r.den /= i;
            }
        }
        return r;
    }

    int main()
    {
        ratio ins[]{{2,4},{3,9}};
        ratio outs[std::size(ins)];
        std::transform(std::begin(ins), std::end(ins), outs, lowest_term);
        for (const auto& r: outs) {
            std::cout << r.num << '/' << r.den << '\n';
        }
    }
