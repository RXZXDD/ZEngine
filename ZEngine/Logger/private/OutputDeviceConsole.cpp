#include "../public/OutputDeviceConsole.h"
#include "Logger/public/LoggerMisc.h"

#include <iostream>
#include <Windows.h>

namespace ZEngine {
	ZOutputDeviceConsole::ZOutputDeviceConsole()
	{
		SetConsoleOutputCP(CP_UTF8);
	}

	void ZEngine::ZOutputDeviceConsole::Log(const ZLogRecord& Record)
	{
		std::cout << Record.msg << std::endl;

	}
}
