#include "HuffmanDecoding.h"

HuffmanDecoding::HuffmanDecoding(std::string input, std::string output, std::string dictionary)
	:Huffman(input, output, dictionary)
{
	startDecodingSequence();
}

void HuffmanDecoding::startDecodingSequence()
{
	if (!gatherDataFromFile(inputFilePath))
		return;

	if (!gatherDataFromDictionary(dictionaryPath))
		return;

	gatherShiftFromEncodedFile();

	fromBytesToString();

	translateHuffmanCode();

	saveDecodedFile(outputFilePath);

	UserInterface::endOfProgram();
}

bool HuffmanDecoding::gatherDataFromDictionary(std::string path)
{
	file.open(path, std::ios::in | std::ios::binary);

	if (!file.good())
	{
		return false;
	}

	int tmp = 0;
	char tmpChar{};
	std::string stringFromDictionary;

	while (file.get(tmpChar))
	{
		if (tmp % 2 == 0)
		{
			charFromDictionary = tmpChar;
		}
		else
		{
			stringFromDictionary = "";
			while (file.get(tmpChar))
			{
				if (tmpChar == '\n')
				{
					break;
				}
				stringFromDictionary += tmpChar;
			}
			huffmanCodeFromDictionary.push_back(std::make_pair(charFromDictionary, stringFromDictionary));
		}
		tmp++;
	}

	file.close();

	return true;
}

void HuffmanDecoding::gatherShiftFromEncodedFile()
{
	std::string shiftStr = dataFromFile.substr(0, 1);
	shift = std::atoi(shiftStr.c_str());
	dataFromFile.erase(dataFromFile.begin(), dataFromFile.begin() + 1);
}

void HuffmanDecoding::fromBytesToString()
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

void HuffmanDecoding::translateHuffmanCode()
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

void HuffmanDecoding::saveDecodedFile(std::string path)
{
	file.open(path, std::ios::out | std::ios::binary);
	file << decodedString;
	file.close();
}