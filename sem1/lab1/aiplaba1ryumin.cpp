#include <iostream>
#include <math.h>
#include <iomanip>

// 26

using namespace std;
double x, y, a;
int counter = 0;

double f(double x, double a) {
    if (a == NULL) return NULL;
    if(((x / 2) + a) > 1 || ((x / 2) + a) < -1 || (0.2 * a) < 0 || sqrt((0.2 * a) + cos((x / 2) + a)) == 0)
        return NULL;
    return (2 * x) / sqrt((0.2 * a) + cos((x / 2) + a));
    
}


int main()
{
    cout << "Enter a:";
    if (!(cin >> a)) 
        a = NULL;
    else {
        if ((!(-1000000.000001 <= a <= 1000000.000001)) || (a >= -0.0000001 && a <= 0.0000001))
                a = NULL;
            
    }

    for (int i = 0; i < 105; i++)
        cout << "-";
    cout << endl;

    cout << "|" << "  N  " << "|" << "\t" << setw(10) << "X  " << "\t" << "|" << "\t" << setw(40) << "a" << "\t" << "|" << "\t" << setw(10) << "y" << "\t" << "|" << endl;

    for (int i = 0; i < 105; i++)
        cout << "-";
    cout << endl;


    for (x = -0.9; x <= 4.1; x += 0.5) {
        counter++;
        y = f(x, a);
        if (y == NULL)
            cout << fixed << "|" << setw(5) << counter << "|" << '\t' << setw(10) << x << "\t" << "|" << "\t" << setw(40) << a << "\t" << "|" << '\t' << setw(10) << "Can`t calcualte" << '\t' << "|" << endl;
        else
            cout << fixed << "|" << setw(5) << counter << "|" << "\t" << setw(10) << x << "\t" << "|" << "\t" << setw(40) << a << "\t" << "|" << '\t' << setw(10) << y << '\t' << "|" << endl;
    }

    for (int i = 0; i < 105; i++)
        cout << "-";
    cout << endl;

    return 0;
}
