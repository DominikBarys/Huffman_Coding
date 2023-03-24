#pragma once
#include <fstream>
#include <unordered_map>
#include "FileHandler.h"

class Huffman
{
public:
	Huffman() = delete;
	Huffman(int argc, char* argv[]);

private:
	FileHandler fileHandler;

	std::fstream file;
	std::string dataFromFile;

	std::unordered_map<char, int> amountOfCharacters;

	void checkMode();

	void huffmanEncoding();
	void calculateAmountOfCharacters();
	bool gatherDataFromFile(std::string path);
};

