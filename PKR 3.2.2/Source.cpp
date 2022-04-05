#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

enum Spec { CS, IT, ME, PhIT, TR };

string strSpec[] = { "����'�����i �����", "I����������", "���������� �� ������i��", "�i���� �� i����������", "������� ��������" };

struct Student
{
    string lname;
    int kurs;
    Spec spec;
    int physics;
    int math;
    union {
        int progr;
        int numb;
        int ped;
    };
};

void Create(Student* s, int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "��i�����: ";
        cin >> s[i].lname;
        cout << "����: ";
        cin >> s[i].kurs;
        cout << "����i����i��� (0 - ����'�����i �����, 1 - I����������, 2 - ���������� �� ������i��, 3 - �i���� �� i����������, 4 - ������� ��������) ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "��i��� � �i����: ";
        cin >> s[i].physics;
        cout << "��i��� � ����������: ";
        cin >> s[i].math;
        if (s[i].spec == 0) {
            cout << "��i��� � �������������: ";
            cin >> s[i].progr;
        }
        else if (s[i].spec == 1) {
            cout << "��i��� � ��������� �����i�: ";
            cin >> s[i].numb;
        }
        else {
            cout << "��i��� � �������i��: ";
            cin >> s[i].ped;
        }
    }
}

void Print(Student* s, int amSt)
{
    cout << "--------------------------------------------------------------------------------------------------------------------------"
        << endl;
    cout << "| � |    ��i�����   | ���� |      ����i����i���     | �i���� | ���������� | ������������� | �������i ������ | �������i�� |"
        << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < amSt; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(14) << left << s[i].lname
            << "| " << setw(5) << right << s[i].kurs
            << "| " << setw(23) << left << strSpec[s[i].spec]
            << "| " << setw(7) << s[i].physics
            << "| " << setw(11) << right << s[i].math;
        if (s[i].spec == 0)
        {
            cout << "| " << setw(14) << right << s[i].progr
                << "| " << setw(16) << right << " "
                << "| " << setw(11) << right << " " << "| ";
        }
        else if (s[i].spec == 1)
        {
            cout << "| " << setw(14) << right << " "
                << "| " << setw(16) << right << s[i].numb
                << "| " << setw(11) << right << " " << "| ";
        }
        else
        {
            cout << "| " << setw(14) << right << " "
                << "| " << setw(16) << right << " "
                << "| " << setw(11) << right << s[i].ped << "| ";
        }
        cout << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------"
        << endl;
}



double avgGrade(Student* s, const int i)
{
    double m = (s[0].physics + s[0].math + s[0].progr) / 3;
    double m1 = (s[0].physics + s[0].math + s[0].numb) / 3;
    double m2 = (s[0].physics + s[0].math + s[0].ped) / 3;
    if (s[i].spec == 0)
    {
        m = (s[i].physics + s[i].math + s[i].progr) / 3;
        return m;
    }
    else if (s[i].spec == 1)
    {
        m1 = (s[i].physics + s[i].math + s[i].numb) / 3;
        return m1;
    }
    else
        m2 = (s[i].physics + s[i].math + s[i].ped) / 3;
    return m2;
}

void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((avgGrade(p, i1) > avgGrade(p, i1 + 1)) || (avgGrade(p, i1) == avgGrade(p, i1 + 1) && p[i1].math > p[i1 + 1].math)
                ||
                (p[i1].math == p[i1 + 1].math &&
                    p[i1].lname > p[i1 + 1].lname))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* indexSort(Student* s, int N)
{
    int* P = new int[N];

    for (int i = 0; i < N; i++)
    {
        P[i] = i;
    }
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = P[i];
        for (j = i - 1; j >= 0 && ((avgGrade(s, P[j]) > avgGrade(s, value))
            ||
            (avgGrade(s, P[j]) == avgGrade(s, value) &&
                s[P[j]].math > s[value].math)
            ||
            (s[P[j]].math == s[value].math &&
                s[P[j]].lname > s[value].lname));
            j--)
        {
            P[j + 1] = P[j];
        }
        P[j + 1] = value;
    }
    return P;
}

int binSearch(Student* p, const int N, const string prizv, const int math)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].lname == prizv && avgGrade(p, m) == avgGrade(p, m) && p[m].math == math)
            return m;
        if ((p[m].lname < prizv)
            ||
            (p[m].lname == prizv &&
                avgGrade(p, m) < avgGrade(p, m))
            ||
            avgGrade(p, m) < avgGrade(p, m) &&
            p[m].math < math)
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int amSt;
    string lastName;
    int math;
    int avgGrade, found;
    cout << "ʳ������ ��������: ";
    cin >> amSt;
    Student* s = new Student[amSt];

    int menuItem;
    do
    {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ��������� " << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ������� ������������� ����� " << endl;
        cout << " [4] - �������� ������������� �� ���� ����� " << endl;
        cout << " [5] - ������� ����� ��� ����������, �� ��������� ������� " << endl;
        cout << " �� �������� ������������ �������� �� ������� ������������ �� �������� ������� �����." << endl;
        cout << " [0] - ����� �� ���������� �������� " << endl;
        cout << "������ �������: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem) {
        case 1:
            Create(s, amSt);
            break;
        case 2:
            Print(s, amSt);
            break;
        case 3:
            Sort(s, amSt);
            break;
        case 4:
            indexSort(s, amSt);
            break;
        case 5:
            cout << "������ ����� ������:" << endl;
            cout << " �������: "; cin >> lastName;
            cout << endl;
            cout << " ������� ���: " << endl; cin >> avgGrade;
            cout << endl;
            cout << " ������ � ����������: " << endl; cin >> math;
            cout << endl;
            cin.get(); // ������� ����� ��������� � �� ����������� �������
            cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����


            if ((found = binSearch(s, amSt, lastName, math)) != -1)
                cout << "�������� �������� � ������� " << found + 1 << endl;
            else
                cout << "�������� �������� �� ��������" << endl;
            break;
        case 0:
            break;
        }
    } while (menuItem != 0);
    return 0;
}