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
			if (((i + 1) < argc) && (argv[i+1] == std::string("e") || argv[i+1] == std::string("d")))
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