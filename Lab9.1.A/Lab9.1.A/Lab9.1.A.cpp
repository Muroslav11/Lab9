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
    int informatyka;
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
string getSpecName(Specialty s);
int CountGoodMarks(Student* s, const int N, int& phys, int& math, int& info);
double PercentExcellentPhysicsAndMath(Student* s, const int N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    int c_phys, c_math, c_info;
    CountGoodMarks(s, N, c_phys, c_math, c_info);

    cout << "Кількість оцінок 'добре' (4):" << endl;
    cout << " - Фізика: " << c_phys << endl;
    cout << " - Математика: " << c_math << endl;
    cout << " - Інформатика: " << c_info << endl << endl;

    double proc = PercentExcellentPhysicsAndMath(s, N);
    cout << fixed << setprecision(2);
    cout << "Процент студентів з '5' з фізики та математики: " << proc << "%" << endl;

    for (int i = 0; i < N; i++) {
        // Очищення пам'яті всередині не потрібне для string, але delete[] нижче обов'язковий
    }

    delete[] s;
    return 0;
}

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

void Create(Student* s, const int N) {
    int specIndex;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << " Прізвище: "; getline(cin, s[i].prizv);
        cout << " Курс: "; cin >> s[i].kurs;
        cout << " Спеціальність (0-KN, 1-INF, 2-ME, 3-FI, 4-TN): ";
        cin >> specIndex;
        s[i].spec = (Specialty)specIndex;
        cout << " Оцінка з фізики: "; cin >> s[i].physics;
        cout << " Оцінка з математики: "; cin >> s[i].math;
        cout << " Оцінка з інформатики: "; cin >> s[i].informatyka;
        cout << endl;
    }
}

void Print(Student* s, const int N) {
    cout << "=============================================================================" << endl;
    cout << "| № | Прізвище     | Курс | Спеціальність          | Фіз | Мат | Інф |" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(12) << left << s[i].prizv;
        cout << "| " << setw(4) << right << s[i].kurs << " ";
        cout << "| " << setw(22) << left << getSpecName(s[i].spec);
        cout << "| " << setw(3) << right << s[i].physics << " ";
        cout << "| " << setw(3) << right << s[i].math << " ";
        cout << "| " << setw(3) << right << s[i].informatyka << " |" << endl;
    }
    cout << "=============================================================================" << endl << endl;
}

int CountGoodMarks(Student* s, const int N, int& phys, int& math, int& info) {
    phys = 0;
    math = 0;
    info = 0;

    for (int i = 0; i < N; i++) {
        if (s[i].physics == 4) phys++;
        if (s[i].math == 4) math++;
        if (s[i].informatyka == 4) info++;
    }
    return phys + math + info;
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