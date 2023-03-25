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

	makeHuffmanCode(root, EMPTY_STRING, huffmanCode);
}

void Huffman::makeHuffmanCode(Node* node, std::string code, std::unordered_map<char, std::string> huffmanCode)
{
	if (node == nullptr)
		return;

	if (isLeaf(node))
		huffmanCode[node->getChar()] = code;

	makeHuffmanCode(node->getLeftNode(), code + "0", huffmanCode);
	makeHuffmanCode(node->getRightNode(), code + "1", huffmanCode);
}

bool Huffman::isLeaf(Node* node)
{
	return node->getLeftNode() == nullptr && node->getRightNode() == nullptr;
}

void Huffman::makeDictionary()
{
	file.open(fileHandler.dictionaryPath);

	for (auto pair : huffmanCode)
	{
		file.put(pair.first);
		file.put('\n');
		file.write(pair.second.c_str(), pair.second.size());
		file.put('\n');
	}
}

void Huffman::makeStringOfHuffmanCodes()
{
	for (char ch : dataFromFile)
	{
		stringOfHuffmanCodes += huffmanCode[ch];
	}
}

void Huffman::convertToBytes()
{
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

	root = sortedQueueOfNodes.top();
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
