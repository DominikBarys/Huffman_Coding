#pragma once
#include <bitset>
#include "Huffman.h"

class HuffmanDecoding : public Huffman
{
public:
	HuffmanDecoding() = delete;
	HuffmanDecoding(std::string input, std::string output, std::string dictionary);

private:
	char charFromDictionary{};
	std::vector <std::pair<char, std::string>> huffmanCodeFromDictionary{};
	std::string decodedString{};

	void startDecodingSequence();

	bool gatherDataFromDictionary(std::string path);
	void gatherShiftFromEncodedFile();
	void fromBytesToString();
	void translateHuffmanCode();
	void saveDecodedFile(std::string);
};

