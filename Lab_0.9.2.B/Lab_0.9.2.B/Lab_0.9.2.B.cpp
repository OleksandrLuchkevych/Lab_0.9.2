#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
//enum Specialnist { ROBITNYK, INZHENER, SLUZHBOVETS };
//string specialnistStr[] = { "робітник", "інженер", "службовець" };
enum Specialnist { KN, IT, MATH, PHYSIC, WORK };
enum Curs { FIRST, SECOND, THIRD, FOUR };
string cursStr[] = { "I", "II", "III", "IV" };
string specialnistStr[] = { "Комп науки", "Інформатика", "Мат та ек", "Фіз та інформ", "Труд навч" };

struct Student
{
	string prizv;
	Curs curs;
	Specialnist specialnist;
	struct
	{
		int physic;
		int math;

	};
	union
	{
		int IT;
		int nummet;
		int pedagog;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Curs curs);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];
	double proc;
	int ispecurs;
	Specialnist specialnist;
	Curs curs;
	string prizv;
	int found;
	char filename[100];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - бінарний пошук студента за посадою та прізвищем" << endl;
		cout << " [5] - індексне впорядкування та вивід даних" << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			cout << "Введіть ключі пошуку:" << endl;
			cout << "  курс (0 - I, 1 - II, 2 - III, 3 - IV):";
			cin >> ispecurs;
			curs = (Curs)ispecurs;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, curs)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int specialnist;
	int curs;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс (0 - I, 1 - II, 2 - III, 3 - IV): ";
		cin >> curs;
		cout << " спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
		cin >> specialnist;
		cout << " оцінка з фізики : "; cin >> p[i].physic;
		cout << " оцінка з математики : "; cin >> p[i].math;
		p[i].specialnist = (Specialnist)specialnist;
		p[i].curs = (Curs)curs;
		switch (p[i].specialnist)
		{
		case KN:
			cout << " оцінка з програмування : "; cin >> p[i].IT;
			break;
		case IT:
			cout << " оцінка з чисельних методів : "; cin >> p[i].nummet;
			break;
		case MATH:
		case PHYSIC:
		case WORK:
			cout << " оцінка з педагогіки : "; cin >> p[i].pedagog;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "==========================================================================================================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Оцінка з фізики | Оцінка з математики | Оцінка з програмування | Оцінка з чисельних методів | Оцінка з педагогіки |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << i + 1;
		cout << "| " << setw(9) << p[i].prizv;
		cout << "| " << setw(5) << cursStr[p[i].curs];
		cout << "| " << setw(14) << specialnistStr[p[i].specialnist];
		cout << "| " << setw(16) << p[i].physic;
		cout << "| " << setw(20) << p[i].math;
		switch (p[i].specialnist)
		{
		case KN:
			cout << "| " << setw(23) << p[i].IT << "|" << setw(29) << "|" << setw(22) << "|";
			break;
		case IT:
			cout << "| " << setw(24) << "|" << setw(28) << p[i].nummet << "|" << setw(22) << "|";
			break;
		case MATH:
		case PHYSIC:
		case WORK:
			cout << "| " << setw(24) << "|" << setw(29) << "|" << setw(21) << p[i].pedagog << "|";
			break;
		}
		cout << endl;
	}
	cout << "==========================================================================================================================================================="
		<< endl;
	cout << endl;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].IT < p[i1 + 1].IT || p[i1].IT < p[i1 + 1].nummet || p[i1].IT < p[i1 + 1].pedagog
				|| p[i1].nummet < p[i1 + 1].IT || p[i1].nummet < p[i1 + 1].nummet || p[i1].nummet < p[i1 + 1].pedagog
				|| p[i1].pedagog < p[i1 + 1].IT || p[i1].pedagog < p[i1 + 1].nummet || p[i1].pedagog < p[i1 + 1].pedagog)
				||
				((p[i1].IT == p[i1 + 1].IT || p[i1].IT == p[i1 + 1].nummet || p[i1].IT == p[i1 + 1].pedagog
					|| p[i1].nummet == p[i1 + 1].IT || p[i1].nummet == p[i1 + 1].nummet || p[i1].nummet == p[i1 + 1].pedagog
					|| p[i1].pedagog == p[i1 + 1].IT || p[i1].pedagog == p[i1 + 1].nummet || p[i1].pedagog == p[i1 + 1].pedagog) &&
					p[i1].curs < p[i1 + 1].curs)
				|| ((p[i1].IT == p[i1 + 1].IT || p[i1].IT == p[i1 + 1].nummet || p[i1].IT == p[i1 + 1].pedagog
					|| p[i1].nummet == p[i1 + 1].IT || p[i1].nummet == p[i1 + 1].nummet || p[i1].nummet == p[i1 + 1].pedagog
					|| p[i1].pedagog == p[i1 + 1].IT || p[i1].pedagog == p[i1 + 1].nummet || p[i1].pedagog == p[i1 + 1].pedagog) &&
					p[i1].curs == p[i1 + 1].curs &&
					p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, const string prizv, const Curs curs)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].curs == curs)
			return m;
		if ((p[m].curs < curs)
			||
			(p[m].curs == curs &&
				p[m].prizv < prizv))
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
int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 &&
			((p[I[j]].IT < p[value].IT || p[I[j]].IT < p[value].nummet || p[I[j]].IT < p[value].pedagog
				|| p[I[j]].nummet < p[value].IT || p[I[j]].nummet < p[value].nummet || p[I[j]].nummet < p[value].pedagog
				|| p[I[j]].pedagog < p[value].IT || p[I[j]].pedagog < p[value].nummet || p[I[j]].pedagog < p[value].pedagog)
				||
				((p[I[j]].IT == p[value].IT || p[I[j]].IT == p[value].nummet || p[I[j]].IT == p[value].pedagog
					|| p[I[j]].nummet == p[value].IT || p[I[j]].nummet == p[value].nummet || p[I[j]].nummet == p[value].pedagog
					|| p[I[j]].pedagog == p[value].IT || p[I[j]].pedagog == p[value].nummet || p[I[j]].pedagog == p[value].pedagog) &&
					p[I[j]].curs < p[value].curs)
				|| ((p[I[j]].IT == p[value].IT || p[I[j]].IT == p[value].nummet || p[I[j]].IT == p[value].pedagog
					|| p[I[j]].nummet == p[value].IT || p[I[j]].nummet == p[value].nummet || p[I[j]].nummet == p[value].pedagog
					|| p[I[j]].pedagog == p[value].IT || p[I[j]].pedagog == p[value].nummet || p[I[j]].pedagog == p[value].pedagog) &&
					p[I[j]].curs == p[value].curs &&
					p[I[j]].prizv > p[value].prizv));
		j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]... 
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
	cout << "==========================================================================================================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Оцінка з фізики | Оцінка з математики | Оцінка з програмування | Оцінка з чисельних методів | Оцінка з педагогіки |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << i + 1;
		cout << "| " << setw(9) << p[I[i]].prizv;
		cout << "| " << setw(5) << cursStr[p[I[i]].curs];
		cout << "| " << setw(14) << specialnistStr[p[I[i]].specialnist];
		cout << "| " << setw(16) << p[I[i]].physic;
		cout << "| " << setw(20) << p[I[i]].math;
		switch (p[i].specialnist)
		{
		case KN:
			cout << "| " << setw(23) << p[I[i]].IT << "|" << setw(29) << "|" << setw(22) << "|";
			break;
		case IT:
			cout << "| " << setw(24) << "|" << setw(28) << p[I[i]].nummet << "|" << setw(22) << "|";
			break;
		case MATH:
		case PHYSIC:
		case WORK:
			cout << "| " << setw(24) << "|" << setw(29) << "|" << setw(21) << p[I[i]].pedagog << "|";
			break;
		}
		cout << endl;
	}
	cout << "==========================================================================================================================================================="
		<< endl;
	cout << endl;
}