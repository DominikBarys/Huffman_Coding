#pragma once
#include <iostream>
#include <string>

enum Mode{NONE ,INPUT, OUTPUT};

class FileHandler
{
public:
	FileHandler() = delete;
	FileHandler(int argc, char* argv[]);

private:
	std::string inputFilePath{};
	std::string outputFilePath{};
	std::string dictionaryPath{};
	Mode mode = NONE;

	bool checkInputParams();
};

