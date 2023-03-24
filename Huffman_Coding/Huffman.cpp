#include "Huffman.h"

Huffman::Huffman(int argc, char* argv[])
{
	fileHandler = FileHandler(argc, argv);
	checkMode();
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
}

void Huffman::calculateAmountOfCharacters()
{

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
