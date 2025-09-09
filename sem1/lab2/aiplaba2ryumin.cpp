#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

bool isValid(double value) {
    return (value >= 0.0 && value <= 1.0);
}

int main() {
    setlocale(LC_CTYPE, "rus");
    double C, M, Y, K;
    int R, G, B;

    while (true) {
        cout << "Введите значения CMYK в диапозоне [0, 1]:" << endl;
        cout << "C: ";
        cin >> C;
        if (!isValid(C))
            goto cond;
        cout << "M: ";
        cin >> M;
        if (!isValid(M))
            goto cond;
        cout << "Y: ";
        cin >> Y;
        if (!isValid(Y))
            goto cond;
        cout << "K: ";
        cin >> K;
        if (!isValid(K))
            goto cond;

        cond:
        if (!cin || !isValid(C) || !isValid(M) || !isValid(Y) || !isValid(K)) {
            cout << "Ошибка: введённые значения не принадлежат диапозоны [0, 1]." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        R = round((255 * (1 - C) * (1 - K)));
        G = round((255 * (1 - M) * (1 - K)));
        B = round((255 * (1 - Y) * (1 - K)));
        cout << "RGB: (" << R << ", " << G << ", " << B << ")" << endl;
        break; 
    }

    return 0;
}
