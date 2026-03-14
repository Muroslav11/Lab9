#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Route {
    string startPoint;
    string endPoint;
    int routeNumber;
};


int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(10000, '\n');
            return value;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка: введіть коректне ціле число.\n";
    }
}

string getValidString(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void inputRoutes(Route* arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << "\n--- Маршрут #" << i + 1 << " ---\n";
        arr[i].startPoint = getValidString("Початковий пункт: ");
        arr[i].endPoint = getValidString("Кінцевий пункт: ");
        arr[i].routeNumber = getValidInt("Номер маршруту: ");
    }
}

void printRoutes(const Route* arr, int size) {
    if (size <= 0 || arr == nullptr) {
        cout << "\nМасив порожній.\n";
        return;
    }
    cout << "\n" << string(65, '-') << "\n";
    cout << "| " << setw(5) << left << "№"
        << "| " << setw(20) << left << "Початковий пункт"
        << "| " << setw(20) << left << "Кінцевий пункт"
        << "| " << setw(10) << left << "Маршрут" << "|\n";
    cout << string(65, '-') << "\n";

    for (int i = 0; i < size; ++i) {
        cout << "| " << setw(5) << left << i + 1
            << "| " << setw(20) << left << arr[i].startPoint
            << "| " << setw(20) << left << arr[i].endPoint
            << "| " << setw(10) << left << arr[i].routeNumber << "|\n";
    }
    cout << string(65, '-') << "\n";
}

void sortRoutesByNumber(Route* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j].routeNumber > arr[j + 1].routeNumber) {
                Route temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int findRouteIndex(const Route* arr, int size, int target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i].routeNumber == target) {
            return i;
        }
    }
    return -1;
}

bool saveToFile(const Route* arr, int size, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) return false;

    fout << size << "\n";
    for (int i = 0; i < size; ++i) {
        fout << arr[i].startPoint << "\n"
            << arr[i].endPoint << "\n"
            << arr[i].routeNumber << "\n";
    }
    fout.close();
    return true;
}

Route* loadFromFile(const string& filename, int& outSize) {
    ifstream fin(filename);
    if (!fin.is_open()) return nullptr;

    if (!(fin >> outSize)) return nullptr;
    fin.ignore();

    Route* newArr = new Route[outSize];
    for (int i = 0; i < outSize; ++i) {
        getline(fin, newArr[i].startPoint);
        getline(fin, newArr[i].endPoint);
        fin >> newArr[i].routeNumber;
        fin.ignore();
    }
    fin.close();
    return newArr;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Route* routes = nullptr;
    int size = 0;
    int choice;

    do {
        cout << "\n========== ГОЛОВНЕ МЕНЮ (Варіант 10) ==========\n";
        cout << "1. Створити масив маршрутів\n";
        cout << "2. Вивести всі маршрути\n";
        cout << "3. Сортувати за номерами маршрутів\n";
        cout << "4. Пошук маршруту за номером\n";
        cout << "5. Зберегти у файл\n";
        cout << "6. Зчитати з файлу\n";
        cout << "0. Вихід\n";
        choice = getValidInt("Оберіть дію: ");

        switch (choice) {
        case 1: {
            int n = getValidInt("Введіть кількість маршрутів: ");
            if (n > 0) {
                if (routes != nullptr) delete[] routes;
                size = n;
                routes = new Route[size];
                inputRoutes(routes, size);
                cout << "Дані успішно введено.\n";
            }
            break;
        }
        case 2:
            printRoutes(routes, size);
            break;
        case 3:
            if (size > 0) {
                sortRoutesByNumber(routes, size);
                cout << "Масив відсортовано.\n";
            }
            else cout << "Масив порожній.\n";
            break;
        case 4: {
            if (size > 0) {
                int target = getValidInt("Введіть номер маршруту для пошуку: ");
                int index = findRouteIndex(routes, size, target);
                if (index != -1) {
                    cout << "\nМаршрут знайдено:\n";
                    cout << "Початковий пункт: " << routes[index].startPoint << endl;
                    cout << "Кінцевий пункт:   " << routes[index].endPoint << endl;
                    cout << "Номер маршруту:   " << routes[index].routeNumber << endl;
                }
                else {
                    cout << "Маршрут з номером " << target << " не знайдено.\n";
                }
            }
            else cout << "Масив порожній.\n";
            break;
        }
        case 5: {
            if (size > 0) {
                string fname = getValidString("Введіть ім'я файлу для запису: ");
                if (saveToFile(routes, size, fname)) cout << "Файл збережено.\n";
                else cout << "Помилка запису.\n";
            }
            else cout << "Немає даних для запису.\n";
            break;
        }
        case 6: {
            string fname = getValidString("Введіть ім'я файлу для зчитування: ");
            int newSize = 0;
            Route* loaded = loadFromFile(fname, newSize);
            if (loaded) {
                if (routes != nullptr) delete[] routes;
                routes = loaded;
                size = newSize;
                cout << "Дані завантажено.\n";
            }
            else cout << "Файл не знайдено або порожній.\n";
            break;
        }
        }
    } while (choice != 0);

    if (routes != nullptr) delete[] routes;
    return 0;
}