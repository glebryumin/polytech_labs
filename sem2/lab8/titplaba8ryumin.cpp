#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <locale>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void initLocalization() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    locale::global(locale(""));
    cout.imbue(locale());
}


const vector<string> VALID_COMPONENTS = {
    "морковь", "огурцы", "помидоры", "говядина",
    "картофель", "лук", "сыр", "укроп", "масло"
};

const vector<string> VALID_PROPERTIES = {
    "вегетарианское", "кошерное", "безлактозное", "халяльное", "некошерное"
};


struct Dish {
    string name;
    vector<string> components;
    bool isVegetarian;
    bool isKosher;
    bool isLactoseFree;
    bool isHalal;

    bool operator==(const Dish& other) const {
        return name == other.name;
    }
};

class MenuDatabase {
private:

    unordered_map<size_t, vector<Dish>> componentHashTable;
    unordered_map<size_t, vector<Dish>> propertyHashTable;


    size_t getHash(const string& s) {
        return hash<string>{}(s);
    }

public:

    void addDish(const Dish& dish, const string& property) {

        for (const auto& component : dish.components) {
            size_t componentHash = getHash(component);
            componentHashTable[componentHash].push_back(dish);
        }


        size_t propertyHash = getHash(property);
        propertyHashTable[propertyHash].push_back(dish);
    }

    vector<Dish> searchDishes(const vector<string>& components, const string& property) {
        vector<Dish> result;
        if (components.empty()) return result;

        vector<size_t> componentHashes;
        for (const auto& component : components) {
            componentHashes.push_back(getHash(component));
        }
        size_t propertyHash = getHash(property);

        unordered_map<size_t, vector<Dish>> temp;
        for (auto hash : componentHashes) {
            if (componentHashTable.find(hash) == componentHashTable.end()) return {};
            temp[hash] = componentHashTable[hash];
        }

        vector<Dish> commonDishes;
        bool first = true;
        for (const auto& pair : temp) {
            if (first) {
                commonDishes = pair.second;
                first = false;
            }
            else {
                vector<Dish> intersection;
                for (const auto& dish : commonDishes) {
                    if (find(pair.second.begin(), pair.second.end(), dish) != pair.second.end()) {
                        intersection.push_back(dish);
                    }
                }
                commonDishes = intersection;
            }
        }

        if (propertyHashTable.find(propertyHash) == propertyHashTable.end()) return {};
        const auto& propertyDishes = propertyHashTable[propertyHash];

        for (const auto& dish : commonDishes) {
            if (find(propertyDishes.begin(), propertyDishes.end(), dish) != propertyDishes.end()) {
                result.push_back(dish);
            }
        }

        return result;
    }
};


template<typename T>
void printNumberedList(const vector<T>& items) {
    for (size_t i = 0; i < items.size(); ++i) {
        cout << "  " << (i + 1) << ". " << items[i] << endl;
    }
}
vector<string> inputComponents() {
    while (true) {
        cout << "Выберите компоненты (1-" << VALID_COMPONENTS.size() << "):" << endl;
        for (size_t i = 0; i < VALID_COMPONENTS.size(); ++i) {
            cout << "  " << (i + 1) << ". " << VALID_COMPONENTS[i] << endl;
        }

        cout << "Введите номера через запятую (1-3 компонента): ";
        string input;
        getline(cin, input);


        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

        vector<int> choices;
        stringstream ss(input);
        string token;
        bool hasError = false;

        while (getline(ss, token, ',')) {
            if (token.empty()) {
                cout << "Ошибка: пустой элемент!" << endl;
                hasError = true;
                break;
            }

            if (token.find_first_not_of("0123456789") != string::npos) {
                cout << "Ошибка: '" << token << "' не является числом!" << endl;
                hasError = true;
                break;
            }

            try {
                int num = stoi(token);
                if (num < 1 || num > VALID_COMPONENTS.size()) {
                    cout << "Ошибка: номер " << num << " вне диапазона!" << endl;
                    hasError = true;
                    break;
                }
                choices.push_back(num - 1);
            }
            catch (...) {
                cout << "Ошибка: недопустимый ввод!" << endl;
                hasError = true;
                break;
            }
        }

        if (hasError) {
            cout << "Попробуйте снова." << endl << endl;
            continue;
        }

        if (choices.empty() || choices.size() > 3) {
            cout << "Ошибка: выберите от 1 до 3 компонентов!" << endl << endl;
            continue;
        }


        sort(choices.begin(), choices.end());
        choices.erase(unique(choices.begin(), choices.end()), choices.end());

        vector<string> components;
        for (int idx : choices) {
            components.push_back(VALID_COMPONENTS[idx]);
        }

        return components;
    }
}

string inputProperty() {
    while (true) {
        cout << "Выберите свойство:" << endl;
        for (size_t i = 0; i < VALID_PROPERTIES.size(); ++i) {
            cout << "  " << (i + 1) << ". " << VALID_PROPERTIES[i] << endl;
        }

        cout << "Введите номер: ";
        string input;
        getline(cin, input);

        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

        if (input.empty() || input.find_first_not_of("0123456789") != string::npos) {
            cout << "Ошибка: введите число!" << endl << endl;
            continue;
        }

        try {
            int num = stoi(input);
            if (num < 1 || num > VALID_PROPERTIES.size()) {
                cout << "Ошибка: недопустимый номер!" << endl << endl;
                continue;
            }
            return VALID_PROPERTIES[num - 1];
        }
        catch (...) {
            cout << "Ошибка: недопустимый ввод!" << endl << endl;
        }
    }
}

int main() {
    initLocalization();

    MenuDatabase db;

    Dish dish1{ "Овощной салат", {"ab", "ab", "помидоры"}, true, true, true, true };
    db.addDish(dish1, "вегетарианское");

    Dish dish2{"Винегрет", {"картофель", "морковь", "огурцы"}, true, true, true, true};
    db.addDish(dish2, "вегетарианское");

    Dish dish3{ "Жаркое", {"говядина", "картофель", "лук"}, false, true, true, true };
    db.addDish(dish3, "некошерное");

    Dish dish4{ "Гуляш", {"говядина", "лук", "помидоры"}, false, true, true, true };
    db.addDish(dish4, "некошерное");

    Dish dish5{ "Сырная тарелка", {"сыр", "укроп", "масло"}, true, false, false, true };
    db.addDish(dish5, "кошерное");

    Dish dish6{ "Гренки", {"сыр", "помидоры", "лук"}, true, false, false, true };
    db.addDish(dish6, "безлактозное");

    Dish dish7{ "Рулетики из огурцов", {"огурцы", "сыр", "укроп"}, true, true, false, true };
    db.addDish(dish7, "вегетарианское");

    Dish dish8{ "Фаршированные помидоры", {"помидоры", "сыр", "лук"}, true, true, false, true };
    db.addDish(dish8, "вегетарианское");

    Dish dish9{ "Картофель фри", {"картофель", "масло", "укроп"}, true, true, true, true };
    db.addDish(dish9, "вегетарианское");

    Dish dish10{ "Тушёные овощи", {"морковь", "лук", "масло"}, true, true, true, true };
    db.addDish(dish10, "вегетарианское");

    Dish dish11{ "Овощной суп", {"картофель", "морковь", "укроп"}, true, true, true, true };
    db.addDish(dish11, "вегетарианское");

    Dish dish12{ "Харчо", {"говядина", "рис", "помидоры"}, false, true, true, true };
    db.addDish(dish12, "некошерное");

    Dish dish13{ "Морковные оладьи", {"морковь", "масло", "лук"}, true, true, true, true };
    db.addDish(dish13, "вегетарианское");

    Dish dish14{ "Сырный суп", {"сыр", "картофель", "укроп"}, true, false, false, true };
    db.addDish(dish14, "кошерное");

    Dish dish15{ "Мясная запеканка", {"говядина", "сыр", "лук"}, false, false, false, true };
    db.addDish(dish15, "халяльное");

    while (true) {
        vector<string> components = inputComponents();
        string property = inputProperty();

        vector<Dish> results = db.searchDishes(components, property);

        if (results.empty()) {
            cout << "Блюд по вашему запросу не найдено." << endl;
        }
        else {
            cout << endl << "Найдены блюда:" << endl;
            for (const auto& dish : results) {
                cout << "-> " << dish.name << " (";
                for (const auto& c : dish.components) cout << c << " ";
                cout << ")" << endl;
            }
        }

        cout << endl << "Продолжить поиск? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (tolower(choice) != 'y') break;
    }
    return 0;
}