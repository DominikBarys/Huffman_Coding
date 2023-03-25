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
	const std::string EMPTY_STRING = "";
	FileHandler fileHandler;
	Node* root = nullptr;

	std::fstream file{};
	std::string dataFromFile{};
	std::string encodedString{};
	std::string stringOfHuffmanCodes{};
	std::vector<char> buffer{};

	std::unordered_map<char, int> amountOfCharacters{};
	std::unordered_map<char, std::string> huffmanCode{};
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> sortedQueueOfNodes{};

	Node* makeNode(char character, int amount, Node* left, Node* right);

	void checkMode();

	void huffmanEncoding();
	void makeHuffmanCode(Node* node, std::string code, std::unordered_map<char, std::string> huffmanCode);
	bool isLeaf(Node* node);
	void makeDictionary();
	void makeStringOfHuffmanCodes();

	void convertToBytes();

	void calculateAmountOfCharacters();
	void buildHuffmanTree();

	bool gatherDataFromFile(std::string path);
};

