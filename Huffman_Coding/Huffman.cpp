#include "Huffman.h"

Huffman::Huffman(int argc, char* argv[])
{
	fileHandler = FileHandler(argc, argv);
	checkMode();
}

Node* Huffman::makeNode(char character, int amount, Node* left, Node* right)
{
	Node* node = new Node(character, amount, left, right);
	return node;
}

void Huffman::checkMode()
{
	if (fileHandler.mode == ENCODE)
	{
		huffmanEncoding();
	}
	else if (fileHandler.mode == DECODE)
	{
		std::cout << "Output\n";
	}
	else if (fileHandler.mode == NONE)
	{
		std::cout << "The input parameters are invalid\n";
	}
}

void Huffman::huffmanEncoding()
{
	if (!gatherDataFromFile(fileHandler.inputFilePath))
		return;

	calculateAmountOfCharacters();

	buildHuffmanTree();
}

void Huffman::calculateAmountOfCharacters()
{
	for (auto character : dataFromFile)
	{
		amountOfCharacters[character]++;
	}
}

void Huffman::buildHuffmanTree()
{
	for (auto pair : amountOfCharacters)
	{
		sortedQueueOfNodes.push(makeNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (sortedQueueOfNodes.size() != 1)
	{
		Node* left = sortedQueueOfNodes.top();
		sortedQueueOfNodes.pop();
		Node* right = sortedQueueOfNodes.top();
		sortedQueueOfNodes.pop();

		int sum = left->getAmount() + right->getAmount();

		sortedQueueOfNodes.push(makeNode('/0', sum, left, right));
	}
}

bool Huffman::gatherDataFromFile(std::string path)
{
	file.open(fileHandler.inputFilePath);

	if (!file.good())
	{
		std::cout << "File not found\n";
		return false;
	}

	while (std::getline(file, dataFromFile))
		file.close();

	return true;
}
