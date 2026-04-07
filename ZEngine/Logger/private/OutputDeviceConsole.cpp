#include "../public/OutputDeviceConsole.h"

#include <iostream>

namespace ZEngine {
	ZOutputDeviceConsole::ZOutputDeviceConsole()
	{
		SetConsoleOutputCP(CP_UTF8);
	}

	void ZEngine::ZOutputDeviceConsole::Log(std::string Line)
	{
		std::cout << Line << std::endl;

	}
}
