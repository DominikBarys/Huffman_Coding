#include "HuffmanEncoding.h"

HuffmanEncoding::HuffmanEncoding(std::string input, std::string output, std::string dictionary)
	:Huffman(input,output,dictionary)
{
	startEncodingSequence();
}

HuffmanEncoding::~HuffmanEncoding()
{
	if (root != nullptr)
		delete root;
}

void HuffmanEncoding::startEncodingSequence()
{
	if (!gatherDataFromFile(inputFilePath))
		return;

	calculateAmountOfCharacters();

	buildHuffmanTree();

	makeHuffmanCode(root, EMPTY_STRING, huffmanCode);

	makeDictionary();

	makeStringOfHuffmanCodes();

	convertToBytes();

	makeEncodedFile();
}

Node* HuffmanEncoding::makeNode(char character, int amount, Node* left, Node* right)
{
	Node* node = new Node(character, amount, left, right);
	return node;
}

bool HuffmanEncoding::isLeaf(Node* node)
{
	return node->getLeftNode() == nullptr && node->getRightNode() == nullptr;
}

void HuffmanEncoding::calculateAmountOfCharacters()
{
	for (auto character : dataFromFile)
	{
		amountOfCharacters[character]++;
	}
}

void HuffmanEncoding::buildHuffmanTree()
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

void HuffmanEncoding::makeHuffmanCode(Node* node, std::string code, std::unordered_map<char, std::string>& huffmanCode)
{
	if (node == nullptr)
		return;

	if (isLeaf(node))
		huffmanCode[node->getChar()] = code;

	makeHuffmanCode(node->getLeftNode(), code + "0", huffmanCode);
	makeHuffmanCode(node->getRightNode(), code + "1", huffmanCode);
}

void HuffmanEncoding::makeDictionary()
{
	file.open(dictionaryPath, std::ios::out | std::ios::binary);

	for (auto pair : huffmanCode)
	{
		file.put(pair.first);
		file.put('\n');
		file.write(pair.second.c_str(), pair.second.size());
		file.put('\n');
	}

	file.close();
}

void HuffmanEncoding::makeStringOfHuffmanCodes()
{
	for (char ch : dataFromFile)
	{
		stringOfHuffmanCodes += huffmanCode[ch];
	}
}

void HuffmanEncoding::convertToBytes()
{
	int counter = 0;
	unsigned char byte = 0;

	for (unsigned char bit : stringOfHuffmanCodes)
	{
		if (counter > 7)
		{
			buffer.push_back(byte);
			counter = 0;
		}
		if (bit == '0')
		{
			byte = (byte << 1) & 0xFE;
		}
		else
		{
			byte = (byte << 1) | 0x01;
		}
		counter++;
	}

	shift = counter;

	if (counter > 0)
	{
		byte = (byte << (8 - shift));
		buffer.push_back(byte);
	}

	shift += 48;
}

void HuffmanEncoding::makeEncodedFile()
{
	file.open(outputFilePath, std::ios::out | std::ios::binary);
	file.put(shift);
	std::copy(buffer.begin(), buffer.end(), std::ostreambuf_iterator<char>(file));
	file.close();
}