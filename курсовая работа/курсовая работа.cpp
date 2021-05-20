#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <clocale>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
const string path = "studentsdb.txt";
#define LINE_LENGTH 140;
#define head1 "|              Фамилия              |                Имя                |             Отчество              | Дата рождения |  Пол  |\n"
#define head2 "|           Год поступления         |             Факультет             |             Кафедра               |             Группа             |      Номер зачетной книжки         |\n"
const int BLOCK_SIZE = 35;
const int  DATE_SIZE =  15;
const int SEX_SIZE =  7;
const int NUMBER_OF_SUBJECTS = 9;
const int NUMBER_OF_SESSIONS = 10;
int last_student = 0;
const int NUMBER_OF_STUDENTS = 100;
string students_record_book[NUMBER_OF_STUDENTS];
#define line cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------\n"
struct sub
{
	string name = "unknown"; 
	int mark = 0; 
};
class input_output
{
public:
	
	void cin_clear() 
	{
		cin.seekg(0, ios::end); 
		cin.clear(); 
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
						cout << "Дата введена неверно\n";
						break;
					}
				}
				else
				{
					cout << "Месяц должен быть от 1 до 12\n";
				}
			}
			else
			{
				cout << "Год должен быть от 1900 до 2020\n";
			}
		}
		cout << "Неверная дата\n";
		return false;
	}

	int protection_incoming_year()
	{
		string year;
		int number = 0;
		while (true)
		{
			cout << "\nВведите год постулпения: ";
			cin >> year;
			if (isdigit(year[0]) and isdigit(year[1]) and isdigit(year[2]) and isdigit(year[3]) and year.length() == 4)
			{
				number = string_to_int(year);
				if (number >= 1900 and number <= 2020)
				{
					return number;
				}
				cout << "\nГод введен неправильно: год должен быть больше 1900 и меньше 2020";
				continue;
			}
			cout << "\nГод - число целого типа";
		}
	}

	char protection_sex()
	{
		string gender;
		while (true)
		{
			cout << "\nУкажите пол студента: ";
			cin >> gender;
			if (gender == "М" or gender == "Ж") 
			{
				cin_clear();
				return gender[0];
			}
			else
			{
				cout << "\nПол введен неверно, повторите ввод" << endl;
				cin_clear();
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
			number1 += (static_cast<int>(number[i] )-48)* ten;
			ten /= 10;
		}
		return number1;
	}
};

class session
{
protected:
	sub exams[NUMBER_OF_SESSIONS][NUMBER_OF_SUBJECTS];
	double middle_mark[NUMBER_OF_SESSIONS];


public:
	friend class menu;
	friend class student;
	void clear_info()
	{
		for (int i = 0; exams[i][0].name != "unknown"; i++)
		{
			for (int j = 0; exams[i][j].name != "unknown"; j++)
			{
				exams[i][j].name = "unknown";
			}
		}
	}
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

	void set_middle_marks()
	{
		double total = 0;
		int count = 0;
		for (int i = 0; exams[i][0].name != "unknown"; i++)
		{
			for (int j = 0; exams[i][j].name != "unknown"; j++)
			{
				count++;
				total += exams[i][j].mark;
			}
			middle_mark[i] = total / count;
			total = 0;
			count = 0;
		}
	}
	double get_middle_mark(int number_of_session)
	{
		return middle_mark[number_of_session];
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
};



struct FIO
{
	string name; 
	string second_name; 
	string middle_name; 
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
		FIO fio; 
		date bday; 
		int* incoming_year; 
		char* sex = NULL;
		char* faculty = NULL;
		char* kafedra = NULL;
		char* group = NULL;
		char* record_book = NULL;
		session sessions;
		int student_number;
	public:
		friend class menu;
		
		student() 
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
			student_number = 0;
		}

		bool subject_check(string subject)
		{
			for (int i = 0; sessions.exams[i][0].name != "unknown"; i++)
			{
				for (int j = 0; sessions.exams[i][j].name != "unknown"; j++)
				{
					if (sessions.exams[i][j].name == subject)
					{
						return true;
					}
				}
			}
			return false;
		}

		char* get_record_book()
		{
			
			return record_book;
		}

		string get_record_book_s()
		{
			string rb = string(record_book);
			return record_book;
			
		}
		~student() //особождает все поля класса
		{
			if (bday.day != NULL)
			{
				delete(bday.day);
			}
			if (bday.month != NULL)
			{
				delete(bday.month);
			}
			if (bday.year != NULL)
			{
				delete(bday.year);
			}
			if (incoming_year != NULL)
			{
				delete(incoming_year);
			}
			if (faculty != NULL)
			{
				delete(faculty);
			}
			if (kafedra != NULL)
			{
				delete(kafedra);
			}
			if (group != NULL)
			{
				delete(group);
			}
			if (record_book != NULL)
			{
				delete(record_book);
			}
		}
		void clear_sessions()
		{
			sessions.clear_info();
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
			sessions.set_middle_marks();
		}

		void set_id(int student_num)
		{
			student_number = student_num;
		}

		double get_middle_mark(int number_of_session)
		{
			return sessions.get_middle_mark(number_of_session);
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
				cin.ignore(INT_MAX, '\n');
				if (is_int_string(number_of_sessions))
				{
					number_of_sessions2 = atoi(number_of_sessions.c_str());
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
							cin.ignore(INT_MAX, '\n');
							
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

		void show_all()
		{
			cout << "Студент: " << student_number << endl;
			cout << head1;
			cout << "|" << setw(BLOCK_SIZE) << left << fio.second_name <<"|" <<setw(BLOCK_SIZE) << left << fio.name << "|" << setw(BLOCK_SIZE) << left << fio.middle_name << "|" << *bday.day << "." << *bday.month << "." << *bday.year << "      |" << *sex <<"      |" << endl;
			line;
			cout << head2;
			cout <<"|" <<  setw(BLOCK_SIZE) << left << *incoming_year << "|" << setw(BLOCK_SIZE) << left << faculty << "|" << setw(BLOCK_SIZE) << left << kafedra << "|" << setw(BLOCK_SIZE) << left << group << setw(BLOCK_SIZE) << left << record_book << endl;
			line;
			sessions.show_all();
			cout << endl;
		}

		//все сэттеры
		 void set_name()
		{
				 cout << "\nВведите имя студента: ";
				 cin >> fio.name;
				 cin.ignore(INT_MAX, '\n');
		}

		 void set_name(string name)
		 {
			 fio.name = name;
		 }

		 void set_second_name()
		 {
			 
				 cout << "\nВведите фамилию студента: ";
				 cin >> fio.second_name;
				 cin.ignore(INT_MAX, '\n');
		 }

		 void set_second_name(string second_name)
		 {
			 fio.second_name = second_name;
		 }
		 void set_middle_name()
		 {
				 cout << "\nВведите отчество студента: ";
				 cin >> fio.middle_name;
				 cin.ignore(INT_MAX, '\n');
		 }

		 void set_middle_name(string middle_name)
		 {
			 fio.middle_name = middle_name;
		 }
		 void set_incoming_year()
		 {
			 *incoming_year = protection_incoming_year();
			 cin_clear();
		 }
		 void set_incoming_year(int in_year)
		 {
			 *incoming_year = in_year;
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

		 void set_bday(int day, int month, int year)
		 {
			 *bday.day = day;
			 *bday.month = month;
			 *bday.year = year;
		 }

		 void set_record_book()
		 {
			 string rec_book;
			 int ten;
			 bool tmp = true;
			 while (true)
			 {
				 cout << "\nВведите номер зачетное книжки студента: ";
				 cin >> rec_book;
				 for (int i = 0; i < last_student; i++)
				 {
					 if (rec_book == students_record_book[i])
					 {
						 cout << "\nТакой номер зачетной книжки уже существует";
						 tmp = false;
						 break;
					 }
					 tmp = true;
				 }
				 if (!tmp)
				 {
					 continue;
				 }
				 
				int len = rec_book.length();
				for (int i = 0; i < len; i++)
				{
					*(record_book + i) = rec_book[i];
				}
				*(record_book + rec_book.length()) = '\0';
			 }
		 }

		 void set_record_book(string rbook)
		 {
			 int len = rbook.length();
			 for (int i = 0; i < len; i++)
			 {
				 *(record_book + i) = rbook[i];
			 }
			 *(record_book + rbook.length()) = '\0';
		 }
		 
		 void set_sex()
		 {
			 *sex = protection_sex();
		 }

		 void set_sex(char sex1)
		 {
			 *sex = sex1;
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
					 if (tmp != NULL)
					 {
						 free(tmp);
					 }
					 break;

				 }
				 else
				 {
					 cout << "\nНазвание факультета введено некорректно";
				 }
			 }
		 }
		 void set_faculty(string fc)
		 {
			 int len = fc.length();
			 for (int i = 0; i < len; i++)
			 {
				 faculty[i] = fc[i];
			 }
			 faculty[len] = '\0';
		 }
		 void set_group()
		 {
			 cout << "\nВведите название группы: ";
			 cin >> group;
			 cin.ignore(INT_MAX, '\n');
		 }

		 void set_group(string gr)
		 {
			 strcpy(group, gr.c_str());
		 }

		 void set_kafedra()
		 { 
			cout << "\nВведите кафедру студента: ";
			cin >> kafedra;
			cin_clear();
		 }

		 void set_kafedra(string kaf)
		 {
			 int len = kaf.length();
			 for (int i = 0; i < len; i++)
			 {
				 kafedra[i] = kaf[i];
			 }
			 kafedra[len] = '\0';
		 }

		 int get_id()
		 {
			 return student_number;
		 }

		
		
		 void operator[](const int index) 
		 {
			 ifstream file(path); 
			 string buf;
			 for (int i = 0; i < index; i++) 
			 {
				 getline(file, buf, 'N'); 
				 file.ignore(1, '\n');
			 }
			 
			 file.getline(record_book, 100, '\n');
			 getline(file, fio.name, '\n'); 
			 getline(file, fio.second_name, '\n'); 
			 getline(file, fio.middle_name, '\n'); 
			 file >> *sex; 
			 file >> *bday.day; 
			 file >> *bday.month; 
			 file >> *bday.year;
			 file >> *incoming_year;
			 string fc;
			 file.ignore(1, '\n');
			 getline(file, fc, '\n');
			 set_faculty(fc);
			 string kf;
			 getline(file, kf, '\n');
			 set_kafedra(kf);
			 string gr;
			 getline(file, gr, '\n');
			 set_group(gr);
			 sessions.clear_info();
			 while (true) 
			 {
				 string subject;
				 getline(file, subject, '\n');
				 if (subject == "N")
				 {
					 break;
				 }
				 int mark, number_of_session;
				 file >> mark >> number_of_session;
				 sessions.set_subject(number_of_session, subject);
				 sessions.set_mark(mark, number_of_session, subject);
				 file.ignore(1, '\n');
			 }
			 sessions.set_middle_marks();
			 file.close();
		 }

};

class menu : public input_output
{
private:
	student students;
	int choose = 0;
	bool idk = true;
public:
	menu()
	{
		ifstream file(path);
		while (!file.eof())
		{
			string line1;
			getline(file, line1, '\n');
			if (line1 == "N")
			{
				last_student++;
			}
			else if (line1 == "&")
			{
				break;
			}
		}
		file.close();
		for (int i = 0; i < last_student; i++)
		{
			students[i];
			students_record_book[i] = students.get_record_book_s();
		}
	}

	void main_menu()
	{
		while (idk)
		{

			choose = show_menu();
			switch(choose)
			{
				case 1:
					students.clear_sessions();
					students.set_all();
					add_student_to_db(path);
					break;
				case 2:
					for (int i = 0; i < last_student; i++)
					{
						students[i];
						students.set_id(i + 1);
						students.show_all();
					}
					break;
				case 3:
					delete_student1();
					break;
				case 4:
					find_student1();
					break;
				case 5:
					cout << "\nВведите номер сессии: ";
					int number_of_session;
					cin >> number_of_session;
					sort1(number_of_session - 1);
					break;
				case 6:
					cout << "\nВведите номер зачетной книжки студента, данные о котором нужно изменить: ";
					char rb[100];
					cin >> rb;
					cin.ignore(INT_MAX, '\n');
					change_info(rb);
					break;
				case 7:
					idk = false;
					break;
			}
		}
	}

	int change_info(char rb[])
	{
		ifstream file(path);
		bool idk = true;
		int student_number = 0;
		string student_info;
		while (idk)
		{
			getline(file, student_info, '\n');
			if (student_info == rb)
			{
				idk = false;
			}
			else if (student_info == "&")
			{
				cout << "\nВ базе данных не студента, с таким номером зачетной книжки";
				return 1;
			}
			else
			{
				getline(file, student_info, 'N');				
				file.ignore(1, '\n');
				student_number++;
			}
		}
		file.close();
		students[student_number];
		delete_student(rb);

		cout << "\n[1] - Изменить Имя Студента";
		cout << "\n[2] - Изменить Фамилию Студента";
		cout << "\n[3] - Изменить Отчество Студента";
		cout << "\n[4] - Изменить дату рождения Студента";
		cout << "\n[5] - Изменить год поступления Студента";
		cout << "\n[6] - Изменить факультет Студента";
		cout << "\n[7] - Изменить кафедру Студента";
		cout << "\n[8] - Изменить группу Студента";
		cout << "\n[9] - Изменить оценки за определенные предметы в определенных сессия";
		cout << "\n>>>>>>> ";
		string choice;
		cin >> choice;
		if (is_int_string(choice))
		{
			int ch = string_to_int(choice);
			if (ch >= 1 and ch <= 9)
			{
				switch (ch)
				{
				case 1:
					students.set_name();
					add_student_to_db(path);
					break;
				case 2:
					students.set_second_name();
					add_student_to_db(path);
					break;
				case 3:
					students.set_middle_name();
					add_student_to_db(path);
					break;
				case 4:
					students.set_bday();
					add_student_to_db(path);
					break;
				case 5:
					students.set_incoming_year();
					add_student_to_db(path);
					break;
				case 6:
					students.set_faculty();
					add_student_to_db(path);
					break;
				case 7:
					students.set_kafedra();
					add_student_to_db(path);
					break;
				case 8:
					students.set_group();
					add_student_to_db(path);
					break;
				case 9:
					cout << "\nВведите номер сессии: ";
					string ns;
					cin >> ns;
					cin.ignore(INT_MAX, '\n');
					if (is_int_string(ns))
					{
						int ns1 = string_to_int(ns);
						cout << "\nВведите название предмета: ";
						string subject;
						cin >> subject;
						cin.ignore(INT_MAX, '\n');
						cout << "\nВведите оценку за этот предмет: ";
						string mark;
						cin >> mark;
						cin.ignore(INT_MAX, '\n');
						if (is_int_string(mark))
						{
							if (string_to_int(mark) >= 2 and string_to_int(mark) <= 5)
							{
								if (students.subject_check(subject))
								{
									students.sessions.set_mark(string_to_int(mark), ns1, subject);
								}
								else
								{
									students.sessions.set_subject(ns1, subject);
									students.sessions.set_mark(string_to_int(mark), ns1, subject);
								}
							}
						}
						else
						{
							cout << "\nОценка введена неверно";
						}
					}
					else
					{
						cout << "\nНомер сессии веден неверно";
					}
					add_student_to_db(path);
					break;
				}
			}
		}

	}
	void sort1(int number_of_session)
	{
		double max = -1;
		int max_index = 0;
		student s;
		for (int i = last_student; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				student s;
				s[j];
				if (s.get_middle_mark(number_of_session) > max)
				{
					max = s.get_middle_mark(number_of_session);
					max_index = j;
				}
			}
			s[max_index];
			delete_student(s.get_record_book());
			add_student_to_db(path);
			max = 0; max_index = 0;
		}
	}

	void add_student_to_db(string name)
	{
		fstream outfile(name);
		outfile.seekp(-1, ios::end);
		outfile << students.record_book << '\n';
		outfile << students.fio.name << '\n';
		outfile << students.fio.second_name << '\n';
		outfile << students.fio.middle_name << '\n';
		outfile << *students.sex << '\n';
		outfile << *students.bday.day << '\n';
		outfile << *students.bday.month << '\n';
		outfile << *students.bday.year << '\n';
		outfile << *students.incoming_year << '\n';
		outfile << students.faculty << '\n';
		outfile << students.kafedra << '\n';
		outfile << students.group << '\n';
		for (int i = 0; students.sessions.exams[i][0].name != "unknown"; i++)
		{
			for (int j = 0; students.sessions.exams[i][j].name != "unknown"; j++)
			{
				outfile << students.sessions.exams[i][j].name << '\n';
				outfile << students.sessions.exams[i][j].mark << " " << i + 1;
				outfile << '\n';
			}
		}
		outfile << 'N' << '\n';
		outfile << '&';
		last_student++;
	}

	void find_student1()
	{
		bool is_found = false;
		cout << "\nВведите номер зачетной книжки студента, информацию о котором вы хотите получить: ";
		cin.ignore(32767, '\n');
		string rb;
		getline(cin, rb);
		for (int i = 0; i < last_student; i++)
		{
			students[i];
			if (students.get_record_book_s() == rb)
			{
				students.show_all();
				is_found = true;
			}
		}
		if (!is_found)
		{
			cout << "\nТакого студента в базе данных нет";
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
			cout << "\n[4] - Найти студента по номеру зачетной книжки: ";
			cout << "\n[5] - Сортировка: ";
			cout << "\n[6] - Изменить информацию о студенте: ";
			cout << "\n[7] - Выйти из программы: ";
			cout << "\n>>>>>>>>> ";
			cin >> ch;
			system("cls");
			cin.ignore(INT_MAX, '\n');
			if (is_int_string(ch))
			{
				int one = string_to_int(ch);
				if (one >= 1 and one <= 7)
				{
					return one;
				}
				else
				{
					cout << "\nТакого вариант не существует, попробуйте заново";
				}
			}
			else
			{
				cout << "\nВы должны ввести число, соотвествующее определенной функции программы";
			}
		}
	}
	void delete_student1()
	{
		if (last_student == 0)
		{
			cout << "\nВ базе данных нет студентов";
		}
		else
		{
			cout << "\nВведите номер зачетной книжки студента, которого нужно удалить: ";
			char rb[100];
			cin >> rb;
			cin.ignore(INT_MAX, '\n');
			delete_student(rb);
			cout << "\nУдаление произошло успешно!";
		}
	}

	void delete_student(char* record_book)
	{
		for (int i = 0; i < last_student; i++)
		{
			students[i];
			if (!strcmp(students.get_record_book(), record_book))
			{
				last_student--;
				ifstream file(path);
				ofstream outfile("newstudentdb.txt");
				while (!file.eof())
				{
					string line1;
					getline(file, line1, '\n');
					if (line1 == record_book)
					{
						string buff;
						getline(file, buff, 'N');
						file.ignore(1, 'N');
						continue;
					}
					else if (line1 == "&")
					{
						break;
					}
					outfile << line1 + "\n";
				}
				file.close();
				outfile << "&";
				outfile.close();
				remove("studentsdb.txt");
				char oldname[] = "newstudentdb.txt";
				char newname[] = "studentsdb.txt";
				rename(oldname, newname);
				break;
			}
		}
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	setlocale(0, "Rus");
	menu m;
	m.main_menu();
	return 1;
}