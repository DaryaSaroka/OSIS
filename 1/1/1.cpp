#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

int main()
{
	char filename[25];
	std::string format;
	printf("Enter file name\n");
	scanf("%s", filename);
	printf("Enter format\n");

	freopen(filename, "a+", stdout);
	std::cin >> format;

	std::string path = "./";
	for (auto& p : fs::directory_iterator(path))
	{
		std::string filepath = p.path().u8string();
		if (filepath.find("." + format) != std::string::npos) {
			std::cout << filepath.substr(2) << std::endl;
		}
	}

	//system("pause");
	return 0;
}
