#include "WinUtils.h"
#include "Admin.h"

void Admin::processAdminInput()
{
	std::string adminInput = "";
	
	while (1)
	{
		std::cout << "Admin> ";
		getline(std::cin, adminInput);
		
		if (adminInput == "logout")	
		{
			WinUtils::clearScreen();
			return;
		}
	}
}
