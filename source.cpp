#include "frequency-dictionary.h"


using namespace myFD;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FD dictionary;
	dictionary.readFile();
	dictionary.printFile();
	dictionary.printAllwords();
	dictionary.printTop5Words();

    return 0;
}
