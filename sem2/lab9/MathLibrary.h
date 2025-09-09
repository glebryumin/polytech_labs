#pragma once
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <limits>
#include <string>
#include <vector>

typedef void (*callbackShow)(int, ...);

namespace cc {
    const int len_val{ 14 };
    const std::string chars_value("+-.0123456789");
    const std::string chars_step(".0123456789");
    const int dp{ 12 };
    const double err{ std::numeric_limits<double>::infinity() };
    const int table{ 1 };
    const int row{ 2 };
}

struct Set {
    std::string e, x, fr, fl, d;
    Set() = default;
    Set(std::string e_, std::string x_, std::string fr_, std::string fl_, std::string d_)
        : e(e_), x(x_), fr(fr_), fl(fl_), d(d_) {
    }
};

// Переименованная функция
extern "C" MATHLIBRARY_API double myf_2(double x, double a, double e);
extern "C" MATHLIBRARY_API double myf_math(double x, double a);
extern "C" MATHLIBRARY_API double myf_delta(double fr, double fl);
extern "C" MATHLIBRARY_API void show(int code, std::vector<Set>* sets, callbackShow func);
extern "C" MATHLIBRARY_API char* FName();