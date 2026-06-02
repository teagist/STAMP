//****************************************************************************
//	STAMP Command Line Interface.
//
//  Faculty User Definition File.
//
//	Programmed by: Houston Brown
//	Last Compiled Date: 5/15/2024
//****************************************************************************

#include "WinUtils.h"
#include "Faculty.h"

void Faculty::processFacultyInput()
{
	std::string facultyInput = "";
	
	while (1)
	{
		std::cout << "Faculty> ";
		getline(std::cin, facultyInput);
		
		if (facultyInput == "logout")	
		{
			WinUtils::clearScreen();
			return;
		}
	}
}
