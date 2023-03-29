#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <regex>

//TO DO Handling only names of files by adding to it native directory to program folder

class Huffman;

enum Mode{NONE ,ENCODE, DECODE};

class FileHandler
{
public:
	FileHandler() = default;
	FileHandler(int argc, char* argv[]);

private:
	std::string inputFilePath{};
	std::string outputFilePath{};
	std::string dictionaryPath{};
	Mode mode = NONE;

	std::regex ruleForFilepath{ ".+(?=\\\\)" };

	std::filesystem::path directoryPath = std::filesystem::current_path();

	void checkInputParams();
	void extractParameters(int argc, char* argv[]);

	friend class Huffman;
};

