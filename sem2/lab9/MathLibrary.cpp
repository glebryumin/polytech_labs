#include "pch.h"
#include <utility>
#include "MathLibrary.h"
#include <cmath>

double ryumin_func(double x, double e) {
    double sum = 0.0;
    for (double i = 1; i < abs(round(x)); i++) {
        sum += x * (1 + i) / i;
    }
    return sum;
}

extern "C" __declspec(dllexport) double myf_math(double x, double a) {
    return (1 + x) * exp(x);
}

extern "C" __declspec(dllexport) double myf_2(double x, double a, double e) {
    return ryumin_func(x, e);
}

extern "C" __declspec(dllexport) double myf_delta(double fr, double fl) {
    return sqrt(fabs(pow(fr, 2) - pow(fl, 2)));
}

extern "C" __declspec(dllexport) void show(int code, std::vector<Set>* sets, callbackShow func) {
    if (code == cc::table) {
        func(code, sets);
    }
    else {
        if (code == cc::row) {
            func(code, sets[0]);
        }
    }
}
extern "C" __declspec(dllexport) std::string FName() {
    return "Exponential";
}