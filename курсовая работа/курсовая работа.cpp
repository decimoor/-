#include <string>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define LINE_LENGTH 140;
#define head1 "|              Фамилия              |                Имя                |             Отчество              | Дата рождения |      Пол      |\n"
#define head2 "|           Год поступления         |             Факультет             |             Кафедра               | Номер зачетной книжки         |\n"
#define line cout << " "; for (int j = 0; j < LINE_LENGTH; j++) cout <<"_"; cout <<endl; 
struct sub
{
	string name; //математика
	int mark; //пять
};

class input_output
{
public:
	void show(char* str) { cout << str; } // вывод строки по ссылке на первый элемент
	void show(int number) { cout << number; } // вывод числа
	void show(string str) { cout << str;  } // вывод строки типа string
	void cin_clear() //функция очищает поток ввода
	{
		cin.seekg(0, ios::end);
		cin.clear();
	}
	void cin_ignore()
	{
		cin.clear();
		cin.ignore();
	}

	//далее идут методы, которые проверяют правильность введенных данных

	bool check_date(int day, int month, int year)
	{
		if (day != 0 and month != 0 and year != 0)
		{
			if (year >= 1900 and year <= 2020)
			{
				if (month >= 1 and month <= 12)
				{
					switch (month)
					{
					case 1: case 3: case 5: case 7: case 8: case 10: case 12:
						if (day >= 1 and day <= 31) { return true; }
						break;

					case 2:
						if (year % 4 != 0 or (year % 100 == 0 and year % 400 != 0))
						{
							if (day >= 1 and day <= 28) { return true; }
						}
						else
						{
							if (day >= 1 and day <= 29) { return true; }
						}
						break;
					case 4: case 6: case 9: case 11:
						if (day >= 1 and day <= 30) { return true; }
						break;
					default:
						show("ОШИБКА: дата введена неверно\n");
						break;
					}
				}
				else
				{
					show("ОШИБКА: Месяц должен быть от 1 до 12\n");
				}
			}
			else
			{
				show("ОШИБКА: Год должен быть от 1900 до 2020\n");
			}
		}
		show("Неверная дата\n");
		return false;
	}

	int protection_year_of_receipt()
	{
		string year;
		int number = 0;
		while (true)
		{
			cin >> year;
			if (isdigit(year[0]) and isdigit(year[1]) and isdigit(year[2]) and isdigit(year[3]))
			{
				cin_ignore();
				number = static_cast<int>(year[0]) * 1000 + static_cast<int>(year[1]) * 100 + static_cast<int>(year[2]) * 10 + static_cast<int>(year[3]);
				if (number >= 1900 and number <= 2020)
				{
					return number;
				}
				show("Год введен неправильно: год должен быть больше 1900 и меньше 2020\n");
				continue;
			}
			show("Год - число целого типа\n");
			cin_ignore();
			Sleep(2);
		}
	}

	



};
struct FIO
{
	string name;
	string second_name;
	string middle_name;
};
class student
{
	private:
		FIO fio; //Чотчаев, Рашид, Хутович

		
};

int main()
{
	cout << "go to work bitch" << endl;
	cout << "you suck man" << endl;
}