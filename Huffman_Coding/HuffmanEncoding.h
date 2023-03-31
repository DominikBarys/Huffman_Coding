#pragma once
#include "Huffman.h"
#include "Node.h"

class HuffmanEncoding : public Huffman
{
public:
	HuffmanEncoding() = delete;
	HuffmanEncoding(std::string input, std::string output, std::string dictionary);
	~HuffmanEncoding();

private:
	const std::string EMPTY_STRING = "";
	Node* root = nullptr;
	std::unordered_map<char, int> amountOfCharacters{};
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> sortedQueueOfNodes{};
	std::unordered_map<char, std::string> huffmanCode{};
	std::string stringOfHuffmanCodes{};
	std::vector<char> buffer{};


	void startEncodingSequence();

	Node* makeNode(char character, int amount, Node* left, Node* right);
	bool isLeaf(Node* node);
	void calculateAmountOfCharacters();
	void buildHuffmanTree();
	void makeHuffmanCode(Node* node, std::string code, std::unordered_map<char, std::string>& huffmanCode);
	void makeDictionary();
	void makeStringOfHuffmanCodes();
	void convertToBytes();
	void makeEncodedFile();
};

