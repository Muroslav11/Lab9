#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cmath>

using namespace std;

enum Specialty { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, LABOR_TRAINING };

struct Student {
    string lastName;
    int course;
    Specialty specialty;
    int physics;
    int math;
    int informatics;
};

string getSpecName(Specialty s) {
    switch (s) {
    case COMPUTER_SCIENCE:    return "Комп'ютерні науки";
    case INFORMATICS:         return "Інформатика";
    case MATH_ECONOMICS:      return "Математика та економіка";
    case PHYSICS_INFORMATICS: return "Фізика та інформатика";
    case LABOR_TRAINING:      return "Трудове навчання";
    default:                  return "Невідома";
    }
}

double GetAverageGrade(const Student& s) {
    return (s.physics + s.math + s.informatics) / 3.0;
}

bool IsBetter(const Student& a, const Student& b, bool reverseName = true) {
    double avgA = GetAverageGrade(a);
    double avgB = GetAverageGrade(b);

    if (abs(avgA - avgB) > 1e-9) return avgA < avgB; 
    if (a.course != b.course) return a.course < b.course;

    if (reverseName) return a.lastName > b.lastName; 
    else return a.lastName < b.lastName; 
}

int getValidInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt; cin >> value;
        if (cin.fail() || value < minVal || value > maxVal) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! Введіть число від " << minVal << " до " << maxVal << ".\n";
        }
        else {
            return value;
        }
    }
}

void Create(Student* p, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент № " << i + 1 << ":" << endl;

        cin.get();
        cin.sync();

        cout << " Прізвище: "; getline(cin, p[i].lastName);
        p[i].course = getValidInt(" Курс (1-6): ", 1, 6);
        p[i].specialty = (Specialty)getValidInt(" Спеціальність (0-КН, 1-ІН, 2-МЕ, 3-ФІ, 4-ТН): ", 0, 4);
        p[i].physics = getValidInt(" Фізика (2-5): ", 2, 5);
        p[i].math = getValidInt(" Математика (2-5): ", 2, 5);
        p[i].informatics = getValidInt(" Інформатика (2-5): ", 2, 5);
    }
}

void Print(Student* p, const int N) {
    cout << "\n" << string(95, '=') << endl;
    cout << "| " << setw(2) << "№" << " | " << setw(15) << left << "Прізвище" << " | " << setw(4) << "Курс"
        << " | " << setw(25) << left << "Спеціальність" << " | " << setw(3) << "Фіз" << " | " << setw(3) << "Мат"
        << " | " << setw(3) << "Інф" << " | " << setw(7) << "Сер.бал" << " |" << endl;
    cout << string(95, '-') << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << " | " << setw(15) << left << p[i].lastName
            << " | " << setw(4) << right << p[i].course << " | " << setw(25) << left << getSpecName(p[i].specialty)
            << " | " << setw(3) << p[i].physics << " | " << setw(3) << p[i].math << " | " << setw(3) << p[i].informatics
            << " | " << setw(7) << fixed << setprecision(2) << GetAverageGrade(p[i]) << " |" << endl;
    }
    cout << string(95, '=') << endl;
}

void Sort(Student* p, const int N) {
    Student tmp;
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - i - 1; j++)
            if (!IsBetter(p[j], p[j + 1], true)) {
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
}

int* IndexSort(Student* p, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++) I[i] = i;

    int value, j;
    for (int i = 1; i < N; i++) {
        value = I[i];
        for (j = i - 1; j >= 0 && !IsBetter(p[I[j]], p[value], false); j--) {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(Student* p, int* I, const int N) {
    if (I == nullptr) return;
    cout << "\nІндексна таблиця (Варіант 10):" << endl;
    cout << string(95, '=') << endl;

    cout << "| " << setw(2) << "№" << " | " << setw(15) << left << "Прізвище" << " | " << setw(4) << "Курс"
        << " | " << setw(25) << left << "Спеціальність" << " | " << setw(3) << "Фіз" << " | " << setw(3) << "Мат"
        << " | " << setw(3) << "Інф" << " | " << setw(7) << "Сер.бал" << " |" << endl;
    cout << string(95, '-') << endl;

    for (int i = 0; i < N; i++) {
        int idx = I[i];
        cout << "| " << setw(2) << right << i + 1 << " | " << setw(15) << left << p[idx].lastName
            << " | " << setw(4) << right << p[idx].course << " | " << setw(25) << left << getSpecName(p[idx].specialty)
            << " | " << setw(3) << p[idx].physics << " | " << setw(3) << p[idx].math << " | " << setw(3) << p[idx].informatics
            << " | " << setw(7) << fixed << setprecision(2) << GetAverageGrade(p[idx]) << " |" << endl;
    }
    cout << string(95, '=') << endl;
}

int BinSearch(Student* p, const int N, const string name, const int course, const double avg) {
    int L = 0, R = N - 1, m;
    while (L <= R) {
        m = (L + R) / 2;
        double currentAvg = GetAverageGrade(p[m]);

        if (p[m].lastName == name && p[m].course == course && abs(currentAvg - avg) < 1e-9)
            return m;

        if (currentAvg < avg ||
            (abs(currentAvg - avg) < 1e-9 && p[m].course < course) ||
            (abs(currentAvg - avg) < 1e-9 && p[m].course == course && p[m].lastName > name)) {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    }
    return -1;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N = getValidInt("Кількість студентів: ", 1, 100);
    Student* p = new Student[N];
    int* indexArr = nullptr;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem) {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            cout << "Фізичне впорядкування виконано." << endl;
            break;
        case 4:
            if (indexArr) delete[] indexArr;
            indexArr = IndexSort(p, N);
            PrintIndexSorted(p, indexArr, N);
            break;
        case 5: {
            cin.get(); cin.sync();
            string name;
            cout << "Введіть ключі пошуку:" << endl;
            cout << " прізвище: "; getline(cin, name);
            int crs = getValidInt(" курс: ", 1, 6);
            double avg;
            cout << " середній бал: "; cin >> avg;
            int res = BinSearch(p, N, name, crs, avg);
            if (res != -1)
                cout << "Знайдено студента в позиції " << res + 1 << endl;
            else
                cout << "Шуканого студента не знайдено (виконайте сортування [3] перед пошуком)" << endl;
            break;
        }
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    if (indexArr) delete[] indexArr;
    return 0;
}