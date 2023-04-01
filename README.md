# Huffman coding program 

## Description
A program for encoding and then decoding files such as: txt, bmp, png, mp3, mp4 and other similar files. 
The program uses the Huffman method for this. After the encoding operation it generates the dictionary file (that is later used for decoding)
and encoded file in binary format. To decode an encoded file, enter the encoded file and the previously generated dictionary on the program input.

##

## How to use the program
### The program has four input parameters that can be given in any order. Each parameter is preceded by an appropriate sign:
* **-m** -> Mode in which the program works, **'e'** for encoding and **'d'** for decoding
* **-i** -> Path to the input file. If the only name of the file is given, the program will look for it in a special folder "\Resources" in the directory with the program.
* **-o** -> Path to the output file. If the only name of the file is given, the program will save it in a special folder "\Resources" in the directory with the program.
* **-d** -> Path to dictionary .txt file generated in encoding and used in decoding. If the only name of file is given, the program will generate or search for it in a special folder "\Resources" in the directory with the program.

**Encoded file and dictionary has to be always in .txt format**

To use a program call it with the previously mentioned parameters and then, after a spece, enter the argument for the given parameter.

##

## Example of use
* For encoding: 
```
Huffman_Coding.exe -m e -i FileToEncode.png -o EncodedFile.txt -d Dictionary.txt
```
**Remember that the output file and dictionary should be in .txt format**
* For decoding:
```
Huffman_Coding.exe -m d -i EncodedFile.txt -o DecodedFile.png -d Dictionary.txt
```
**Make sure you are using the dictionary generated when encoding this file earlier and the output file has the same format as the input file when encoding**

##
