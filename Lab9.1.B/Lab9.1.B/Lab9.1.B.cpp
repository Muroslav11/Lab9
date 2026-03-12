#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Specialty { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, LABOR_TRAINING };

struct Student {
    string prizv;
    int kurs;
    Specialty spec;
    int physics;
    int math;
    union {
        int programming;
        int numerical_methods;
        int pedagogy;
    };
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
string getSpecName(Specialty s);
void CountGoodMarks(Student* s, const int N, int& phys, int& math, int& third);
double PercentExcellentPhysicsAndMath(Student* s, const int N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* s = new Student[N]();

    Create(s, N);
    Print(s, N);

    int c_phys, c_math, c_third;
    CountGoodMarks(s, N, c_phys, c_math, c_third);

    cout << "Кількість оцінок 'добре' (4):" << endl;
    cout << " - Фізика: " << c_phys << endl;
    cout << " - Математика: " << c_math << endl;
    cout << " - Профільний предмет: " << c_third << endl << endl;

    double proc = PercentExcellentPhysicsAndMath(s, N);
    cout << fixed << setprecision(2);
    cout << "Процент студентів з '5' з фізики та математики: " << proc << "%" << endl;

    delete[] s;
    return 0;
}

string getSpecName(Specialty s) {
    switch (s) {
    case COMPUTER_SCIENCE:    return "Комп'ютерні науки";
    case INFORMATICS:         return "Інформатика";
    case MATH_ECONOMICS:      return "Мат. та економ.";
    case PHYSICS_INFORMATICS: return "Фіз. та інформ.";
    case LABOR_TRAINING:      return "Трудове навч.";
    default:                  return "Невідома";
    }
}

void Create(Student* s, const int N) {
    int specIndex;
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент № " << i + 1 << endl;
        cin.get();
        cin.sync();

        cout << "Прізвище: "; getline(cin, s[i].prizv);
        cout << "Курс: "; cin >> s[i].kurs;
        cout << "Спеціальність (0-КН, 1-ІНФ, 2-МЕ, 3-ФІ, 4-ТН): ";
        cin >> specIndex;
        s[i].spec = (Specialty)specIndex;

        cout << "Фізика: "; cin >> s[i].physics;
        cout << "Математика: "; cin >> s[i].math;

        if (s[i].spec == COMPUTER_SCIENCE) {
            cout << "Оцінка з програмування: "; cin >> s[i].programming;
        }
        else if (s[i].spec == INFORMATICS) {
            cout << "Оцінка з чисельних методів: "; cin >> s[i].numerical_methods;
        }
        else {
            cout << "Оцінка з педагогіки: "; cin >> s[i].pedagogy;
        }
    }
}

void Print(Student* s, const int N) {
    cout << endl;
    cout << "=============================================================================================" << endl;
    cout << "| № | Прізвище       |Курс| Спеціальність        |Фіз|Мат|Прог|Числ|Пед |" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(15) << left << s[i].prizv;
        cout << "| " << setw(2) << right << s[i].kurs << " ";
        cout << "| " << setw(21) << left << getSpecName(s[i].spec);
        cout << "| " << setw(1) << right << s[i].physics << " ";
        cout << "| " << setw(1) << right << s[i].math << " ";

        if (s[i].spec == COMPUTER_SCIENCE)
            cout << "| " << setw(2) << right << s[i].programming << " |    |    |";
        else if (s[i].spec == INFORMATICS)
            cout << "|    | " << setw(2) << right << s[i].numerical_methods << " |    |";
        else
            cout << "|    |    | " << setw(2) << right << s[i].pedagogy << " |";

        cout << endl;
    }
    cout << "=============================================================================================" << endl << endl;
}

void CountGoodMarks(Student* s, const int N, int& phys, int& math, int& third) {
    phys = 0;
    math = 0;
    third = 0;

    for (int i = 0; i < N; i++) {
        if (s[i].physics == 4)
            phys++;

        if (s[i].math == 4)
            math++;

        int mark;
        if (s[i].spec == COMPUTER_SCIENCE) {
            mark = s[i].programming;
        }
        else if (s[i].spec == INFORMATICS) {
            mark = s[i].numerical_methods;
        }
        else {
            mark = s[i].pedagogy;
        }

        if (mark == 4)
            third++;
    }
}

double PercentExcellentPhysicsAndMath(Student* s, const int N) {
    if (N == 0) return 0;
    int k = 0;
    for (int i = 0; i < N; i++) {
        if (s[i].physics == 5 && s[i].math == 5)
            k++;
    }
    return 100.0 * k / N;
}