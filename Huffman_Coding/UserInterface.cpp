#include "UserInterface.h"

 std::string UserInterface::defaultText = "Work in progress";
 std::string UserInterface::EMPTY_STRING = "      ";
 char UserInterface::numberOfDots = 0;
 bool UserInterface::programWorks = false;

void UserInterface::refreshProgress()
{
}

void UserInterface::refreshText()
{
	while (programWorks)
	{
		Sleep(500);

		switch (numberOfDots)
		{
		case 0:
			std::cout << "\r" + defaultText + EMPTY_STRING;
			break;
		case 1:
			std::cout << "\r" + defaultText + " .";
			break;
		case 2:
			std::cout << "\r" + defaultText + " . .";
			break;
		case 3:
			std::cout << "\r" + defaultText + " . . .";
			break;
		}

		numberOfDots++;
		if (numberOfDots > 3)
		{
			numberOfDots = 0;
		}
	}
}

void UserInterface::refreshUI()
{
	while (programWorks)
	{
		
	}
}