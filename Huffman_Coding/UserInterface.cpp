#include "UserInterface.h"

 std::string UserInterface::defaultText = "Work in progress";
 std::string UserInterface::EMPTY_STRING = "      ";
 char UserInterface::numberOfDots = 0;
 bool UserInterface::programWorks = false;
 double UserInterface::timeElapsed = 0;
 std::chrono::time_point<std::chrono::steady_clock> UserInterface::clockStart{};
 std::chrono::time_point<std::chrono::steady_clock> UserInterface::clockEnd{};

 void UserInterface::startOfProgram()
 {
	 clockStart = std::chrono::high_resolution_clock::now();
	 programWorks = true;
 }

 void UserInterface::endOfProgram()
 {
	 clockEnd = std::chrono::high_resolution_clock::now();
	 programWorks = false;
	 showTimeElapsed();
 }

 void UserInterface::refreshWorkInProgress()
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

 void UserInterface::showTimeElapsed()
 {
	 timeElapsed = timeElapsed = std::chrono::duration_cast<std::chrono::duration<double>>(clockEnd - clockStart).count();

	 system("cls");
	 std::cout << "The program has finished\n";
	 std::cout << "Time elapsed: " << std::fixed << std::setprecision(3) << timeElapsed << " seconds\n";
 }

 void UserInterface::invalidInputParameters()
 {
	 std::cout << "Input parameters are invalid\n";
 }

