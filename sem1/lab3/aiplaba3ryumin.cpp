#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
// #include <Windows.h>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "rus");
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
    string filename, extention;
    cout << "Введите путь до файла: ";
    cin >> filename;
    if (filename.size() >= 4 && filename.substr(filename.size() - 4) != ".txt") {
        cout << "Не удалось открыть файл." << endl;
        return 1;
    }
    else {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл." << endl;
            return 1;
        }

        string text, outtext = "";
        getline(file, text, '\0');

        file.close();

        for (int i = 0; i < text.length(); i += 5) {
            if ((i + 5) < text.length())
                outtext = outtext + text[i + 1] + text[i + 2] + text[i + 3] + text[i + 4] + text[i];
            else {
                for (int j = i; j < text.length(); j++)
                    outtext = outtext + text[j];
            }
        }

        cout << "Исходный текст: " << text << endl;
        cout << "Измененный текст: " << outtext << endl;

        return 0;
    }
}
