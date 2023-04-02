#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>

class UserInterface
{
public:
	UserInterface() = delete;

	static void startOfProgram();
	static void endOfProgram();

	static void refreshWorkInProgress();

	static void showTimeElapsed();

	static void invalidInputParameters();

private:

	static std::string EMPTY_STRING;

	static std::string defaultText;
	static char numberOfDots;
	static bool programWorks;

	static std::chrono::time_point<std::chrono::steady_clock> clockStart;
	static std::chrono::time_point<std::chrono::steady_clock> clockEnd;
	static double timeElapsed;
};

