#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <regex>

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
	std::string setFilepathToResources(std::string path);

	friend class Huffman;
};

