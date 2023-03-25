#pragma once
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include "FileHandler.h"
#include "Node.h"

class Huffman
{
public:
	Huffman() = delete;
	Huffman(int argc, char* argv[]);

private:
	FileHandler fileHandler;

	std::fstream file{};
	std::string dataFromFile{};

	std::unordered_map<char, int> amountOfCharacters{};
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> sortedQueueOfNodes;

	void checkMode();

	void huffmanEncoding();
	void calculateAmountOfCharacters();
	void buildHuffmanTree();

	bool gatherDataFromFile(std::string path);
};

