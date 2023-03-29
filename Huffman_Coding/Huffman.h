#pragma once
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <thread>
#include "FileHandler.h"
#include "Node.h"
#include "UserInterface.h"

//TO DO Support for different types of files, not only files like txt, bmp or jpeg

class Huffman
{
public:
	Huffman() = delete;
	Huffman(int argc, char* argv[]);
	~Huffman();

private:

	std::vector<std::thread> uiThreads;

	const std::string EMPTY_STRING = "";
	FileHandler fileHandler;
	Node* root = nullptr;

	std::fstream file{};
	std::string dataFromFile{};
	std::string encodedString{};
	std::string decodedString{};
	std::string stringOfHuffmanCodes{};
	std::vector<char> buffer{};
	int shift{};
	char charFromDictionary{};

	std::unordered_map<char, int> amountOfCharacters{};
	std::unordered_map<char, std::string> huffmanCode{};
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> sortedQueueOfNodes{};
	std::vector <std::pair<char, std::string>> huffmanCodeFromDictionary{};

	Node* makeNode(char character, int amount, Node* left, Node* right);

	void checkMode();

	void huffmanEncoding();
	void makeHuffmanCode(Node* node, std::string code, std::unordered_map<char, std::string>& huffmanCode);
	bool isLeaf(Node* node);
	void makeDictionary();
	void makeStringOfHuffmanCodes();
	void makeEncodedFile();
	void convertToBytes();
	void calculateAmountOfCharacters();
	void buildHuffmanTree();

	void huffmanDecoding();

	bool gatherDataFromFile(std::string path);
	bool gatherDataFromDictionary(std::string path);
	void gatherShiftFromEncodedFile();
	void fromBytesToString();
	void translateHuffmanCode();
	void saveDecodedFile(std::string);

	void makeUiThreads();
	void joinThreads();
};

