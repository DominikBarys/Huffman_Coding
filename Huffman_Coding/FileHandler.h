#pragma once
#include <iostream>
#include <string>

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

	friend class Huffman;

};

