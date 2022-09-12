#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include "Menu.h"



namespace myFD
{
	using std::cout;
	using std::cin;
	using std::ifstream;
	using std::ofstream;
	using std::string;
	using std::map;
	using std::multimap;
	using std::setw;
	using std::left;
	using std::right;
	using namespace MENU;
	

	class FD
	{
		map <string, int> m;
		multimap<int, string> top5;
		string file;
		bool check(const char c, const string s);
		void writeTop5();
		void saveAllwords() const;
		void saveTop5words() const;
		void readFile();

	public:
		FD() { this->readFile(); }
		void printFile() const;
		void printAllwords() const;
		void printTop5Words() const;
		void menu() const;
	};
	
	void myFD::FD::readFile()
	{
		string text;
		char temp{};
		string noread = " 0123456789!@#$%^&*()-_=+*/?.,<>~|';:\"\'\n\r\t";
		
		ifstream fin;

		fin.open("text.txt", std::ios::in);

		if (!fin)
		{
			std::cerr << "Помилка читання файлу...\n";
			exit(1);
		}


		if (fin.is_open())
			while (fin.read(&temp, sizeof(char)))
			{
				if (check(temp, noread))
					text += temp;
				else if (!check(temp, noread) && text.length() > 1)
				{
					m.emplace(text, 0);
					m[text] += 1;
					text.clear();
				}
				else
					text.clear();

				this->file += temp;
			}

		fin.close();

		writeTop5();
	}

	void myFD::FD::printAllwords() const
	{
		cout << "-----------------------------------------\n";
		cout << "         Частотний словник\n";
		cout << "-----------------------------------------\n";

		cout << setw(18) << left << "| Слово" << "|";
		cout << setw(5) << left << "Кількість застосувань|" << '\n';
			
			
			
		for (auto n : m)
		{
			cout << "-----------------------------------------\n";
			cout << setw(2) << left << "|";
			cout << setw(16) << left << n.first << "|";
			cout << setw(21) << right << n.second << "|\n";
			
		}
		cout << "-----------------------------------------\n";
		saveAllwords();
		system("pause");
	}

	bool myFD::FD::check(const char c, const string s)
	{
		for (size_t i{}; i < s.length(); i++)
		{
			if (c == s[i])
				return false;
		}
		return true;
	}

	void myFD::FD::printFile() const
	{
		cout << "-----------------------------------------\n";
		cout << "              Вміст файлу:\n";
		cout << "-----------------------------------------\n";
		cout << this->file << '\n';
		cout << "-----------------------------------------\n";
		system("pause");
	}

	void myFD::FD::writeTop5()
	{
		////Переписуємо в новий меп
			for (auto n : m)
				top5.emplace(n.second, n.first);
	}
	
	void myFD::FD::printTop5Words() const
	{
		cout << "-----------------------------------------\n";
		cout << "              ТОП 5 слів\n";
		cout << "-----------------------------------------\n";		
		cout << setw(22) << left << "|Кількість застосувань|";
		cout << setw(17) << left << "      Слово" << "|\n";



		int count{};

		for (auto it = top5.crbegin(); it != top5.crend(); ++it)
		{
			if (count < 5)
			{
				cout << "-----------------------------------------\n";
				cout << setw(10) << left << "|"; 
				cout << setw(12) << left << it->first << '|';
				cout << setw(17) << right << it->second << "|\n";
			}
			count++;
		}

		cout << "-----------------------------------------\n";
		saveTop5words();
		system("pause");
	}

	void FD::menu() const
	{
		while (true)
		{
			system("cls");
			int c = Menu::select_vertical({ "Роздрукувати вміст файлу",
											"Роздрукувати частотний словник",
											"Роздрукувати ТОП-5 вживаних слів",
											"Вихід" },
				HorizontalAlignment::Center, 5);

			switch (c)
			{
			case 0: printFile(); break;
			case 1: printAllwords(); break;
			case 2: printTop5Words(); break;
			case 3: exit(0);
			default:
				break;
			}
		}
	}

	void myFD::FD::saveAllwords() const
	{
		ofstream out;
		out.open("allword.txt", std::ios::out);

		if (!out)
		{
			std::cerr << "Помилка збереження файлу...";
			exit(1);
		}

		for (auto n : m)
			out << n.first << " " << n.second << '\n';

		out.close();
	}

	void myFD::FD::saveTop5words() const
	{
		ofstream out;
		out.open("top5word.txt", std::ios::out);

		if (!out)
		{
			std::cerr << "Помилка збереження файлу...";
			exit(1);
		}

		int count{};

		for (auto it = top5.crbegin(); it != top5.crend(); ++it)
		{
			if (count < 5)
			{
				out << it->first << " " << it->second << '\n';
			}
			count++;
		}

		out.close();
	}

}