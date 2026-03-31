#include "../public/OutputDeviceConsole.h"

#include <iostream>

namespace ZEngine {
	ZOutputDeviceConsole::ZOutputDeviceConsole()
	{
		SetConsoleOutputCP(CP_UTF8);
	}
	void ZEngine::ZOutputDeviceConsole::Log(std::string Line, const ZBaseLogger* logger, const LogLevel level)
	{
		std::cout << Line << std::endl;

	}
}
