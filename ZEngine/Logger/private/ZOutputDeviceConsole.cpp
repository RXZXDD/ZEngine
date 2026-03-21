#include "../public/ZOutputDeviceConsole.h"

#include <iostream>


namespace ZEngine {
	void ZOutputDeviceConsole::Log(std::wstring Line)
	{
		std::wcout << Line << std::endl;

	}
}
