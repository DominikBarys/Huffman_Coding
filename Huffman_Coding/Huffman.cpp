#include "Huffman.h"

Huffman::Huffman(std::string input, std::string output, std::string dictionary)
	:inputFilePath(input), outputFilePath(output), dictionaryPath(dictionary)
{
	makeUiThreads();
}

Huffman::~Huffman()
{
	joinThreads();
}

bool Huffman::gatherDataFromFile(std::string path)
{
	file.open(path, std::ios::in | std::ios::binary);

	if (!file.good())
	{
		std::cout << "File not found\n";
		file.close();
		return false;
	}

	char gatheredCHar{};

	while (file.get(gatheredCHar))
	{
		dataFromFile += gatheredCHar;
	}

	file.close();

	return true;
}

void Huffman::makeUiThreads()
{
	uiThreads.push_back(std::thread(&UserInterface::refreshWorkInProgress));
}

void Huffman::joinThreads()
{
	for (auto &thread : uiThreads)
	{
		thread.join();
	}
	UserInterface::showTimeElapsed();
}