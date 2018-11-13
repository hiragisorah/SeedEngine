#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main(void)
{
	std::string file_name = "test.txt";

	fs::file_time_type file_time = fs::file_time_type::min();

	while (1)
	{
		while (file_time == fs::last_write_time(file_name));

		file_time = fs::last_write_time(file_name);

		system("cls");

		std::ifstream is;
		is.open(file_name);
		
		if (is.fail()) continue;

		std::string str;
		while (is.good())
		{
			is >> str;
			std::cout << str.c_str() << std::endl;
		}

		is.close();
	}

	rewind(stdin);
	getchar();

	return 0;
}