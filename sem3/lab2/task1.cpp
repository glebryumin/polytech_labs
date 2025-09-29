#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <locale>    
#include <codecvt> 

using namespace std;

class Runway {
    public:
    int length;
    int width;
    string name;
    bool isOccupied;
};


class Airport {
    private:
        vector<Runway> runways;
    public:
        void addRunway(const Runway& runway) {
            runways.push_back(runway);
        }
        void displayRunways() const {
            for (const auto& runway : runways) {
                cout << "Имя полосы: " << runway.name << ", Длина: " << runway.length 
                     << ", Ширина: " << runway.width << ", Занята: " 
                     << (runway.isOccupied ? "Да" : "Нет") << endl;
            }
        }
};

int getIntInput(string prompt, string errorMessage, int minValue = numeric_limits<int>::min(), int maxValue = numeric_limits<int>::max()) {
    int value;
    string input;
    cout << prompt << endl;
    while (true) {
        cin >> input;
        bool isValid = !input.empty() && (input[0] == '-' ? input.size() > 1 : true);
        for (size_t i = (input[0] == '-' ? 1 : 0); i < input.size(); ++i) {
            if (!isdigit(input[i])) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            try {
                size_t pos;
                value = stoi(input, &pos);
                if (pos == input.size() && value >= minValue && value <= maxValue) {
                    break;
                }
            } catch (...) {}
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage << endl;
    }
    return value;
}
string getStringInput(string prompt, string errorMessage) {
    string value;
    cout << prompt;
    cin >> value;
    while(value.empty() || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage << endl;
        cin >> value;
    }
    
    return value;
}

std::wstring toLower(const std::wstring& input) {
    std::locale loc("ru_RU.UTF-8");
    std::wstring result;
    for (wchar_t c : input) {
        result += std::use_facet<std::ctype<wchar_t>>(loc).tolower(c);
    }
    return result;
}

std::string toLowerUtf8(const std::string& input) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wide = conv.from_bytes(input);
    wide = toLower(wide);
    return conv.to_bytes(wide);
}
bool getBoolInput(string prompt, string errorMessage) {
    string value;
    cout << prompt;
    cin >> value;
    value = toLowerUtf8(value);
    while(value != "yes" && value != "no" && value != "y" && value != "n"  && value != "да" && value != "д" && value != "нет" && value != "н" || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage << endl;
        cin >> value;
        value = toLowerUtf8(value);
    }
    
    return (value == "yes" || value == "y" || value == "да" || value == "д");
}

int main() {
    Airport airport;

    Runway runway1 = {getIntInput("Введите длину взлётной полосы 1: ", "Ошибка! Попробуйте ещё раз:", 1), getIntInput("Введите ширину взлётной полосы 1: ", "Ошибка! Попробуйте ещё раз:", 1), getStringInput("Введите название полосы 1:", "Ошибка! Попробуйте ещё раз:"), getBoolInput("Полоса 1 занята? (yes/no;да/нет):", "Ошибка! Попробуйте ещё раз:")};
    cout << endl;
    Runway runway2 = {getIntInput("Введите длину взлётной полосы 2: ", "Ошибка! Попробуйте ещё раз:", 1), getIntInput("Введите ширину взлётной полосы 2: ", "Ошибка! Попробуйте ещё раз:", 1), getStringInput("Введите название полосы 2:", "Ошибка! Попробуйте ещё раз:"), getBoolInput("Полоса 2 занята? (yes/no;да/нет):", "Ошибка! Попробуйте ещё раз:")};

    airport.addRunway(runway1);
    airport.addRunway(runway2);

    airport.displayRunways();

    return 0;
}