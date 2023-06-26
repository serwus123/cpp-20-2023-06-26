#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std::literals;

void print(const auto& c, std::string_view prefix = "items")
{
    std::cout << prefix << ": [ ";
    for(const auto& item : c)
        std::cout << item << " ";
    std::cout << "]\n";
}

bool cmp_by_size(const auto& a, const auto& b)
{
    return a.size() < b.size();
}

auto cmp_by_size_lambda_20 = [](const auto& l, const auto& r) {
    return l.size() < r.size();
};

namespace Explain
{
    template <typename T1, typename T2> 
    bool cmp_by_size(const T1& a, const T2& b)
    {
        return a.size() < b.size();
    } 

    struct Lambda_47623542376
    {
        template <typename T1, typename T2> 
        auto operator()(const T1& a, const T2& b) const
        {
            return a.size() < b.size();
        } 
    };

    template <typename TRange, typename TComparer>
    void sort(TRange&& rng, TComparer comp)
    {
        // comp(a, b)
    }
}

bool foo(int) { return true; }
bool foo(double ) { return true; }

template <typename F, typename... TArgs>
decltype(auto) call_wrapper(F f, TArgs&&... args)
{
    std::cout << "calling a function!!!" << std::endl;

    return f(std::forward<TArgs>(args)...); // perfect forwarding
}

namespace Cpp20
{
    decltype(auto) call_wrapper(auto f, auto&&... args)
    {
        std::cout << "calling a function!!!" << std::endl;

        return f(std::forward<decltype(args)>(args)...); // perfect forwarding
    }
}

TEST_CASE("abbreviated template syntax")
{
    auto my_cmp_less = [](auto x, auto y) {
        return std::cmp_less(x, y);
    };

    std::string str = "abc";
    std::vector vec = {1, 2, 3, 4};

    CHECK(cmp_by_size(str, vec));
    //CHECK(cmp_by_size(str, 5)); // ERROR - int has no size()


    std::vector<std::string> words = {"twenty-two", "zero", "one", "two", "three", "four"};

    std::ranges::sort(words, cmp_by_size_lambda_20);
    std::ranges::sort(words, cmp_by_size<std::string, std::string>);

    std::vector<int> numbers{1, 2, 3, 4};
    std::ranges::all_of(numbers, [](auto n) { return foo(n); });
}