#include "Huffman.h"

Huffman::Huffman(int argc, char* argv[])
{
	makeUiThreads();
	UserInterface::startOfProgram();
	fileHandler = FileHandler(argc, argv);
	checkMode();
}

Huffman::~Huffman()
{
	if (root != nullptr)
		delete root;
}

Node* Huffman::makeNode(char character, int amount, Node* left, Node* right)
{
	Node* node = new Node(character, amount, left, right);
	return node;
}

void Huffman::checkMode()
{
	switch (fileHandler.mode)
	{
	case ENCODE:
		huffmanEncoding();
		break;
	case DECODE:
		huffmanDecoding();
		break;
	case NONE:
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

	makeDictionary();

	makeStringOfHuffmanCodes();

	convertToBytes();

	makeEncodedFile();

	Sleep(50000); /////////////////

	UserInterface::endOfProgram();

	joinThreads();
}

void Huffman::makeHuffmanCode(Node* node, std::string code, std::unordered_map<char, std::string>& huffmanCode)
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
	file.open(fileHandler.dictionaryPath, std::ios::out);

	for (auto pair : huffmanCode)
	{
		file.put(pair.first);
		file.put('\n');
		file.write(pair.second.c_str(), pair.second.size());
		file.put('\n');
	}

	file.close();
}

void Huffman::makeStringOfHuffmanCodes()
{
	for (char ch : dataFromFile)
	{
		stringOfHuffmanCodes += huffmanCode[ch];
	}
}

void Huffman::makeEncodedFile()
{
	file.open(fileHandler.outputFilePath, std::ios::out | std::ios::binary);
	file.put(shift);
	std::copy(buffer.begin(), buffer.end(), std::ostreambuf_iterator<char>(file));
	file.close();
}

void Huffman::convertToBytes()
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

void Huffman::calculateAmountOfCharacters()
{
	for (auto character : dataFromFile)
	{
		amountOfCharacters[character]++;
	}
}

void Huffman::buildHuffmanTree() //progess bar?
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

void Huffman::huffmanDecoding()
{
	if (!gatherDataFromDictionary(fileHandler.dictionaryPath))
		return;

	if (!gatherDataFromFile(fileHandler.inputFilePath))
		return;

	gatherShiftFromEncodedFile();

	fromBytesToString();

	translateHuffmanCode();

	saveDecodedFile(fileHandler.outputFilePath);

	Sleep(5000); /////////////////

	UserInterface::endOfProgram();

	joinThreads();
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

bool Huffman::gatherDataFromDictionary(std::string path)
{
	file.open(path, std::ios::in);
	
	if (!file.good())
	{
		return false;
	}

	int tmp = 1;
	std::string stringFromDictionary{};

	while (std::getline(file, dataFromFile))
	{
		if (tmp % 2)
		{
			charFromDictionary = dataFromFile[0];
		}
		else
		{
			stringFromDictionary = dataFromFile;
			huffmanCodeFromDictionary.push_back(std::make_pair(charFromDictionary, stringFromDictionary));
		}
		tmp++;
	}

	file.close();

	return true;
}

void Huffman::gatherShiftFromEncodedFile()
{
	std::string shiftStr = dataFromFile.substr(0,1);
	shift = std::atoi(shiftStr.c_str());
	dataFromFile.erase(dataFromFile.begin(), dataFromFile.begin() + 1);
}

void Huffman::fromBytesToString()
{
	unsigned long long int lengthOfData = dataFromFile.size();
	std::string decoded{};

	for (auto ch : dataFromFile)
	{
		decoded += std::bitset<8>(ch).to_string();
	}
	
	dataFromFile = decoded;

	dataFromFile.erase(dataFromFile.end() - (8 - shift), dataFromFile.end());
}

void Huffman::translateHuffmanCode()
{
	std::string huffmanSequence{};

	for (size_t i = 0; i < dataFromFile.size(); i++)
	{
		huffmanSequence += dataFromFile[i];

		for (size_t j = 0; j < huffmanCodeFromDictionary.size(); j++)
		{
			if (huffmanSequence == huffmanCodeFromDictionary.at(j).second)
			{
				decodedString += huffmanCodeFromDictionary.at(j).first;
				huffmanSequence.clear();
				break;
			}
		}
	}
}

void Huffman::saveDecodedFile(std::string path)
{
	file.open(path, std::ios::out | std::ios::binary);
	file << decodedString;
	file.close();
}

void Huffman::makeUiThreads()
{
	uiThreads.push_back(std::thread(&UserInterface::refreshText));
	uiThreads.push_back(std::thread(&UserInterface::refreshUI));
}

void Huffman::joinThreads()
{
	for (auto &thread : uiThreads)
	{
		thread.join();
	}
}

//&Huffman::userInterface.refreshText