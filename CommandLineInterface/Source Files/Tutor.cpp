#include "WinUtils.h"
#include "Tutor.h"

void Tutor::processTutorInput()
{
	std::string tutorInput = "";
	
	while (1)
	{
		std::cout << "Tutor> ";
		getline(std::cin, tutorInput);
		
		if (tutorInput == "logout")	
		{
			WinUtils::clearScreen();
			return;
		}
	}
}
