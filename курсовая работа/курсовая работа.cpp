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
	char* name = new char[21]; //математика
	int* mark = new int; //пять
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
	inline void Wait() {
		char temp[2];
		show("Нажмите ввод для продолжения...");
		cin_clear();
		cin.get(temp, 2);
		cin_clear();
	}

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

	int protection_incoming_year()
	{
		string year;
		int number = 0;
		while (true)
		{
			cin >> year;
			if (isdigit(year[0]) and isdigit(year[1]) and isdigit(year[2]) and isdigit(year[3]))
			{
				cin_ignore();
				number = (static_cast<int>(year[0]) - 48) * 1000 + (static_cast<int>(year[1]) - 48) * 100 + (static_cast<int>(year[2]) - 48) * 10 + (static_cast<int>(year[3]) - 48);
				if (number >= 1900 and number <= 2020)
				{
					return number;
				}
				show("Год введен неправильно: год должен быть больше 1900 и меньше 2020\n");
				continue;
			}
			show("Год - число целого типа\n");
			cin_ignore();
			Wait();
		}
	}

	char protection_sex()
	{
		char gender;
		while (true)
		{
			cin >> gender;
			if (gender == 'М' or gender == 'Ж')
			{
				cin_clear();
				return gender;
			}
			else
			{
				cout << "Пол введен неверно, повторите ввод" << endl;
				cin_clear();
				protection_sex();
			}
		}
	}

	
};

	 



struct FIO
{
	char* name = NULL; //Рашид
	char* second_name; //Чотчаев
	char* middle_name; //Хутович
};

struct date
{
	int* day = NULL;
	int* month = NULL;
	int* year = NULL;
};
class student
{

	private:
		enum { NAME_SIZE = 30, FACULTY_SIZE = 100, KAFEDRA_SIZE = 100, GROUP_SIZE = 100, RECORD_GROUP_SIZE = 50};
		FIO fio; //Чотчаев, Рашид, Хутович
		date bday; //25 июля 2002 года
		int* incoming_year; //2020 год
		char* sex = NULL;
		char* faculty = NULL;
		char* kafedra = NULL;
		char* group = NULL;
		char* record_book = NULL;
	public:
		student() //конструктор инициализирует поля класса различными данными
		{
			fio.name = new char[NAME_SIZE];
			fio.middle_name = new char[NAME_SIZE];
			fio.second_name = new char[NAME_SIZE];
			bday.day = new int;
			*bday.day = 0;
			bday.month = new int;
			*bday.month = 0;
			bday.year = new int;
			*bday.year = 0;
			incoming_year = new int;
			*incoming_year = 0;
			sex = new char('М');
			faculty = new char[FACULTY_SIZE];
			kafedra = new char[KAFEDRA_SIZE];
			group = new char[GROUP_SIZE];
			record_book = new char[RECORD_GROUP_SIZE];
		}
		~student() //особождает все поля класса
		{
			delete(fio.middle_name);
			delete(fio.name);
			delete(fio.second_name);
			delete(bday.day);
			delete(bday.month);
			delete(bday.year);
			delete(incoming_year);
			delete(faculty);
			delete(kafedra);
			delete(group);
			delete(record_book);
		}
		void set_all()
		{
			
		}
		 void set_name()
		{
			 cout << "Введите имя студента: ";
			 cin >> fio.name;
		}
		 void set_middle_name()
		 {
			 cout << "Введите фамилию студента: ";
			 cin >> fio.second_name;
		 }
		



};

int main()
{

}