#pragma once
#include <filesystem>
#include <regex>
#include "HuffmanDecoding.h"
#include "HuffmanEncoding.h"

enum Mode{NONE ,ENCODE, DECODE};

class FileHandler
{
public:
	FileHandler() = default;
	FileHandler(int argc, char* argv[]);
	~FileHandler();

private:
	std::string inputFilePath{};
	std::string outputFilePath{};
	std::string dictionaryPath{};

	Mode mode = NONE;
	Huffman* huffman;

	const std::regex ruleForFilepath{ ".+(?=\\\\)" };

	std::filesystem::path directoryPath = std::filesystem::current_path();

	void startProgram(Mode mode);
	void checkInputParams();
	void extractParameters(int argc, char* argv[]);
	std::string setFilepathToResources(std::string path);
};

