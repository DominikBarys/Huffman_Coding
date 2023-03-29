#include <chrono>
#include <Windows.h>
#include "Huffman.h"

//TO DO Add thread to show user in terminal progress of program

int main(int argc, char* argv[])
{ 
    auto clockStart = std::chrono::high_resolution_clock::now();

    Huffman huffman(argc, argv);

    auto clockEnd = std::chrono::high_resolution_clock::now();

    double timeElapsed = std::chrono::duration_cast<std::chrono::duration<double>>(clockEnd - clockStart).count();

    std::cout << "Time elapsed: " << std::fixed << std::setprecision(2) << timeElapsed << " seconds\n";

    system("pause");
}