//https://reddit.com/r/cpp_questions/comments/jzd8mj/having_issues_trying_to_write_two_int_arrays_into/
/*
 * we are only allowed to have two arrays throughout the entire program.
 * The program takes two files, inputs the first 20 numbers into an array (skipping duplicate numbers), then it sorts them and pushes them to the function below to send them to a different file.
 * I've tried a few different ways of doing this but I can't seem to get if fully figured out. I keep getting close but continue to have issues. The final file can't contain any duplicate numbers either so if the two files share a number it needs to skip over it.
 */

//A quick-and-dirty poor man's static_vector.
template <typename T, size_t Size>
struct static_vector {
    std::array<std::byte, Size * sizeof(T)> buffy;
    std::pmr::monotonic_memory_resource memres(buffy);
    std::pmr::vector<T> vector(memres);

    static_vector() { vector.reserve(Size); }
    bool contains(T t) const { return vector.end() != vector.find(t); }
    void push_back(T t) { vector.push_back(t); }
    auto begin() { return vector.begin(); }
    auto end() { return vector.end(); }
    std::optional<T> get_and_inc(decltype(vector)::iterator& i)
    {
        if (vector.end() == i) return std::nullopt;
        return *i++;
    }
};

using twenty_ints = static_vector<int, 20>;

void read_ints_skip_dups(std::string_view file, twenty_ints& ns)
{
    std::ifstream in(file);
    int n;
    while ((ns.size() < 20) and (in >> n)) {
        if (not ns.contains(n)) {
            ns.push_back(n);
        }
    }
}

int main(int argc, char** argv)
{
    twenty_ints a, b;
    if (argc > 1) read_ints_skip_dups(argv[1]);
    if (argc > 2) read_ints_skip_dups(argv[2]);
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), a.end());
    auto a_iter { a.begin() };
    auto b_iter { b.begin() };
    std::optional<int> last;
    while ((a_iter != a.end()) or (b_iter != b.end())) {
        //Nope...this logic is wrong...
        auto next_a { a.get_and_inc(a_iter) };
        auto next_b { b.get_and_inc(b_iter) };
        if ((not last) and (not next_b)) std::cout << next_a;
        else if ((not last) and (not next_a)) std::cout << next_b;
        else if ((not next_b) and (last != next_a)) std::out << next_a;
        else if ((not next_a) and (last != next_b)) std::out << next_b;
    }
}
