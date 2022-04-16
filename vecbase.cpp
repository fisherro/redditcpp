//https://reddit.com/r/cpp_questions/comments/omtt7u/virtual_functions_and_inheritance/
#if 0
//Original code from post:
struct BaseClass{
    //I am sure this wont compile 
    template<typename T, typename args...>
    virtual auto func(T, args...) {}
}
struct DerivedClass1 : public BaseClass{
    //I am sure this wont compile 
    template<typename T, typename args...>
    auto func(T, args...) {}
}
struct DerivedClass2 : public BaseClass{
    //I am sure this wont compile 
    template<typename T, typename args...>
    auto func(T, args...) {}
}
struct DerivedClass3 : public BaseClass{
    //I am sure this wont compile 
    template<typename T, typename args...>
    auto func(T, args...) {}
}

int main(){
    DerivedClass1 d1;
    DerivedClass2 d2;
    DerivedClass3 d3;
    std::vector<BaseClass> all_classes{b1,b2,b3};
    for(auto x: all_classes){
        x.func(//some args)
    }
    return 0;
}
#endif

//TODO: Also do a variant version.

#include <iostream>

struct BaseClass{
    //NOTE: Templates may not be virtual!
    template<typename T, typename... args>
    virtual auto func(T t, args...) { std::cout << "BaseClass " << t << '\n'; }
}
struct DerivedClass1 : public BaseClass{
    //I am sure this wont compile 
    template<typename T t, typename... args>
    auto func(T, args...) override { std::cout << "DerivedClass1 " << t << '\n'; }
}
struct DerivedClass2 : public BaseClass{
    //I am sure this wont compile 
    template<typename T t, typename... args>
    auto func(T, args...) override { std::cout << "DerivedClass2 " << t << '\n'; }
}
struct DerivedClass3 : public BaseClass{
    //I am sure this wont compile 
    template<typename T t, typename... args>
    auto func(T, args...) override { std::cout << "DerivedClass3 " << t << '\n'; }
}

int main()
{
    DerivedClass1 d1;
    DerivedClass2 d2;
    DerivedClass3 d3;
    using ref = std::reference_wrapper<BaseClass>;
    std::vector<ref> all_classes{b1,b2,b3};
    for (auto x: all_classes) {
        x.func(x);
    }
}

