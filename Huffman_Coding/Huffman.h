#pragma once
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <thread>
#include "UserInterface.h"

class Huffman
{
public:
	Huffman() = delete;
	Huffman(std::string input, std::string output, std::string dictionary);
	~Huffman();

protected:

	std::string inputFilePath{};
	std::string outputFilePath{};
	std::string dictionaryPath{};

	std::string dataFromFile{};
	std::fstream file{};
	int shift{};

	bool gatherDataFromFile(std::string path);

private:

	std::vector<std::thread> uiThreads{};

	void makeUiThreads();
	void joinThreads();
};

