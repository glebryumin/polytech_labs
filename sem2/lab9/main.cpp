#define NOMINMAX
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <locale>
#include <clocale>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

#include "MathLibrary.h"

void __stdcall ShowTable(int code, ...) {
    va_list args;
    va_start(args, code);

    const string inf_str = to_string(numeric_limits<double>::infinity());
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
    if (code == cc::table) {
        vector<Set>* sets = va_arg(args, vector<Set>*);
        cout << string(120, '-') << endl;
        cout << "|" << setw(22) << "X"
            << "|" << setw(31) << "f(X)"
            << "|" << setw(31) << "F(X)"
            << "|" << setw(31) << "delta"
            << "|" << endl;
        cout << string(120, '-') << endl;

        for (const auto& set : *sets) {
            bool fr_inf = (set.fr == inf_str);
            bool fl_inf = (set.fl == inf_str);

            cout << "|" << setw(22) << set.x
                << "|" << setw(31) << (fr_inf ? "error" : set.fr)
                << "|" << setw(31) << (fl_inf ? "error" : set.fl)
                << "|" << setw(31) << (fr_inf || fl_inf ? "error" : set.d)
                << "|" << endl;
        }
        cout << string(120, '-') << endl;
    }
    else if (code == cc::row) {
        Set* set = va_arg(args, Set*);
        bool fr_inf = (set->fr == inf_str);
        bool fl_inf = (set->fl == inf_str);
        if (set->fr.c_str() == "inf" && set->fl.c_str() == "inf")
            cout << "|" << setw(22) << set->x
            << "|" << setw(31) << (fr_inf ? "error" : set->fr)
            << "|" << setw(31) << (fl_inf ? "error" : set->fl)
            << "|" << setw(31) << (fr_inf || fl_inf ? "error" : set->d)
            << "|" << endl;
    }
    SetConsoleTextAttribute(hConsole,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
    );
    va_end(args);
}

template <typename T>
T safe_input(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);

        if (input.empty()) {
            cerr << "Ошибка: Пустой ввод!" << endl;
            continue;
        }

        bool is_valid = true;
        for (char c : input) {
            if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
                is_valid = false;
                break;
            }
        }

        if (!is_valid) {
            cerr << "Ошибка: Недопустимые символы!" << endl;
            continue;
        }

        istringstream iss(input);
        if (iss >> value) {
            return value;
        }
        else {
            cerr << "Ошибка: Некорректный формат!" << endl;
        }
    }
}

int input_epsilon() {
    int epsilon_power;
    while (true) {
        epsilon_power = safe_input<int>("Введите степень точности E (1-12): ");
        if (epsilon_power >= 1 && epsilon_power <= 12) {
            return epsilon_power;
        }
        else {
            cerr << "Ошибка: Степень должна быть от 1 до 12!" << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    HINSTANCE hDLL = LoadLibrary(TEXT("MathLibrary.dll"));
    if (!hDLL) {
        cerr << "Ошибка загрузки DLL!" << endl;
        return 1;
    }

    // Получение функций с проверкой
    auto myf_series = reinterpret_cast<double(*)(double, double, double)>(GetProcAddress(hDLL, "myf_2"));
    auto myf_math = reinterpret_cast<double(*)(double, double)>(GetProcAddress(hDLL, "myf_math"));
    auto delta = reinterpret_cast<double(*)(double, double)>(GetProcAddress(hDLL, "myf_delta"));
    auto show = reinterpret_cast<void(*)(int, const vector<Set>&, callbackShow)>(GetProcAddress(hDLL, "show"));
    auto FName = reinterpret_cast<std::string(*)()>(GetProcAddress(hDLL, "FName"));

    if (!myf_series || !myf_math || !delta || !show) {
        cerr << "Ошибка загрузки функций из DLL!" << endl;
        FreeLibrary(hDLL);
        return 1;
    }


    double x_start = safe_input<double>("Введите начальную границу x_start: ");
    while (x_start > pow(10, 12) || -pow(10, 12) > x_start) {
        cout << "Ошибка: введите значение из диапазона (-10^12;10^12)!" << endl;
        x_start = safe_input<double>("Введите начальную границу x_start: ");
    }
    double x_end = safe_input<double>("Введите конечную границу x_end: ");
    while (x_end > pow(10, 12) || -pow(10, 12) > x_end || x_end < x_start) {
        cout << "Ошибка: введите значение из диапазона (-10^12;10^12), меньшее, чем x_start!" << endl;
        x_end = safe_input<double>("Введите начальную границу x_end: ");
    }
    double step = safe_input<double>("Введите шаг step: ");
    while (step > pow(10, 12) || step < 0) {
        cout << "Ошибка: введите значение из диапазона (0;10^12)!" << endl;
        step = safe_input<double>("Введите шаг step: ");
    }
    vector<Set> table1;
    for (double x = x_start; x <= x_end; x += step) {
        double fr = myf_series(x, 0, 7);
        double fl = myf_math(x, 0);
        table1.push_back({
            to_string(7),
            to_string(x),
            to_string(fr),
            to_string(fl),
            to_string(delta(fr, fl))
            });
    }

    cout << endl << FName() << endl;
    show(cc::table, table1, ShowTable);

    int epsilon = input_epsilon();
    double x_ideal = safe_input<double>("Введите x_ideal: ");
    while (x_ideal > pow(10, 12) || -pow(10, 12) > x_ideal) {
        cout << "Ошибка: введите значение из диапазона (-10^12;10^12)!" << endl;
        x_ideal = safe_input<double>("Введите начальную границу x_ideal: ");
    }
    vector<Set> table2;
    for (int i = 0; i < epsilon; ++i) {
        double e = pow(10, -i);
        double fr = myf_series(x_ideal, 0, e) * e;
        double fl = myf_math(x_ideal, 0) * e;
        table2.push_back({
            to_string(e),
            to_string(x_ideal),
            to_string(fr),
            to_string(fl),
            to_string(delta(fr, fl))
            });
    }

    show(cc::table, table2, ShowTable);

    FreeLibrary(hDLL);
    return 0;
}