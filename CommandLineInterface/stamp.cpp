//****************************************************************************
//	STAMP Command Line Interface
//	Programmed by: Houston Brown
//	Last Compiled Date: 5/15/2024
//****************************************************************************

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <csignal>
#include "WinUtils.h"
#include "Student.h"
#include "Tutor.h"
#include "Faculty.h"
#include "Admin.h"
#include "KeyboardInterruptException.cpp"


void printOpeningHdr();

void login();

void registerAcct();

void printHelp();

void clearConsoleScreen();

void processInput();

void signalHandler(int signal);


//****************************************************************************
//	Driver
//****************************************************************************
int main(int argc, char *argv[])
{
	// Register signal handler
    signal(SIGINT, signalHandler);
	std::string dashboardInput = "";

	WinUtils::clearScreen();
	printOpeningHdr();
	
	try
	{
		processInput();	
	}
	catch (KeyboardInterruptException& kiex)
	{
		exit(1);
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught in stamp.cpp" << std::endl;
	}
	
	return 0;
}


//****************************************************************************
//	NAME: printOpeningMsg.
//
//	DESCRIPTION: Display the opening banner of system information.
//****************************************************************************
void printOpeningHdr()
{
	const std::string STARS = "********************************************" \
							  "************************************";
	const std::string BLANKLINE = "*                                       " \
							  "                                       *";							  
							  
	std::cout << STARS << std::endl;
	
	/////////////////////////////////////////////////////
	// Coloring Output
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO myBuffInfo;
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &myBuffInfo);
	/////////////////////////////////////////////////////
	
	SetConsoleTextAttribute(hConsole, 10);	
	printf("*        ####    ######       ##              ##     ##        #######         *\n");
	printf("*       #    #   ######     ## ##            ## ##  ## ##      ##     ##       *\n");
	printf("*       ##         ##      ##   ##          ##  ##  ##  ##     ##     ##       *\n");
	printf("*        ####      ##     #########        ##     ##     ##    ########        *\n");
	printf("*            ##    ##    ##       ##      ##              ##   ##              *\n");
	printf("*       #    ##    ##   ##         ##    ##                ##  ##              *\n");
	printf("*        ####      ##  ##           ##  ##                  ## ##              *\n");	

	// Restoring console defaults
	SetConsoleTextAttribute(hConsole, myBuffInfo.wAttributes);	
	
	std::cout << BLANKLINE << std::endl;
	std::cout << "*\tWelcome to the Studnet/Tutor Appointment Management";
	std::cout << " Program (STAMP)    *" << std::endl << BLANKLINE;
	std::cout << std::endl;
	
	std::cout << "*     All information entered here is the sole property of";
	std::cout << " the owners of this  *" << std::endl;
	std:: cout << "* system(TTM co.).";
	
	std::cout << " Unauthorized use of this system is striclty prohibited.";
	std::cout << "     *" << std::endl;
	
	//std::cout << BLANKLINE << std::endl;		
	std::cout << STARS << std::endl;
}

//****************************************************************************
//	NAME: login.
//
//	DESCRIPTION: When the user enters the login command, verify their
//				 credentials.  If they are valid, pass control to the proper
//				 function.  Else, return to the main prompt.   
//****************************************************************************
void login(const std::string uname, const std::string password)
{
	if (uname == "uname" && password == "password")
	{
		WinUtils::clearScreen();
		Student::processStudentInput();
	}
	if (uname == "tutor" && password == "password")
	{
		WinUtils::clearScreen();
		Tutor::processTutorInput();
	}
	if (uname == "faculty" && password == "password")
	{
		WinUtils::clearScreen();
		Faculty::processFacultyInput();
	}
	if (uname == "admin" && password == "password")
	{
		WinUtils::clearScreen();
		Admin::processAdminInput();
	}
}

//****************************************************************************
//	NAME: registerAcct.
//
//	DESCRIPTION: When the user enters the register account command, then call
//				 the new student user API call and pass in the arguments to
//				 the command.  Display an appropriate message based on the
//				 return value of the call.    
//****************************************************************************
void registerAcct()
{
}

//****************************************************************************
//	NAME: printHelp.
//
//	DESCRIPTION: Display a list of the commands and arguments for each 
//				 command. 
//****************************************************************************
void printHelp()
{
}

//****************************************************************************
//	NAME: clearConsoleScreen.
//
//	DESCRIPTION: If the user enters "clear", then the WinUtils function
//				 will be called and the console screen will be cleared.   
//****************************************************************************
void clearConsoleScreen()
{
	WinUtils::clearScreen();
}

//****************************************************************************
//	NAME: processInput.
//
//	DESCRIPTION: Process the requests of the user and call the appropiate
//				 functions in accordance with the User Manual for STAMP.  
//****************************************************************************
void processInput()
{
	std::string userInput = "";
	
	while (1)
	{
		std::cout << "STAMP> ";
		getline(std::cin, userInput);
		
		std::istringstream iss(userInput);
		std::vector<std::string> tokens;
		std::string token;
		
		while (iss >> token)
		{
			tokens.push_back(token);
		}
		
		if (!tokens.empty())
		{
			if (tokens[0] != "login" && tokens[0] != "help"
				&& tokens[0] != "regact" && tokens[0] != "clear")
			{
				// invalid command
				const std::string errorMsg = tokens[0] + 
											 " is not a valid command.";
				WinUtils::printErrorMsg(errorMsg);
				std::cout << std::endl << std::endl;
				continue;
			}
			if (tokens[0] == "login" && tokens.size() == 3)
			{
				login(tokens[1], tokens[2]);
			}
			if (tokens[0] == "clear" && tokens.size() == 1)
			{
				clearConsoleScreen();
			}
			else if (tokens.size() < 3)
			{
				if (tokens.size() < 3)
				{
					const std::string errMsg = "invalid number of arguments.";
					WinUtils::printErrorMsg(errMsg);
					std::cout << std::endl << std::endl;
					continue;
				}
			}
		}
	}
}

//****************************************************************************
//	NAME: signalHandler.
//
//	DESCRIPTION: If the CTRL+C signal is encountered, then exit the program
//				 gracefully.  
//****************************************************************************
void signalHandler(int signal) 
{
	if (signal == SIGINT) 
	{
        exit(signal); // Exit with the signal code
    }
    // only processing CTRL+C signal
}
