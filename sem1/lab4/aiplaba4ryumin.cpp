#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

long double f(long double x) {
    return pow(tan((3.14159 * x) / 2), 2);
}


long double F(long double x) {
    return ((18 * pow(x, 2) - pow(x, 4)) / (-1 * pow(x, 6) + 20 * pow(x, 4) - 117 * pow(x, 2) + 162));
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    int numbersAfterDot = 0;
    long double xStart = 0.0, xEnd = 0.0, xDelta = 0.0, sigma = 0.0, xIdeal = 0.0, accuracy = 0;
    cout << "Введите Эпсилон (количество знаков после запятой, натуральное значение):";
    cin >> numbersAfterDot;
    while (cin.fail() || numbersAfterDot <= 0 || numbersAfterDot > 10) {
        cout << "Ошибка! Некорректное значение, введите корректное значение:";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> numbersAfterDot;
    }
    accuracy = pow(10, -1 * numbersAfterDot);
    cout.precision(numbersAfterDot);

    cout << "Введите Xstart:";
    cin >> xStart;
    while (cin.fail() || (abs(xStart) < accuracy && xStart != 0)) {
        cout << "Ошибка! Некорректное значение, введите корректное значение:";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> xStart;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Введите Xend:";
    cin >> xEnd;
    while (cin.fail() || (abs(xEnd) < accuracy && xEnd != 0) || xEnd <= xStart) {
        cout << "Ошибка! Некорректное значение, введите корректное значение:";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> xEnd;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Введите Xdelta:";
    cin >> xDelta;
    while (cin.fail() || (abs(xDelta) < accuracy && xDelta != 0) || xDelta > (xEnd - xStart) || ((static_cast<int>(xEnd - xStart) * numbersAfterDot) % static_cast<int>(xDelta * numbersAfterDot)) != 0) {
        cout << "Ошибка! Некорректное значение, введите корректное значение:";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> xDelta;
    }

    for (int i = 0; i < 120; i++) {
        cout << "-";
    }
    cout << endl;

    cout << "|" << setw(22) << "X"  << "|" << setw(31) << "f(x)"  << "|" << setw(31) << "F(x)"  << "|" << setw(31) << "sigma"  << "|" << endl;

    for (int i = 0; i < 120; i++) {
        cout << "-";
    }
    cout << endl;

    for (long double x = xStart; x <= xEnd; x += xDelta) {
        if ((-1 * pow(x, 6) + 20 * pow(x, 4) - 117 * pow(x, 2) + 162) == 0)
            cout << fixed << "|" << setw(22) << x << "|" << setw(31) << f(x) << "|" << setw(31) << "Error" << "|" << setw(31) << "Error" << "|" << endl;
        else 
            cout << fixed << "|" << setw(22) << x << "|" << setw(31) << f(x) << "|" << setw(31) << F(x) << "|" << setw(31) << sqrt(abs(pow(f(x), 2) -pow(F(x), 2))) << "|" << endl;
    }
    for (int i = 0; i < 120; i++) {
        cout << "-";
    }
    cout << endl;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Введите Xideal:";
    cin >> xIdeal;
    while (cin.fail() || (abs(xIdeal) < accuracy)) {
        cout << "Ошибка! Некорректное значение, введите корректное значение:";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> xIdeal;
    }

    for (int i = 0; i < 120; i++) {
        cout << "-";
    }
    cout << endl;

    cout << "|" << setw(22) << "Epsilon" << "|" << setw(31) << "f(Xideal)" << "|" << setw(31) << "F(Xideal)" << "|" << setw(31) << "sigma" << "|" << endl;

    for (int i = 0; i < 120; i++) {
        cout << "-";
    }
    cout << endl;

    for (int epsilon = 1; epsilon <= 7; epsilon++) {
        cout.precision(epsilon);
        cout << fixed << "|" << setw(22) << pow(10, -1 * epsilon) << "|" << setw(31) << f(xIdeal) << "|" << setw(31) << F(xIdeal) << "|" << setw(31) << sqrt(abs(pow(f(xIdeal), 2) - pow(F(xIdeal), 2))) << "|" << endl;
    }

    for (int i = 0; i < 120; i++) {
        cout << "-";
    }
    cout << endl;
    return 0;
}
