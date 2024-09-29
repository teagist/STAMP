#include "WinUtils.h"
#include "Student.h"

void Student::processStudentInput()
{
	signal(SIGINT, signalHandler);
	std::string studentInput = "";
	
	while (1)
	{
		std::cout << "Student> ";
		getline(std::cin, studentInput);
		
		if (studentInput == "logout")	
		{
			WinUtils::clearScreen();
			return;
		}
	}
}


void Student::signalHandler(int signal) 
{
	if (signal == SIGINT) 
	{
        exit(signal); // Exit with the signal code
    }
    // only processing CTRL+C signal
}
