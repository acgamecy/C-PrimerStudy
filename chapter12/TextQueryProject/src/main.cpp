#include <iostream>
#include <string>
#include <fstream>
#include "header/TextQuery.h"

void run(std::ifstream &infile)
{
	TextQuery tq(infile);
	while (true)
	{
		std::cout << "enter word to look for, or q to quit: ";
		std::string s;
		if (!(std::cin >> s) || s == "q") break;
		print(std::cout, tq.query(s));
	}
}

int main()
{
	std::ifstream infile("in.txt");
	if (infile)
	{
		run(infile);
		infile.close();
	}
	else
		std::cout << "open file failed." << std::endl;
	return 0;
}