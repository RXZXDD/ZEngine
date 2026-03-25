#include "../public/OutputDeviceConsole.h"

#include <iostream>


namespace ZEngine {
	void ZEngine::ZOutputDeviceConsole::Log(std::wstring Line, const ZBaseLogger* logger, const LogLevel level)
	{
		std::wcout << Line << std::endl;

	}
}
