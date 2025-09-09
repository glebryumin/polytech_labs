#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

int getValidatedInput(const string& prompt, int minVal, int maxVal) {
    int value;
    bool isValid = false;

    do {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                isValid = true;
            }
            else {
                cout << "Ошибка: значение должно быть между "
                    << minVal << " и " << maxVal << "!\n";
            }
        }
        else {
            cout << "Ошибка: введено некорректное значение!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!isValid);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Функция для сортировки цифр числа по убыванию
int sortDigitsDesc(int num) {
    bool isNegative = num < 0;
    num = abs(num);
    vector<int> digits;
    if (num == 0) {
        digits.push_back(0);
    }
    else {
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }
    sort(digits.rbegin(), digits.rend());
    int result = 0;
    for (int d : digits) {
        result = result * 10 + d;
    }
    return isNegative ? -result : result;
}

// Обработка всей матрицы
vector<vector<int>> processMatrix(const vector<vector<int>>& original) {
    vector<vector<int>> processed = original;
    for (auto& row : processed) {
        for (auto& num : row) {
            num = sortDigitsDesc(num);
        }
    }
    return processed;
}

// Функция сравнения строк
bool isLess(const vector<int>& a, const vector<int>& b) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return false;
}

// Методы сортировки с подсчётом операций
void bubbleSort(vector<vector<int>>& matrix, int& comparisons, int& swaps) {
    int n = matrix.size();
    comparisons = swaps = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            comparisons++;
            if (isLess(matrix[j + 1], matrix[j])) {
                swaps++;
                swap(matrix[j], matrix[j + 1]);
            }
        }
    }
}

void selectionSort(vector<vector<int>>& matrix, int& comparisons, int& swaps) {
    int n = matrix.size();
    comparisons = swaps = 0;
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            comparisons++;
            if (isLess(matrix[j], matrix[minIdx])) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swaps++;
            swap(matrix[i], matrix[minIdx]);
        }
    }
}

void insertionSort(vector<vector<int>>& matrix, int& comparisons, int& swaps) {
    int n = matrix.size();
    comparisons = swaps = 0;
    for (int i = 1; i < n; ++i) {
        int j = i;
        while (j > 0) {
            comparisons++;
            if (isLess(matrix[j], matrix[j - 1])) {
                swaps++;
                swap(matrix[j], matrix[j - 1]);
                j--;
            }
            else break;
        }
    }
}

void shellSort(vector<vector<int>>& matrix, int& comparisons, int& swaps) {
    int n = matrix.size();
    comparisons = swaps = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            auto temp = matrix[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                comparisons++;
                if (isLess(temp, matrix[j - gap])) {
                    swaps++;
                    matrix[j] = matrix[j - gap];
                }
                else break;
            }
            matrix[j] = temp;
        }
    }
}

int partition(vector<vector<int>>& matrix, int low, int high, int& comp, int& swp) {
    auto pivot = matrix[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        comp++;
        if (isLess(matrix[j], pivot)) {
            i++;
            swp++;
            swap(matrix[i], matrix[j]);
        }
    }
    comp++;
    if (isLess(matrix[high], matrix[i + 1])) {
        swp++;
        swap(matrix[i + 1], matrix[high]);
    }
    return i + 1;
}

void quickSortHelper(vector<vector<int>>& matrix, int low, int high, int& comp, int& swp) {
    if (low < high) {
        int pi = partition(matrix, low, high, comp, swp);
        quickSortHelper(matrix, low, pi - 1, comp, swp);
        quickSortHelper(matrix, pi + 1, high, comp, swp);
    }
}

void quickSort(vector<vector<int>>& matrix, int& comp, int& swp) {
    comp = swp = 0;
    quickSortHelper(matrix, 0, matrix.size() - 1, comp, swp);
}

// Генерация матрицы
vector<vector<int>> generateMatrix(int rows, int cols, int minVal, int maxVal) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (auto& row : matrix) {
        for (auto& num : row) {
            num = rand() % (maxVal - minVal + 1) + minVal;
        }
    }
    return matrix;
}

// Вывод матрицы
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int num : row) {
            cout << num << "\t";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    const int MIN = 1000, MAX = 9999;

    // Ввод размеров матрицы
    cout << "Введите параметры матрицы:\n";
    int ROWS = getValidatedInput("Количество строк (1-99): ", 1, 99);
    int COLS = getValidatedInput("Количество столбцов (1-99): ", 1, 99);

    // Генерация и вывод исходной матрицы
    auto original = generateMatrix(ROWS, COLS, MIN, MAX);
    cout << "\nOriginal matrix:\n";
    printMatrix(original);
    cout << "\n";

    // Обработка чисел
    auto processed = processMatrix(original);

    // Применение сортировок
    vector<vector<vector<int>>> matrices(5, processed);

    vector<pair<string, pair<int, int>>> results;

    // Bubble Sort
    int comp = 0, swp = 0;
    bubbleSort(matrices[0], comp, swp);
    results.push_back({ "Bubble", {comp, swp} });

    // Selection Sort
    comp = swp = 0;
    selectionSort(matrices[1], comp, swp);
    results.push_back({ "Selection", {comp, swp} });

    // Insertion Sort
    comp = swp = 0;
    insertionSort(matrices[2], comp, swp);
    results.push_back({ "Insertion", {comp, swp} });

    // Shell Sort
    comp = swp = 0;
    shellSort(matrices[3], comp, swp);
    results.push_back({ "Shell", {comp, swp} });

    // Quick Sort
    comp = swp = 0;
    quickSort(matrices[4], comp, swp);
    results.push_back({ "Quick", {comp, swp} });

    // Вывод результатов
    vector<string> names = { "Bubble", "Selection", "Insertion", "Shell", "Quick" };
    for (size_t i = 0; i < matrices.size(); ++i) {
        cout << "After " << names[i] << " Sort:\n";
        printMatrix(matrices[i]);
        cout << "Comparisons: " << results[i].second.first
            << ", Swaps: " << results[i].second.second << "\n\n";
    }

    // Сравнительная таблица
    cout << "Comparison Table:\n"
        << left << setw(12) << "Method"
        << setw(12) << "Comparisons" << "Swaps\n";
    for (const auto& [method, stats] : results) {
        cout << setw(12) << method
            << setw(12) << stats.first << stats.second << "\n";
    }

    return 0;
}