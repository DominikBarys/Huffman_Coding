#include "FileHandler.h"

FileHandler::FileHandler(int argc, char* argv[])
{
	if (argc > 1)
	{
		UserInterface::startOfProgram();
		extractParameters(argc, argv);
		checkInputParams();
		startProgram(mode);
	}
	else
		UserInterface::invalidInputParameters();
}

FileHandler::~FileHandler()
{
	if (huffman != nullptr)
		delete huffman;
}

void FileHandler::startProgram(Mode mode)
{
	switch (mode)
	{
	case NONE:
		UserInterface::invalidInputParameters();
		break;
	case ENCODE:
		huffman = new HuffmanEncoding(inputFilePath, outputFilePath, dictionaryPath);
		break;
	case DECODE:
		huffman = new HuffmanDecoding(inputFilePath, outputFilePath, dictionaryPath);
		break;
	}
}

void FileHandler::checkInputParams()
{
	if (!std::regex_search(inputFilePath, ruleForFilepath))
	{
		inputFilePath = setFilepathToResources(inputFilePath);
	}
	if (!std::regex_search(outputFilePath, ruleForFilepath))
	{
		outputFilePath = setFilepathToResources(outputFilePath);
	}
	if (!std::regex_search(dictionaryPath, ruleForFilepath))
	{
		dictionaryPath = setFilepathToResources(dictionaryPath);
	}
}

void FileHandler::extractParameters(int argc, char* argv[])
{
	for (size_t i = 1; i < argc; i++)
	{
		if (argv[i] == std::string("-i"))
		{
			if ((i + 1) < argc)
			{
				inputFilePath = argv[++i];
			}
		}
		else if (argv[i] == std::string("-o"))
		{
			if ((i + 1) < argc)
			{
				outputFilePath = argv[++i];
			}
		}
		else if (argv[i] == std::string("-d"))
		{
			if ((i + 1) < argc)
			{
				dictionaryPath = argv[++i];
			}
		}
		else if (argv[i] == std::string("-m"))
		{
			if (((i + 1) < argc) && (argv[i + 1] == std::string("e") || argv[i + 1] == std::string("d")))
			{
				if (argv[++i] == std::string("e"))
				{
					mode = ENCODE;
				}
				else
				{
					mode = DECODE;
				}
			}
		}
	}
}

std::string FileHandler::setFilepathToResources(std::string path)
{
	std::filesystem::path currentPath;

	currentPath = directoryPath;
	currentPath /= "Resources";
	currentPath /= path;
	path = currentPath.string();

	return path;
}
