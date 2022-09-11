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
	//string noread = "\n\"'!@#$%^&*()_+-=\/><?,.~1234567890";
	string noread = "0123456789!@#$%^&*()-_=+*/?.,<>~|';:\"\n\r\t";
	




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
					m.emplace(text, 0);
					m[text] += 1;
					text.clear();
				}
			}
			else
			{
				m.emplace(text, 0);
				m[text] += 1;
				text.clear();
			}
			
		}
	}


	fin.close();


	for (auto n : m)
	{
		cout << n.first << " --- " << n.second << '\n';
	}

	cout << "\n\nTOP5:\n";

	std::multimap<int, string> top5;


	for (auto n : m)
		top5.emplace(n.second, n.first);

	int i{};
	for (auto it = top5.crbegin(); it != top5.crend(); ++it)
	{

		if (i < 5)
		{
			std::cout << it->first << " : " << it->second << '\n';
			i++;
		}
	}



	//for (auto n : top5)
	//{
	//	cout << n.first << " --- " << n.second << '\n';
	//}

    return 0;
}
