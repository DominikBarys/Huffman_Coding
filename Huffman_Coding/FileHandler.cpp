#include "FileHandler.h"

FileHandler::FileHandler(int argc, char* argv[])
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
			if (((i + 1) < argc) && (argv[i+1] == std::string("i") || argv[i+1] == std::string("o")))
			{
				if (argv[++i] == "i")
				{
					mode = INPUT;
				}
				else
				{
					mode = OUTPUT;
				}
			}
		}	
	}

	if (checkInputParams())
	{
		std::cout << "Wejscie: " << inputFilePath <<" Wyjscie: " << outputFilePath << " Slownik: " << dictionaryPath 
			<< " Tryb: " << mode;
	}
}

bool FileHandler::checkInputParams()
{
	if (inputFilePath == "" || outputFilePath == "" || dictionaryPath == "" || mode == NONE)
	{
		std::cout << "The input parameters are invalid\n";
		return false;
	}
	return true;
}
