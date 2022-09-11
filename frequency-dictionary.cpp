#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <map>

using std::cout;
using std::cin;
using std::ifstream;
using std::string;
using std::map;


bool check(const char c, const string s)
{
	for (size_t i{}; i < s.length(); i++)
	{
		if (c == s[i])
			return false;
	}
	return true;
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
		
	string text;
	char temp{};


	ifstream fin;
	string noread = "\"!@#$%^&*()_+-=\|?/><,.~\n1234567890";

	map <string, int> m;







	fin.open("text.txt", std::ios::in);

	if (!fin)
	{
		std::cerr << "Помилка читання файлу...\n";
		exit(1);
	}
	//else
	//	cout << "Файл завантажено\n";

	if (fin.is_open())
	{
		while (fin.read(&temp, sizeof(char)))
		{
			if (check(temp, noread))
			{
				if (temp != char(32))
					text += temp;
				else if (temp == char(32))
				{
					//m.insert(make_pair(text,+1));
					m.emplace(text,0);
					m[text] += 1;
					text.clear();
				}
			}
		}
			
	}


	fin.close();
	



	cout << text;

	
	for (auto n : m)
	{
		cout << n.first << " --- " << n.second << '\n';
	}


    return 0;
}
