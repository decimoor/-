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

	bool is_int_string(string number)
	{
		for (int i = 0; i < number.length(); i++)
		{
			if (!isdigit(number[i]))
			{
				return false;
			}
		}
		return true;
	}

	bool check_date(string date)
	{
		if (isdigit(date[0]) and isdigit(date[1]) and date[3] == '.' and isdigit(date[4]) and isdigit(date[5]) and date[6] == '.' and isdigit(date[7]) and isdigit(date[8]) and isdigit(date[9]) and isdigit(date[10]))
		{
			return true;
		}

		return false;
	}

	bool is_string_string(char str[])
	{
		for (int i = 0; i < sizeof(str); i++)
		{
			if (isdigit(str[i]))
				return false;
		}
		return true;
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
class student: public input_output
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
			set_name();
			set_second_name();
			set_middle_name();
			set_bday();
			set_incoming_year();
			set_faculty();
			set_kafedra();
			set_group();
			set_record_book();
		}

		//все сэттеры
		 void set_name()
		{
			 cout << "\nВведите имя студента: ";
			 cin >> fio.name;
			 cin_clear();
		}
		 void set_second_name()
		 {
			 cout << "\nВведите фамилию студента: ";
			 cin >> fio.second_name;
			 cin_clear();
		 }
		 void set_middle_name()
		 {
			 cout << "\nВведите отчество студента: ";
			 cin >> fio.middle_name;
			 cin_clear();
		 }
		 void set_incoming_year()
		 {
			 cout << "\nВведите год поступления: ";
			 *incoming_year = protection_incoming_year();
			 cin_clear();
		 }
		 void set_bday()
		 {
			 string date;
			 int day;
			 int month;
			 int year = 0;
			 while (true)
			 {
				cout << "\nВведите год рождения в формате {дд.мм.гггг}: ";
				cin >> date;
				if (check_date(date))
				{
					day = (static_cast<int>(date[0]) - 48) * 10 + static_cast<int>(date[1]) - 48;
					month = (static_cast<int>(date[3]) - 48) * 10 + static_cast<int>(date[4]) - 48;
					for (int i = 6, ten = 1000; i < 10; i++)
					{
						year += (static_cast<int>(date[i]) - 48) * ten;
						ten /= 10;
					}
					if (check_date(day, month, year))
					{
						*bday.day = day;
						*bday.month = month;
						*bday.year = year;
						break;
						
					}
				}
				else
				{
					cout << "\nДанные введены неправильно";
				}
				cin_clear();
			 }
		 }

		 void set_record_book()
		 {
			 string rec_book;
			 int ten;
			 while (true)
			 {
				 cout << "\nВведите номер зачетное книжки студента: ";
				 cin >> rec_book;
				 ten = pow(10, rec_book.length() - 1);
				 if (is_int_string(rec_book))
				 {
					 for (int i = 0; i < rec_book.length(); i++)
					 {
						 record_book += (static_cast<int>(rec_book[i]) - 48) * ten;
						 ten /= 10;
					 }
					 break;
				 }
				 else
				 {
					 cout << "\nВ номере зачетной книжки не может быть чисел";
				 }

			 }
		 }
		 
		 void set_sex()
		 {
			 *sex = protection_sex();
		 }

		 void set_faculty()
		 {
			 while (true)
			 {
				 cout << "\nВведите факультет студента: ";
				 char fac[FACULTY_SIZE];
				 cin >> fac;
				 if (is_string_string(fac))
				 {
					 faculty = fac;
					 break;
				 }
				 else
				 {
					 cout << "\nНазвание факультета введено некорректно";
				 }
			 }
		 }
		 void set_group()
		 {
			 cout << "\nВведите название группы: ";
			 cin >> group;

		 }

		 void set_kafedra()
		 {
			 while (true)
			 {
				 cout << "\nВведите кафедру студента: ";
				 char kaf[FACULTY_SIZE];
				 cin >> kaf;
				 if (is_string_string(kaf))
				 {
					 kafedra = kaf;
					 break;
				 }
				 else
				 {
					 cout << "\nНазвание кафедры введено некорректно";
				 }
			 }
		 }




};

int main()
{

}