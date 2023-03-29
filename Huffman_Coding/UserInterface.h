#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

class UserInterface
{
public:
	static void endOfProgram() { programWorks = false; }
	static void startOfProgram() { programWorks = true; }

	static void refreshText();
	static void refreshProgress();
	static void refreshUI();

private:

	static std::string EMPTY_STRING;

	UserInterface() = delete;

	static std::string defaultText;
	static std::string currentText;
	
	static char numberOfDots;

	static bool programWorks;
};

