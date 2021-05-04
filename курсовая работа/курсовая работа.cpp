#include <string>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <clocale>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define LINE_LENGTH 140;
#define head1 "|              Фамилия              |                Имя                |             Отчество              | Дата рождения |  Пол  |\n"
#define head2 "|           Год поступления         |             Факультет             |             Кафедра               |      Номер зачетной книжки         |\n"
const int BLOCK_SIZE = 35;
const int  DATE_SIZE =  15;
const int SEX_SIZE =  7;
const int NUMBER_OF_SUBJECTS = 9;
const int NUMBER_OF_SESSIONS = 10;
int id = -1;
int last_student = 0;
const int NUMBER_OF_STUDENTS = 10;
#define line cout << " --------------------------------------------------------------------------------------------------------------------------------------------\n"
struct sub
{
	string name = "unknown"; //математика
	int mark = 0; //пять
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

	int protection_incoming_year()
	{
		string year;
		int number = 0;
		while (true)
		{
			show("Введите год постулпения: ");
			cin >> year;
			if (isdigit(year[0]) and isdigit(year[1]) and isdigit(year[2]) and isdigit(year[3]) and year.length() == 4)
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
		}
	}

	char protection_sex()
	{
		char gender;
		while (true)
		{
			show("Укажите пол студента: ");
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
		int len = number.length();
		for (int i = 0; i < len; i++)
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
		if (isdigit(date[0]) and isdigit(date[1]) and date[2] == '.' and isdigit(date[3]) and isdigit(date[4]) and date[5] == '.' and isdigit(date[6]) and isdigit(date[7]) and isdigit(date[8]) and isdigit(date[9]) and date.length() == 10)
		{
			return true;
		}

		return false;
	}

	bool is_string_string(char str[])
	{
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (isdigit(str[i]))
				return false;
		}
		return true;
	}
	bool is_string_string(string str)
	{
		int len = str.length();
		for (int i = 0; i < len; i++)
		{
			if (isdigit(str[i]))
				return false;
		}
		return true;
	}

	int string_to_int(string number)
	{
		int number1 = 0;
		int ten = pow(10, number.length() - 1);
		for (int i = 0; i < number.length(); i++)
		{
			number1 = (static_cast<int>(number[i] )-48)* ten;
			ten /= 10;
		}
		return number1;
	}


	
};

class session
{
protected:
	sub exams[NUMBER_OF_SESSIONS][NUMBER_OF_SUBJECTS];

public:
	int get_mark(int number_of_session, string subject)
	{
		for (int i = 0; i < NUMBER_OF_SUBJECTS; i++)
		{
			if (exams[number_of_session][i].name == subject)
			{
				return exams[number_of_session][i].mark;
			}
		}
		cout << "\nДанный студент не сдавал этот экзамен в этом семестре";
	}

	void set_mark(int mark, int number_of_session, string subject)
	{
		for (int i = 0; i < NUMBER_OF_SUBJECTS; i++)
		{
			if (exams[number_of_session - 1][i].name == subject)
			{
				exams[number_of_session - 1][i].mark = mark;
			}

		}
	}

	void set_subject(int number_of_session, string subject)
	{
		int i = 0;
		for (int i = 0; i < NUMBER_OF_SUBJECTS; i++)
		{
			if (exams[number_of_session - 1][i].name == "unknown")
			{
				exams[number_of_session - 1][i].name = subject;
				break;
			}
		}


	}

	void show_all()
	{
		for (int i = 0; exams[i][0].name != "unknown"; i++)
		{
			cout << "\n| Семестр: " << i + 1;
			for (int j = 0; exams[i][j].name != "unknown"; j++)
			{
				cout << "| " << setw(35) << left << exams[i][j].name;
			}
			cout << "|" << endl << "            ";
			for (int j = 0; exams[i][j].name != "unknown"; j++)
			{
				cout << "| " << setw(35) << left << exams[i][j].mark;
			}
			cout << "|" <<  endl;
			line;
		}


	}

	//конструктор инициализирует поле name unknown
};



struct FIO
{
	string name; //Рашид
	string second_name; //Чотчаев
	string middle_name; //Хутович
};

struct date
{
	int* day = NULL; //25
	int* month = NULL; //07
	int* year = NULL; //2002
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
		session sessions;
		int student_number;
	public:
		student() //конструктор инициализирует поля класса различными данными
		{
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
			student_number = ++id;
		}
		~student() //особождает все поля класса
		{
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
			set_sex();
			set_bday();
			set_incoming_year();
			set_faculty();
			set_kafedra();
			set_group();
			set_record_book();
			set_marks();
		}

		bool is_it_here(FIO f)
		{
			if (f.name == fio.name and f.second_name == fio.second_name and f.middle_name == fio.middle_name)
			{
				return true;
			}
			return false;
		}

		string full_name()
		{
			string full_name = fio.second_name + ", " + fio.name + ", " + fio.middle_name;
			return full_name;
		}

		void delete_student()
		{
			fio.name = "unknown";
			last_student--;
		}

		void set_marks()
		{
			string subject;
			string number_of_sessions;
			int number_of_sessions2;
			string mark;
			int j = 0;
			while (true)
			{
				cout << "\nВведите количество сессий, которые были у студента: ";
				cin >> number_of_sessions;
				if (is_int_string(number_of_sessions))
				{
					number_of_sessions2 = string_to_int(number_of_sessions);
					if (number_of_sessions2 <= NUMBER_OF_SESSIONS)
					{
						break;
					}
					else
					{
						cout << "\nКоличество сессий должно быть меньше 9";
					}
				}
				else
				{
					cout << "\nВвод неверен, повторите ввод";
					cin_clear();
				}
			}

			for (int i = 0; i < number_of_sessions2; i++)
			{
				cout << "\nВвод предметов и оценок для сессии под номером: " << i + 1;
				for (j = 0; j < NUMBER_OF_SUBJECTS; j++)
				{
					cout << "\nВведите название предмета, если ввод закончен напишите N: ";
					cin.ignore(32767, '\n');
					getline(cin, subject);
					if (subject == "N")
					{
						break;
					}
					if (!is_string_string(subject))
					{
						cout << "\nНазвание предмета введено неверно, попробуте заново";
						j--;
						cin_clear();
					}
					else
					{
						sessions.set_subject(i+1, subject);
						while (true)
						{
							cout << "\nВведите оценку по этому предмету: ";
							cin >> mark;
							
							if (is_int_string(mark))
							{
								int one = string_to_int(mark);
								if (one <= 5 and one >= 2)
								{
									sessions.set_mark(one, i+1, subject);
									break;
								}
								else
								{
									cout << "\nОценка - число от 2 до 5, попробуйте заново";
									cin_clear();
								}
							}
							else
							{
								cout << "\nОценка введена неверно, попробуйте снова";
							}
						}
					}
				}
				
			}

		}

		//функция, показывающая информацию о студенте
		void show_all()
		{
			cout << "Студент: " << student_number << endl;
			cout << head1 << endl;
			cout << "|" << setw(BLOCK_SIZE) << left << fio.second_name <<"|" <<setw(BLOCK_SIZE) << left << fio.name << "|" << setw(BLOCK_SIZE) << left << fio.middle_name << "|" << *bday.day << "." << *bday.month << "." << *bday.year << "       |" << *sex <<"    |" << endl;
			line;
			cout << head2 << endl;
			line;
			cout <<"|" <<  setw(BLOCK_SIZE) << left << *incoming_year << "|" << setw(BLOCK_SIZE) << left << faculty << "|" << setw(BLOCK_SIZE) << left << kafedra << "|" << setw(BLOCK_SIZE) << left << record_book << endl;
			line;
			sessions.show_all();
		}

		//все сэттеры
		 void set_name()
		{
			 
			 while (true)
			 {
				 cout << "\nВведите имя студента: ";
				 cin >> fio.name;
				 if (is_string_string(fio.name))
				 {
					 break;
				 }
				 else
				 {
					 cout << "\nВ имени студента не может быть цифр, попробуйте заново";
					 cin_clear();
				 }
			 }
		}
		 void set_second_name()
		 {
			 
			 while (true)
			 {
				 cout << "\nВведите фамилию студента: ";
				 cin >> fio.second_name;
				 if (is_string_string(fio.second_name))
				 {
					 break;
				 }
				 else
				 {
					 cout << "\nВ фамилии студента не может быть цифр, попробуйте заново";
					 cin_clear();
				 }
			 }
		 }
		 void set_middle_name()
		 {
			 
			 while (true)
			 {
				 cout << "\nВведите отчество студента: ";
				 cin >> fio.middle_name;
				 if (is_string_string(fio.middle_name))
				 {
					 break;
				 }
				 else
				 {
					 cout << "\nВ отчестве студента не может быть цифр, попробуйте заново";
					 cin_clear();
				 }
			 }
		 }
		 void set_incoming_year()
		 {
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
					year = 0;
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
					 int len = rec_book.length();
					 for (int i = 0; i < len; i++)
					 {
						 *(record_book + i) = rec_book[i];
					 }
					 *(record_book + rec_book.length()) = '\0';
					 break;
				 }
				 else
				 {
					 cout << "\nВ номере зачетной книжки не может быть букв";
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
				 char* tmp = faculty;
				 cout << "\nВведите факультет студента: ";
				 char* fac = new char[FACULTY_SIZE];
				 cin >> fac;
				 if (is_string_string(fac))
				 {

					 faculty = fac;
					 free(tmp);
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
			 cin_clear();
		 }

		 void set_kafedra()
		 { 
			cout << "\nВведите кафедру студента: ";
			cin >> kafedra;
			cin_clear();
		 }

		 //все гэттеры
};



class menu: public student
{
private:
	string add_student = "\n[1] - Добавить студента: ";
	string show_student = "\n[2] - Вывести всех студентов: ";
	string delete_student = "\n[3] - Удалить студента: ";
	string find_student = "\n[4] - Найти студента по ФИО: ";
	string sort = "\n[5] - Сортировка: ";
	string exit = "\n[6] - Выйти из программы: ";
	student students[NUMBER_OF_STUDENTS];
	int choose = 0;
	bool idk = true;
	string fio;
public:
	void main_menu()
	{
		while (idk)
		{
			choose = show_menu();
			switch (choose)
			{
				case 1:
					students[last_student++].set_all();
					break;
				case 2:
					for (int i = 0; i < last_student; i++)
					{
						students[i].show_all();
					}
					break;
				case 3:
					delete_student1();
					break;
				case 4:
					//find_student1();
					break;
				case 5:
					//sort(students);
					break;
				case 6:
					idk = true;
					break;
			}
		}
	}

	

	
	int show_menu()
	{
		string ch;
		while (true)
		{
			cout << "\n[1] - Добавить студента : ";
			cout << "\n[2] - Вывести всех студентов: ";
			cout << "\n[3] - Удалить студента: ";
			cout << "\n[4] - Найти студента по ФИО: ";
			cout << "\n[5] - Сортировка: ";
			cout << "\n[6] - Выйти из программы: ";
			cin >> ch;
			if (is_int_string(ch))
			{
				int one = string_to_int(ch);
				if (one >= 1 and one <= 6)
				{
					return one;
				}
				else
				{
					cout << "\nТакого вариант не существует, попробуйте заново";
					Sleep(300);
				}
			}
			else
			{
				cout << "\nВы должны ввести число, соотвествующее определенной функции программы";
				Sleep(300);
			}
		}
	}
	void delete_student1()
	{
		int tmp = 0;
		if (last_student == 0)
		{
			cout << "\nВ базе данных нет ни одного студента";
		}
		else
		{
			cout << "\nВведите Ф.И.О студента, которого следует удалить из базы данных: ";
			cin.ignore(32767, '\n');
			getline(cin, fio);
			for (int i = 0; i <= last_student; i++)
			{
				if (fio == students[i].full_name())
				{
					if (i == last_student)
					{
						students[i].delete_student();
						tmp = 1;
						break;

					}
					else
					{
						for (int j = i; j < last_student; j++)
						{
							students[j] = students[j + 1];
						}
						students[last_student].delete_student();
						tmp = 1;
						break;
					}
				}
			}
			if (tmp == 0)
			{
				cout << "\nДанного студента нет в базе данных";
			}
		}
		
	}

	
	
	
};

int main()
{
	SetConsoleCP(1251); //дичь, чтобы буквы адекватно выводились
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	menu m;
	m.main_menu();

}