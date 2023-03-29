#include "FileHandler.h"

FileHandler::FileHandler(int argc, char* argv[])
{
	extractParameters(argc, argv);
	checkInputParams();
}

void FileHandler::checkInputParams()
{
	std::filesystem::path currentPath;

	if (!std::regex_search(inputFilePath, ruleForFilepath))
	{
		currentPath = directoryPath;
		currentPath /= inputFilePath;
		inputFilePath = currentPath.string();
	}
	if (!std::regex_search(outputFilePath, ruleForFilepath))
	{
		currentPath = directoryPath;
		currentPath /= outputFilePath; 
		outputFilePath = currentPath.string();
	}
	if (!std::regex_search(dictionaryPath, ruleForFilepath))
	{
		currentPath = directoryPath;
		currentPath /= dictionaryPath;
		dictionaryPath = currentPath.string();
	}

}

//TO DO using tolower() to better parsing input parameters
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
